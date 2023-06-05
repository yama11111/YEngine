#include "Model.h"
#include "CalcTransform.h"
#include "MathUtillity.h"
#include "FileUtillity.h"
#include <cassert>
#include <fstream>
#include <sstream>

#pragma region 名前空間

using std::array;
using std::vector;
using std::list;
using std::unique_ptr;
using YGame::Model;
using YDX::PipelineSet;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;
using YGame::DrawLocation;
using YGame::DrawLocationNum;

#pragma endregion

#pragma region ルートパラメータ番号

static const UINT TraIndex = static_cast<UINT>(Model::Pipeline::RootParameterIndex::eTransformCB); // transform
static const UINT ColIndex = static_cast<UINT>(Model::Pipeline::RootParameterIndex::eColorCB); // color
static const UINT MateIndex = static_cast<UINT>(Model::Pipeline::RootParameterIndex::eMaterialCB); // material
static const UINT LigIndex = static_cast<UINT>(Model::Pipeline::RootParameterIndex::eLightCB); // light
static const UINT TexConfigIndex = static_cast<UINT>(Model::Pipeline::RootParameterIndex::eTexConfigCB); // texConfig
static const UINT TexIndex = static_cast<UINT>(Model::Pipeline::RootParameterIndex::eTexDT); // tex

#pragma endregion

#pragma region Static

vector<unique_ptr<Model>> Model::sModels_{};
array<PipelineSet, Model::Pipeline::sShaderNum_> Model::Pipeline::sPipelineSets_{};
array<array<list<unique_ptr<Model::Pipeline::DrawSet>>, Model::Pipeline::sShaderNum_>, DrawLocationNum> Model::Pipeline::sDrawSets_;
FbxManager* Model::FbxLoader::sFbxMan_ = nullptr;
FbxImporter* Model::FbxLoader::sFbxImp_ = nullptr;

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
	sModels_.push_back(std::move(newModel));

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
	sModels_.push_back(std::move(newModel));

	// モデルポインタを返す
	return newModelPtr;
}

Model* Model::LoadObj(const std::string& modelFileName, const bool isSmoothing)
{
	// 読み込んだことがあるかチェック
	for (size_t i = 0; i < sModels_.size(); i++)
	{
		// ファイルパス が同じなら
		if (modelFileName == sModels_[i]->fileName_)
		{
			// そのテクスチャポインタを返す
			return sModels_[i].get();
		}
	}

	// モデル生成
	unique_ptr<Model> newModel = std::make_unique<Model>();


	// メッシュ生成
	std::unique_ptr<Mesh> newMesh;
	
	// ディレクトリパス (モデルのファイル名と同じフォルダから)
	std::string directoryPath = "Resources/Models/" + modelFileName + "/";
	
	// FBXファイル名
	std::string objFileName = modelFileName + ".obj";
	objFileName = YUtil::FilePath(objFileName);
	

	// メッシュロード
	newMesh.reset(Mesh::LoadObj(directoryPath, objFileName, isSmoothing));

	// 追加
	newModel->meshes_.push_back(std::move(newMesh));

	// ファイル名代入
	newModel->fileName_ = modelFileName;


	// ポインタを獲得
	Model* newModelPtr = newModel.get();

	// モデルを保存
	sModels_.push_back(std::move(newModel));

	// モデルポインタを返す
	return newModelPtr;
}

Model* Model::LoadFbx(const std::string& modelFileName, const bool isSmoothing)
{
	// 読み込んだことがあるかチェック
	for (size_t i = 0; i < sModels_.size(); i++)
	{
		// ファイルパス が同じなら
		if (modelFileName == sModels_[i]->fileName_)
		{
			// そのテクスチャポインタを返す
			return sModels_[i].get();
		}
	}

	// モデル生成
	unique_ptr<Model> newModel = std::make_unique<Model>();


	// メッシュ生成
	std::unique_ptr<Mesh> newMesh;

	// ディレクトリパス (モデルのファイル名と同じフォルダから)
	std::string directoryPath = "Resources/Models/" + modelFileName + "/";

	// FBXファイル名
	std::string fbxFileName = modelFileName + ".fbx";

	//フルパス
	std::string fullPath = directoryPath + fbxFileName;

	// ファイル名代入
	newModel->fileName_ = modelFileName;

	// ファイル名を指定してFBXファイル読み込み
	assert(FbxLoader::sFbxImp_->Initialize(fullPath.c_str(), -1, FbxLoader::sFbxMan_->GetIOSettings()));


	// シーン生成
	FbxScene* fbxScene = FbxScene::Create(FbxLoader::sFbxMan_, "fbxScene");

	// ファイルからロードしたFBX情報をインポート
	FbxLoader::sFbxImp_->Import(fbxScene);


	// FBXノードの数
	int nodeCount = fbxScene->GetNodeCount();

	// 必要分のメモリ確保 (アドレスのずれを予防)
	newModel->nodes_.reserve(nodeCount);

	// ルートノードから順に解析してモデルに流し込む
	FbxLoader::ParseNodeRecursive(newModel.get(), fbxScene->GetRootNode(), isSmoothing);


	// FBXシーン開放
	fbxScene->Destroy();


	// ポインタを獲得
	Model* newModelPtr = newModel.get();

	// モデルを保存
	sModels_.push_back(std::move(newModel));

	// モデルポインタを返す
	return newModelPtr;
}

void Model::AllClear()
{
	// モデル全消去
	for (size_t i = 0; i < sModels_.size(); i++)
	{
		sModels_[i].reset(nullptr);
	}
	sModels_.clear();
}

void Model::SetDrawCommand(Object* pObj, const DrawLocation& location, const ShaderType& shaderType)
{
	// 描画セット挿入
	Pipeline::StaticPushBackDrawSet(this, pObj, location, shaderType);
}

void Model::SetIsVisible(const bool isVisible)
{
	isVisible_ = isVisible;
}

#pragma endregion


#pragma region FbxLoader

void Model::FbxLoader::StaticInitialize()
{
	// 再初期化チェック
	assert(sFbxMan_ == nullptr);

	// FBXマネージャーの生成
	sFbxMan_ = FbxManager::Create();

	// FBXマネージャーの入出力設定
	FbxIOSettings* ios = FbxIOSettings::Create(sFbxMan_, IOSROOT);
	sFbxMan_->SetIOSettings(ios);

	// FBXインポーターの生成
	sFbxImp_ = FbxImporter::Create(sFbxMan_, "");
}

void Model::FbxLoader::StaticFinalize()
{
	// 各種FBXインスタンス破棄
	sFbxImp_->Destroy();
	sFbxMan_->Destroy();
}

void Model::FbxLoader::ParseNodeRecursive(Model* pModel, FbxNode* fbxNode, const bool isSmoothing, Node* parent)
{
	// ノード生成
	std::unique_ptr<Node> newNode = std::make_unique<Node>();


	// ノード名
	newNode->name_ = fbxNode->GetName();


	// FBXノードのローカル情報
	FbxDouble3 fbxPos = fbxNode->LclTranslation.Get();
	FbxDouble3 fbxRot = fbxNode->LclRotation.Get();
	FbxDouble3 fbxScale = fbxNode->LclScaling.Get();

	// 変換
	Vector3 pos = { static_cast<float>(fbxPos[0]), static_cast<float>(fbxPos[1]), static_cast<float>(fbxPos[2]) };
	Vector3 rot = { static_cast<float>(fbxRot[0]), static_cast<float>(fbxRot[1]), static_cast<float>(fbxRot[2]) };
	Vector3 scale = { static_cast<float>(fbxScale[0]), static_cast<float>(fbxScale[1]), static_cast<float>(fbxScale[2]) };

	// 回転角を Degree -> Radianに
	rot.x_ = YMath::ConvertFromDegreeToRadian(rot.x_);
	rot.y_ = YMath::ConvertFromDegreeToRadian(rot.y_);
	rot.z_ = YMath::ConvertFromDegreeToRadian(rot.z_);

	// ローカルトランスフォーム初期化
	newNode->local_.Initialize({ pos, rot, scale });

	// グローバル変形行列の計算
	newNode->globalMat_ = newNode->local_.m_;

	// 親があるなら
	if (parent)
	{
		// 代入
		newNode->parent_ = parent;

		// 親行列を乗算
		newNode->globalMat_ *= parent->globalMat_;
	}

	// ポインタ取得
	Node* pNewNode = newNode.get();

	// ノード配列に追加
	pModel->nodes_.push_back(std::move(newNode));


	// FBXノードのメッシュ情報を解析
	FbxNodeAttribute* fbxNodeAttribute = fbxNode->GetNodeAttribute();

	// メッシュ情報があるなら
	if (fbxNodeAttribute)
	{
		// メッシュなら
		if (fbxNodeAttribute->GetAttributeType() == FbxNodeAttribute::EType::eMesh)
		{
			// メッシュ生成
			std::unique_ptr<Mesh> newMesh;
			
			// メッシュロード
			newMesh.reset(Mesh::LoadFbx("Resources/Models/" + pModel->fileName_ + "/", fbxNode, isSmoothing));

			// 追加
			pModel->meshes_.push_back(std::move(newMesh));
		}
	}


	// 子ノードに対して再帰呼び出し
	for (int i = 0; i < fbxNode->GetChildCount(); i++)
	{
		ParseNodeRecursive(pModel, fbxNode->GetChild(i), isSmoothing, pNewNode);
	}
}

#pragma endregion


#pragma region Object

Model::Object* Model::Object::Create(
	const Status& status,
	ViewProjection* pVP,
	CBColor* pColor,
	CBMaterial* pMaterial,
	CBLightGroup* pLightGroup,
	CBTexConfig* pTexConfig,
	const bool isMutable)
{
	// インスタンス生成 (動的)
	Object* instance = new Object();

	// 定数バッファ生成
	instance->cBuff_.Create(isMutable);

	// 初期化(デフォルト)
	instance->Initialize(status);
	instance->SetViewProjection(pVP);
	instance->SetMaterial(pMaterial);
	instance->SetColor(pColor);
	instance->SetLightGroup(pLightGroup);
	instance->SetTexConfig(pTexConfig);

	// インスタンスを返す
	return instance;
}

void Model::Object::SetDrawCommand(
	const UINT transformRPIndex,
	const UINT colorRPIndex,
	const UINT materialRPIndex, 
	const UINT lightRPIndex,
	const UINT texConfigRPIndex)
{
	// 行列
	cBuff_.map_->matWorld_ = m_;
	cBuff_.map_->matViewProj_ = pVP_->view_ * pVP_->pro_;
	cBuff_.map_->cameraPos_ = pVP_->eye_;
	cBuff_.SetDrawCommand(transformRPIndex);

	// 色
	pColor_->SetDrawCommand(colorRPIndex);

	// マテリアル
	pMaterial_->SetDrawCommand(materialRPIndex);

	// 光
	pLightGroup_->SetDrawCommand(lightRPIndex);

	// テクスチャ設定
	pTexConfig_->SetDrawCommand(texConfigRPIndex);
}

void Model::Object::SetViewProjection(ViewProjection* pVP)
{
	// nullなら
	if (pVP == nullptr)
	{
		// デフォルト代入
		pVP_ = Default::sVP_.get();
		return;
	}

	// 代入
	pVP_ = pVP;
}

void Model::Object::SetColor(CBColor* pColor)
{
	// nullなら
	if (pColor == nullptr)
	{
		// デフォルト代入
		pColor_ = Default::sColor_.get();
		return;
	}

	// 代入
	pColor_ = pColor;
}

void Model::Object::SetMaterial(CBMaterial* pMaterial)
{
	// nullなら
	if (pMaterial == nullptr)
	{
		// デフォルト代入
		pMaterial_ = Default::sMaterial_.get();
		return;
	}

	// 代入
	pMaterial_ = pMaterial;
}

void Model::Object::SetLightGroup(CBLightGroup* pLightGroup)
{
	// nullなら
	if (pLightGroup == nullptr)
	{
		// デフォルト代入
		pLightGroup_ = Default::sLightGroup_.get();
		return;
	}

	// 代入
	pLightGroup_ = pLightGroup;
}

void Model::Object::SetTexConfig(CBTexConfig* pTexConfig)
{
	// nullなら
	if (pTexConfig == nullptr)
	{
		// デフォルト代入
		pTexConfig_ = Default::sTexConfig_.get();
		return;
	}

	// 代入
	pTexConfig_ = pTexConfig;
}

unique_ptr<YGame::ViewProjection> Model::Object::Default::sVP_ = nullptr;
unique_ptr<YGame::CBColor> Model::Object::Default::sColor_ = nullptr;
unique_ptr<YGame::CBMaterial> Model::Object::Default::sMaterial_ = nullptr;
unique_ptr<YGame::CBLightGroup> Model::Object::Default::sLightGroup_ = nullptr;
unique_ptr<YGame::CBTexConfig> Model::Object::Default::sTexConfig_ = nullptr;

void Model::Object::Default::StaticInitialize()
{
	// 生成 + 初期化 (ビュープロジェクションポインタ)
	sVP_.reset(new YGame::ViewProjection());
	sVP_->Initialize();

	// 生成 + 初期化 (色)
	sColor_.reset(CBColor::Create({ 1.0f,1.0f,1.0f,1.0f }, { 1.0f,1.0f,1.0f,1.0f }, false));

	// 生成 + 初期化 (マテリアル)
	sMaterial_.reset(CBMaterial::Create({ 1.0f,1.0f,1.0f }, { 1.0f,1.0f,1.0f }, { 1.0f,1.0f,1.0f }, 1.0f, false));

	// 生成 + 初期化 (光源ポインタ)
	sLightGroup_.reset(CBLightGroup::Create({ 1.0f,1.0f,1.0f }, false));

	// 生成 + 初期化 (テクスチャ設定)
	sTexConfig_.reset(CBTexConfig::Create({ 1.0f,1.0f }, {}, false));
}

#pragma endregion


#pragma region シェーダー番号

static const UINT DefaultIndex	 = static_cast<UINT>(Model::ShaderType::eDefault);
static const UINT PhongIndex	 = static_cast<UINT>(Model::ShaderType::ePhong);
static const UINT ToonIndex		 = static_cast<UINT>(Model::ShaderType::eToon);

#pragma endregion


#pragma region Pipeline

void Model::Pipeline::ShaderSet::Load()
{

	// エラーオブジェクト
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

	// Default
	{
		ID3DBlob* vs = nullptr;
		ID3DBlob* ps = nullptr;

		// 頂点シェーダの読み込みとコンパイル
		LoadShader(L"Resources/Shaders/ModelVS.hlsl", "main", "vs_5_0", vs, errorBlob.Get());
		// ピクセルシェーダの読み込みとコンパイル
		LoadShader(L"Resources/Shaders/ModelPS.hlsl", "main", "ps_5_0", ps, errorBlob.Get());

		defaultVSBlob_ = vs;
		defaultPSBlob_ = ps;
	}

	// phong
	{
		ID3DBlob* ps = nullptr;

		// ピクセルシェーダの読み込みとコンパイル
		LoadShader(L"Resources/Shaders/PhongPS.hlsl", "main", "ps_5_0", ps, errorBlob.Get());

		phongPSBlob_ = ps;
	}

	// toon
	{
		ID3DBlob* ps = nullptr;

		// ピクセルシェーダの読み込みとコンパイル
		LoadShader(L"Resources/Shaders/ToonPS.hlsl", "main", "ps_5_0", ps, errorBlob.Get());

		toonPSBlob_ = ps;
	}

}

void Model::Pipeline::StaticInitialize()
{

#pragma region シェーダー読み込み

	// シェーダー
	ShaderSet shdrs;
	
	// 読み込み
	shdrs.Load();

#pragma endregion


#pragma region 頂点レイアウトの設定


	// 頂点レイアウト
	std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout =
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

	// テクスチャサンプラー配列
	std::vector<D3D12_STATIC_SAMPLER_DESC> samplerDescs;

	// テクスチャサンプラーの設定
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

	// テクスチャサンプラー配列に挿入
	samplerDescs.push_back(samplerDesc);

#pragma endregion


#pragma region ルートパラメータの設定

	// ルートパラメータ
	std::vector<D3D12_ROOT_PARAMETER> rootParams;

	// 定数バッファの数
	size_t rpIdxCBNum = static_cast<size_t> (RootParameterIndex::eTexDT);

	// 定数バッファの数だけ
	for (size_t i = 0; i < rpIdxCBNum; i++)
	{
		// 定数バッファ
		D3D12_ROOT_PARAMETER rootParam{};
		rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;  // 定数バッファビュー
		rootParam.Descriptor.ShaderRegister = static_cast<UINT>(i); // 定数バッファ番号
		rootParam.Descriptor.RegisterSpace = 0;					  // デフォルト値
		rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // 全てのシェーダから見える

		// 配列に挿入
		rootParams.push_back(rootParam);
	}

	// デスクリプタレンジの設定
	D3D12_DESCRIPTOR_RANGE descriptorRange{};
	descriptorRange.NumDescriptors = 1; // 1度の描画に使うテクスチャが1枚なので1
	descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange.BaseShaderRegister = 0; // テクスチャレジスタ0番
	descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	// テクスチャレジスタ
	D3D12_ROOT_PARAMETER rootParam{};
	rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParam.DescriptorTable.pDescriptorRanges = &descriptorRange;
	rootParam.DescriptorTable.NumDescriptorRanges = 1;
	rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // 全てのシェーダから見える

	// 配列に挿入
	rootParams.push_back(rootParam);

#pragma endregion


#pragma region パイプライン設定

	// パイプライン設定
	std::array<D3D12_GRAPHICS_PIPELINE_STATE_DESC, sPipelineSets_.size()> pipelineDescs{};

	// シェーダーの設定
	pipelineDescs[DefaultIndex].VS.pShaderBytecode	 = shdrs.defaultVSBlob_.Get()->GetBufferPointer();
	pipelineDescs[DefaultIndex].VS.BytecodeLength	 = shdrs.defaultVSBlob_.Get()->GetBufferSize();
	pipelineDescs[DefaultIndex].PS.pShaderBytecode	 = shdrs.defaultPSBlob_.Get()->GetBufferPointer();
	pipelineDescs[DefaultIndex].PS.BytecodeLength	 = shdrs.defaultPSBlob_.Get()->GetBufferSize();

	pipelineDescs[PhongIndex].VS.pShaderBytecode	 = shdrs.defaultVSBlob_.Get()->GetBufferPointer();
	pipelineDescs[PhongIndex].VS.BytecodeLength		 = shdrs.defaultVSBlob_.Get()->GetBufferSize();
	pipelineDescs[PhongIndex].PS.pShaderBytecode	 = shdrs.phongPSBlob_.Get()->GetBufferPointer();
	pipelineDescs[PhongIndex].PS.BytecodeLength		 = shdrs.phongPSBlob_.Get()->GetBufferSize();

	pipelineDescs[ToonIndex].VS.pShaderBytecode		 = shdrs.defaultVSBlob_.Get()->GetBufferPointer();
	pipelineDescs[ToonIndex].VS.BytecodeLength		 = shdrs.defaultVSBlob_.Get()->GetBufferSize();
	pipelineDescs[ToonIndex].PS.pShaderBytecode		 = shdrs.toonPSBlob_.Get()->GetBufferPointer();
	pipelineDescs[ToonIndex].PS.BytecodeLength		 = shdrs.toonPSBlob_.Get()->GetBufferSize();

	// パイプラインの数だけ
	for (size_t i = 0; i < sPipelineSets_.size(); i++)
	{
		// サンプルマスクの設定
		pipelineDescs[i].SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定

		// ラスタライザの設定
		pipelineDescs[i].RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // ポリゴン内塗りつぶし
		pipelineDescs[i].RasterizerState.DepthClipEnable = true; // 深度クリッピングを有効に
		pipelineDescs[i].RasterizerState.CullMode = D3D12_CULL_MODE_BACK; // 背面をカリング

		// デプスステンシルステートの設定
		pipelineDescs[i].DepthStencilState.DepthEnable = true; // 深度テスト
		pipelineDescs[i].DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL; // 書き込み許可
		pipelineDescs[i].DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS; // 小さければ合格
		pipelineDescs[i].DSVFormat = DXGI_FORMAT_D32_FLOAT; // 深度フォーマット

		// ブレンドステート
		D3D12_RENDER_TARGET_BLEND_DESC& blendDesc = pipelineDescs[i].BlendState.RenderTarget[0];
		blendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // RBGA全てのチャンネルを描画

		blendDesc.BlendEnable = true;                // ブレンドを有効にする
		blendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD; // 加算
		blendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;   // ソースの値を100%使う
		blendDesc.DestBlendAlpha = D3D12_BLEND_ZERO; // デストの値を  0%使う

		// 半透明合成
		blendDesc.BlendOp = D3D12_BLEND_OP_ADD;			 // 加算
		blendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;      // ソースのアルファ値
		blendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA; // 1.0f - ソースのアルファ値

		// 図形の形状設定
		pipelineDescs[i].PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

		// 頂点レイアウトの設定
		pipelineDescs[i].InputLayout.pInputElementDescs = inputLayout.data(); // 頂点レイアウトの先頭アドレス
		pipelineDescs[i].InputLayout.NumElements = (UINT)inputLayout.size(); // 頂点レイアウト数

		// その他の設定
		pipelineDescs[i].NumRenderTargets = 1; // 描画対象は1つ
		pipelineDescs[i].RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0~255指定のRGBA
		pipelineDescs[i].SampleDesc.Count = 1; // 1ピクセルにつき1回サンプリング
	}

#pragma endregion


#pragma region プリミティブ形状の設定

	// プリミティブ形状
	D3D_PRIMITIVE_TOPOLOGY primitive = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST; // 三角形リスト

#pragma endregion


	// パイプラインの数だけ
	for (size_t i = 0; i < sPipelineSets_.size(); i++)
	{
		// パイプライン初期化
		sPipelineSets_[i].Initialize(samplerDescs, rootParams, pipelineDescs[i], primitive);
	}

	// 描画場所の数だけ
	for (size_t i = 0; i < sDrawSets_.size(); i++)
	{
		// 変換
		DrawLocation location = static_cast<DrawLocation>(i);

		// クリア
		StaticClearDrawSet(location);
	}
}

void Model::Pipeline::StaticClearDrawSet(const DrawLocation& location)
{
	// インデックスに変換
	size_t index = static_cast<size_t>(location);

	// パイプラインの数だけ
	for (size_t i = 0; i < sPipelineSets_.size(); i++)
	{
		// あるなら
		if (sDrawSets_[index][i].empty() == false)
		{
			// クリア
			sDrawSets_[index][i].clear();
		}
	}
}

void Model::Pipeline::StaticPushBackDrawSet(
	Model* pModel, Model::Object* pObj, 
	const DrawLocation& location, const ShaderType& shaderType)
{
	// 描画セット生成
	unique_ptr<Pipeline::DrawSet> newDrawSet = std::make_unique<Pipeline::DrawSet>();

	// 初期化
	newDrawSet->pModel_ = pModel;
	newDrawSet->pObj_ = pObj;
	
	// インデックスに変換
	size_t locationIdx = static_cast<size_t>(location);

	// インデックスに変換
	size_t shaderIdx = static_cast<size_t>(shaderType);

	// 挿入
	sDrawSets_[locationIdx][shaderIdx].push_back(std::move(newDrawSet));
}

void Model::Pipeline::StaticDraw(const DrawLocation& location)
{
	// インデックスに変換
	size_t index = static_cast<size_t>(location);

	// パイプラインの数だけ
	for (size_t i = 0; i < sPipelineSets_.size(); i++)
	{
		// パイプラインをセット
		sPipelineSets_[i].SetDrawCommand();

		// モデル描画
		for (std::unique_ptr<DrawSet>& drawSet : sDrawSets_[index][i])
		{
			// 描画
			drawSet->Draw();
		}
	}
}

void Model::Pipeline::DrawSet::Draw()
{
	// 描画しないなら弾く
	if (pModel_->isVisible_ == false) { return; }

	// 定数バッファをシェーダーに送る
	pObj_->SetDrawCommand(TraIndex, ColIndex, MateIndex, LigIndex, TexConfigIndex);

	// メッシュ毎に違うバッファ
	for (size_t i = 0; i < pModel_->meshes_.size(); i++)
	{
		// 描画
		pModel_->meshes_[i]->Draw(TexIndex);
	}
}

#pragma endregion


