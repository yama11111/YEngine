#include "Model.h"
#include "CalcTransform.h"
#include "FileUtillity.h"
#include <cassert>
#include <fstream>
#include <sstream>

#pragma region 名前空間

using std::unique_ptr;
using YGame::ModelObject;
using YGame::Model;
using YDX::PipelineSet;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;

#pragma endregion

#pragma region ルートパラメータ番号

static const UINT TraIndex	 = static_cast<UINT>(Model::Common::RootParameterIndex::TransformCB); // transform
static const UINT ColIndex	 = static_cast<UINT>(Model::Common::RootParameterIndex::ColorCB); // color
static const UINT LigIndex	 = static_cast<UINT>(Model::Common::RootParameterIndex::LightCB); // light
static const UINT MateIndex	 = static_cast<UINT>(Model::Common::RootParameterIndex::MaterialCB); // material
static const UINT TexIndex	 = static_cast<UINT>(Model::Common::RootParameterIndex::TexDT); // tex

#pragma endregion

#pragma region Static

std::vector<std::unique_ptr<Model>> Model::models_{};
Model::Common Model::common_{};
YDX::PipelineSet Model::Common::sPipelineSet_{};

#pragma endregion

#pragma region Model

Model* Model::CreateCube()
{
	// モデル生成
	unique_ptr<Model> newModel = std::make_unique<Model>();


	// メッシュ生成
	std::unique_ptr<Mesh> newMesh;

	// メッシュロード
	newMesh.reset(Mesh::CreateCube());

	// 追加
	newModel->meshes_.push_back(std::move(newMesh));


	// ポインタを獲得
	Model* newModelPtr = newModel.get();

	// モデルを保存
	models_.push_back(std::move(newModel));

	// モデルポインタを返す
	return newModelPtr;
}

Model* Model::CreateCube(const std::string& texFileName)
{
	// モデル生成
	unique_ptr<Model> newModel = std::make_unique<Model>();


	// メッシュ生成
	std::unique_ptr<Mesh> newMesh;
	
	// メッシュロード
	newMesh.reset(Mesh::CreateCube(texFileName));

	// 追加
	newModel->meshes_.push_back(std::move(newMesh));


	// ポインタを獲得
	Model* newModelPtr = newModel.get();

	// モデルを保存
	models_.push_back(std::move(newModel));

	// モデルポインタを返す
	return newModelPtr;
}

Model* Model::Load(const std::string& modelFileName, const bool isSmoothing)
{
	// 読み込んだことがあるかチェック
	for (size_t i = 0; i < models_.size(); i++)
	{
		// ファイルパス が同じなら
		if (modelFileName == models_[i]->fileName_)
		{
			// そのテクスチャポインタを返す
			return models_[i].get();
		}
	}

	// モデル生成
	unique_ptr<Model> newModel = std::make_unique<Model>();


	// メッシュ生成
	std::unique_ptr<Mesh> newMesh;

	// ファイル名
	std::string objFileName  = modelFileName + ".obj";
	objFileName = YUtil::FilePath(objFileName);
	std::string directoryPath = "Resources/Models/" + modelFileName + "/";

	// メッシュロード
	newMesh.reset(Mesh::Load(directoryPath, objFileName, isSmoothing));

	// 追加
	newModel->meshes_.push_back(std::move(newMesh));

	// ファイル名代入
	newModel->fileName_ = modelFileName;


	// ポインタを獲得
	Model* newModelPtr = newModel.get();

	// モデルを保存
	models_.push_back(std::move(newModel));

	// モデルポインタを返す
	return newModelPtr;
}

void Model::AllClear()
{
	// モデル全消去
	for (size_t i = 0; i < models_.size(); i++)
	{
		models_[i].reset(nullptr);
	}
	models_.clear();
}

void Model::Draw(ModelObject* pObj)
{
	// 描画しないなら弾く
	if (isInvisible_) { return; }

	// 定数バッファをシェーダーに送る
	pObj->SetDrawCommand(TraIndex, ColIndex, LigIndex);

	// メッシュ毎に違うバッファ
	for (size_t i = 0; i < meshes_.size(); i++)
	{
		// 描画
		meshes_[i]->Draw(MateIndex, TexIndex);
	}
}

#pragma endregion

#pragma region Common

void Model::Common::StaticInitialize()
{
	// パイプライン初期化
	std::unique_ptr<PipelineSet::IStatus> pplnState = std::make_unique<PipelineSetStatus>();
	sPipelineSet_.Initialize(pplnState.get());
}

void Model::Common::ShaderSet::Load(ID3DBlob* errorBlob)
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

void Model::Common::PipelineSetStatus::Initialize(ID3DBlob* errorBlob_)
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

void Model::Common::StaticSetPipeline()
{
	// パイプラインをセット
	sPipelineSet_.SetDrawCommand();
}

#pragma endregion
