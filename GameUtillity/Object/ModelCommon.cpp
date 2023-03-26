#include "ModelCommon.h"
#include "FileUtillity.h"
#include <memory>
#include <cassert>
#include <fstream>
#include <sstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#pragma region 名前空間

using YGame::ModelObjectCommon;
using YGame::ModelCommon;
using YDX::PipelineSet;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;

#pragma endregion


#pragma region ModelCBSetCommon

std::unique_ptr<YGame::ViewProjection> ModelObjectCommon::sDefVP_ = nullptr;
std::unique_ptr<YGame::LightGroup> ModelObjectCommon::sDefLightGroup_ = nullptr;
std::unique_ptr<YGame::Color> ModelObjectCommon::sDefColor_ = nullptr;

void ModelObjectCommon::StaticInitialize()
{
	// 生成
	sDefVP_.reset(new YGame::ViewProjection());
	sDefVP_->Initialize({});

	sDefLightGroup_.reset(LightGroup::Create());

	sDefColor_.reset(Color::Create());
}

#pragma endregion


#pragma region ModelCommon

PipelineSet ModelCommon::sPipelineSet_;

void ModelCommon::StaticInitialize()
{
	// パイプライン初期化
	std::unique_ptr<PipelineSet::IStatus> pplnState = std::make_unique<PipelineSetStatus>();
	sPipelineSet_.Initialize(pplnState.get());
}

void ModelCommon::ShaderSet::Load(ID3DBlob* errorBlob)
{
	ID3DBlob* vs = nullptr;
	ID3DBlob* ps = nullptr;

	// 頂点シェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/ModelVS.hlsl", "main", "vs_5_0", vs, errorBlob);
	// ピクセルシェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/ModelPS.hlsl", "main", "ps_5_0", ps, errorBlob);

	vsBlob_ = vs;
	psBlob_ = ps;
}

void ModelCommon::PipelineSetStatus::Initialize(ID3DBlob* errorBlob_)
{
	// シェーダー読み込み
	ShaderSet shdrs;
	shdrs.Load(errorBlob_);

	// 頂点レイアウトの設定
	inputLayout_ =
	{
		// 頂点座標	 (x, y, z)
		{
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		// 法線		 (x, y, z)
		{
			"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		// UV座標	 (x, y)
		{
			"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		// 接空点	 (x, y, z)
		{
			"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		// 頂点色	 (x, y, z, w)
		{
			"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		}
	};

	// テクスチャサンプラーの設定
	{
		D3D12_STATIC_SAMPLER_DESC sampleDesc{};
		sampleDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 横折り返し   (タイリング)
		sampleDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 縦折り返し   (タイリング)
		sampleDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 奥行折り返し (タイリング)
		sampleDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK; // ボーダーの時は黒
		sampleDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;   // 全てリニア補間
		sampleDesc.MaxLOD = D3D12_FLOAT32_MAX; // ミニマップ最大値
		sampleDesc.MinLOD = 0.0f;              // ミニマップ最小値
		sampleDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
		sampleDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // ピクセルシェーダーからのみ使用可能

		sampleDesc_.push_back(sampleDesc);
	}

	// ルートパラメータの設定
	{
		size_t rpIdxCBNum = static_cast<size_t> (RootParameterIndex::TexDT);

		for (size_t i = 0; i < rpIdxCBNum; i++)
		{
			// 定数バッファ
			D3D12_ROOT_PARAMETER rootParam{};
			rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;  // 定数バッファビュー
			rootParam.Descriptor.ShaderRegister = static_cast<UINT>(i); // 定数バッファ番号
			rootParam.Descriptor.RegisterSpace = 0;					  // デフォルト値
			rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // 全てのシェーダから見える

			rootParams_.push_back(rootParam);
		}

		// デスクリプタレンジの設定
		descriptorRange_.NumDescriptors = 1; // 1度の描画に使うテクスチャが1枚なので1
		descriptorRange_.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		descriptorRange_.BaseShaderRegister = 0; // テクスチャレジスタ0番
		descriptorRange_.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

		// テクスチャレジスタ
		D3D12_ROOT_PARAMETER rootParam{};
		rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		rootParam.DescriptorTable.pDescriptorRanges = &descriptorRange_;
		rootParam.DescriptorTable.NumDescriptorRanges = 1;
		rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // 全てのシェーダから見える

		rootParams_.push_back(rootParam);
	}

	// パイプライン設定
	{
		// シェーダーの設定
		pipelineDesc_.VS.pShaderBytecode = shdrs.vsBlob_.Get()->GetBufferPointer();
		pipelineDesc_.VS.BytecodeLength = shdrs.vsBlob_.Get()->GetBufferSize();
		pipelineDesc_.PS.pShaderBytecode = shdrs.psBlob_.Get()->GetBufferPointer();
		pipelineDesc_.PS.BytecodeLength = shdrs.psBlob_.Get()->GetBufferSize();

		// ラスタライザの設定
		pipelineDesc_.RasterizerState.CullMode = D3D12_CULL_MODE_BACK; // 背面をカリング

		// デプスステンシルステートの設定
		pipelineDesc_.DepthStencilState.DepthEnable = true; // 深度テスト
		pipelineDesc_.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL; // 書き込み許可
		pipelineDesc_.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS; // 小さければ合格
		pipelineDesc_.DSVFormat = DXGI_FORMAT_D32_FLOAT; // 深度フォーマット

		// 図形の形状設定
		pipelineDesc_.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	}

	// プリミティブ形状の設定
	primitive_ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST; // 三角形リスト
}

void ModelCommon::CalculateNormals(std::vector<VData>& v, const std::vector<uint16_t> indices)
{
	// 三角形1つごとに計算していく
	for (size_t i = 0; i < indices.size() / 3; i++)
	{
		// 三角形のインデックスを取り出す
		unsigned short index0 = indices[i * 3 + 0];
		unsigned short index1 = indices[i * 3 + 1];
		unsigned short index2 = indices[i * 3 + 2];
		
		// 三角形を構成する頂点座標ベクトルに代入
		Vector3 p0 = v[index0].pos_;
		Vector3 p1 = v[index1].pos_;
		Vector3 p2 = v[index2].pos_;
		
		// p0->p1ベクトル、p0->p2ベクトルを計算 (ベクトルの減算)
		Vector3 v1 = p1 - p0;
		Vector3 v2 = p2 - p0;
		
		// 外積は両方から垂直なベクトル
		Vector3 normal = v1.Cross(v2);
		
		// 正規化 (長さを1にする)
		normal = normal.Normalized();
		
		// 求めた法線を頂点データに代入
		v[index0].normal_ = normal;
		v[index1].normal_ = normal;
		v[index2].normal_ = normal;
	}
}
void ModelCommon::CalculateSmoothedVertexNormals(std::vector<VData>& vertices,
	std::unordered_map<unsigned short, std::vector<unsigned short>>& smoothData)
{
	// スムースデータの数だけ
	auto itr = smoothData.begin();
	for (; itr != smoothData.end(); ++itr)
	{
		// 次の要素を代入
		std::vector<unsigned short>& v = itr->second;
		
		// 法線
		Vector3 normal = {};
		
		// 計算
		for (unsigned short index : v)
		{
			normal += vertices[index].normal_;
		}
		normal = (normal / (float)v.size()).Normalized();
		
		// 代入
		for (unsigned short index : v)
		{
			vertices[index].normal_ = normal;
		}
	}
}
YDX::VertexIndex<ModelCommon::VData> ModelCommon::LoadVertices(const aiMesh* src, bool invU, bool invV, bool isNormalized)
{
	// 戻り値用
	YDX::VertexIndex<VData> vtIdx;

	// 保存用
	aiVector3D zero3D(0.0f, 0.0f, 0.0f);
	aiColor4D zeroColor(0.0f, 0.0f, 0.0f, 0.0f);

	std::vector<VData> vData;
	std::vector<uint16_t> indices;

	// リサイズ(頂点の数だけ)
	vData.resize(src->mNumVertices);

	// 頂点の数
	for (size_t i = 0; i < src->mNumVertices; ++i)
	{
		// 読み込み(代入)
		aiVector3D* position = &(src->mVertices[i]);
		aiVector3D* normal = &(src->mNormals[i]);
		aiVector3D* uv = (src->HasTextureCoords(0)) ? &(src->mTextureCoords[0][i]) : &zero3D;
		aiVector3D* tangent = (src->HasTangentsAndBitangents()) ? &(src->mTangents[i]) : &zero3D;
		aiColor4D* color = (src->HasVertexColors(0)) ? &(src->mColors[0][i]) : &zeroColor;

		if (invU) { uv->x = 1.0f - uv->x; }
		if (invV) { uv->y = 1.0f - uv->y; }

		VData vertex = {};
		vertex.pos_ = Vector3(position->x, position->y, position->z);
		vertex.normal_ = Vector3(normal->x, normal->y, normal->z);
		vertex.uv_ = Vector2(uv->x, uv->y);
		vertex.tangent_ = Vector3(tangent->x, tangent->y, tangent->z);
		vertex.color_ = Vector4(color->r, color->g, color->b, color->a);

		vData[i] = vertex;
	}

	// リサイズ(インデックスの数だけ)
	indices.resize(src->mNumFaces * static_cast<size_t>(3));

	// インデックスの数
	for (size_t i = 0; i < src->mNumFaces; ++i)
	{
		// 読み込み(代入)
		const aiFace& face = src->mFaces[i];

		indices[i * 3 + 0] = face.mIndices[0];
		indices[i * 3 + 1] = face.mIndices[1];
		indices[i * 3 + 2] = face.mIndices[2];
	}

	// 法線計算
	if (isNormalized) { CalculateNormals(vData, indices); }

	// 頂点インデックス初期化(代入)
	vtIdx.Initialize(vData, indices);

	// 頂点インデックスを返す
	return vtIdx;
}

void ModelCommon::StaticSetDrawCommand()
{
	// パイプラインをセット
	sPipelineSet_.SetDrawCommand();
}

#pragma endregion