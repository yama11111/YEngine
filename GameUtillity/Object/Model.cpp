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

static const UINT TraIndex	 = static_cast<UINT>(Model::Pipeline::RootParameterIndex::TransformCB); // transform
static const UINT ColIndex	 = static_cast<UINT>(Model::Pipeline::RootParameterIndex::ColorCB); // color
static const UINT LigIndex	 = static_cast<UINT>(Model::Pipeline::RootParameterIndex::LightCB); // light
static const UINT MateIndex	 = static_cast<UINT>(Model::Pipeline::RootParameterIndex::MaterialCB); // material
static const UINT TexIndex	 = static_cast<UINT>(Model::Pipeline::RootParameterIndex::TexDT); // tex

#pragma endregion

#pragma region Static

std::vector<std::unique_ptr<Model>> Model::models_{};
YDX::PipelineSet Model::Pipeline::sPipelineSet_{};

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
	std::string objFileName = modelFileName + ".obj";
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
	pObj->SetDrawCommand(TraIndex, ColIndex, LigIndex, MateIndex);

	// メッシュ毎に違うバッファ
	for (size_t i = 0; i < meshes_.size(); i++)
	{
		// 描画
		meshes_[i]->Draw(TexIndex);
	}
}

#pragma endregion

#pragma region Pipeline

void Model::Pipeline::ShaderSet::Load() 
{
	// エラーオブジェクト
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

	ID3DBlob* vs = nullptr;
	ID3DBlob* ps = nullptr;

	// 頂点シェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/ModelVS.hlsl", "main", "vs_5_0", vs, errorBlob.Get());
	// ピクセルシェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/ModelPS.hlsl", "main", "ps_5_0", ps, errorBlob.Get());

	vsBlob_ = vs;
	psBlob_ = ps;
}

void Model::Pipeline::StaticInitialize()
{
	// パイプライン初期化用設定
	PipelineSet::InitStatus initStatus;


#pragma region シェーダー読み込み

	ShaderSet shdrs;
	shdrs.Load();

#pragma endregion


#pragma region 頂点レイアウトの設定

	initStatus.inputLayout_ =
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
		//// 接空点	 (x, y, z)
		//{
		//	"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		//},
		//// 頂点色	 (x, y, z, w)
		//{
		//	"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		//}
	};

#pragma endregion


#pragma region テクスチャサンプラーの設定

	D3D12_STATIC_SAMPLER_DESC samplerDesc{};
	samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 横折り返し   (タイリング)
	samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 縦折り返し   (タイリング)
	samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 奥行折り返し (タイリング)
	samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK; // ボーダーの時は黒
	samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;   // 全てリニア補間
	samplerDesc.MaxLOD = D3D12_FLOAT32_MAX; // ミニマップ最大値
	samplerDesc.MinLOD = 0.0f;              // ミニマップ最小値
	samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // ピクセルシェーダーからのみ使用可能

	initStatus.samplerDescs_.push_back(samplerDesc);

#pragma endregion


#pragma region ルートパラメータの設定

	size_t rpIdxCBNum = static_cast<size_t> (RootParameterIndex::TexDT);

	for (size_t i = 0; i < rpIdxCBNum; i++)
	{
		// 定数バッファ
		D3D12_ROOT_PARAMETER rootParam{};
		rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;  // 定数バッファビュー
		rootParam.Descriptor.ShaderRegister = static_cast<UINT>(i); // 定数バッファ番号
		rootParam.Descriptor.RegisterSpace = 0;					  // デフォルト値
		rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // 全てのシェーダから見える

		initStatus.rootParams_.push_back(rootParam);
	}

	// デスクリプタレンジの設定
	initStatus.descriptorRange_.NumDescriptors = 1; // 1度の描画に使うテクスチャが1枚なので1
	initStatus.descriptorRange_.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	initStatus.descriptorRange_.BaseShaderRegister = 0; // テクスチャレジスタ0番
	initStatus.descriptorRange_.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	// テクスチャレジスタ
	D3D12_ROOT_PARAMETER rootParam{};
	rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParam.DescriptorTable.pDescriptorRanges = &initStatus.descriptorRange_;
	rootParam.DescriptorTable.NumDescriptorRanges = 1;
	rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // 全てのシェーダから見える

	initStatus.rootParams_.push_back(rootParam);

#pragma endregion


#pragma region パイプライン設定

	// シェーダーの設定
	initStatus.pipelineDesc_.VS.pShaderBytecode = shdrs.vsBlob_.Get()->GetBufferPointer();
	initStatus.pipelineDesc_.VS.BytecodeLength  = shdrs.vsBlob_.Get()->GetBufferSize();
	initStatus.pipelineDesc_.PS.pShaderBytecode = shdrs.psBlob_.Get()->GetBufferPointer();
	initStatus.pipelineDesc_.PS.BytecodeLength  = shdrs.psBlob_.Get()->GetBufferSize();

	// ラスタライザの設定
	initStatus.pipelineDesc_.RasterizerState.CullMode = D3D12_CULL_MODE_BACK; // 背面をカリング

	// デプスステンシルステートの設定
	initStatus.pipelineDesc_.DepthStencilState.DepthEnable = true; // 深度テスト
	initStatus.pipelineDesc_.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL; // 書き込み許可
	initStatus.pipelineDesc_.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS; // 小さければ合格
	initStatus.pipelineDesc_.DSVFormat = DXGI_FORMAT_D32_FLOAT; // 深度フォーマット

	// 図形の形状設定
	initStatus.pipelineDesc_.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

#pragma endregion


#pragma region プリミティブ形状の設定

	initStatus.primitive_ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST; // 三角形リスト

#pragma endregion


	// パイプライン初期化
	sPipelineSet_.Initialize(initStatus);

}

void Model::Pipeline::StaticSetDrawCommond()
{
	// パイプラインをセット
	sPipelineSet_.SetDrawCommand();
}

#pragma endregion
