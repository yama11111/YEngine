#include "Model.h"
#include "GraphicType.h"
#include "MathVector.h"
#include "MathUtil.h"
#include "FileUtil.h"
#include <cassert>
#include <fstream>
#include <sstream>

using std::array;
using std::vector;
using std::list;
using std::unique_ptr;
using YGame::Model;
using YGame::PipelineSetting;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;

vector<unique_ptr<Model>> Model::sModels_{};
FbxManager* Model::FbxLoader::sFbxMan_ = nullptr;
FbxImporter* Model::FbxLoader::sFbxImp_ = nullptr;

Model::Model() :
	BaseGraphic(GraphicType::kModelTag), meshes_(), nodes_()
{
}

Model* Model::CreateCube(const std::unordered_map<std::string, Texture*>& pTexs)
{
	// モデル生成
	unique_ptr<Model> newModel = std::make_unique<Model>();


	// メッシュ生成
	std::unique_ptr<Mesh> newMesh;

	// メッシュロード
	newMesh.reset(Mesh::CreateCube(pTexs));

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
	objFileName = YFile::FilePath(objFileName);


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

void Model::SetDrawCommand(std::unordered_map<std::string, uint32_t>& rpIndices)
{
	if (isVisible_ == false) { return; }
	
	// メッシュ毎に違うバッファで描画
	for (size_t i = 0; i < meshes_.size(); i++)
	{
		meshes_[i]->SetDrawCommand(rpIndices);
	}
}

PipelineSetting Model::GetPipelineSetting()
{
	PipelineSetting result;

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

	result.inputLayout = inputLayout;
	
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
	result.samplerDescs.emplace_back(samplerDesc);
	
	result.fillMode = D3D12_FILL_MODE_SOLID; // ポリゴン内塗りつぶし

	result.cullMode = D3D12_CULL_MODE_BACK; // 背面をカリング
	
	result.depthEnable = true; // 深度テストを行う

	result.primitiveType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE; // 三角形

	result.primitive = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST; // 三角形リスト

	return result;
}


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
	rot.x = YMath::ConvertFromDegreeToRadian(rot.x);
	rot.y = YMath::ConvertFromDegreeToRadian(rot.y);
	rot.z = YMath::ConvertFromDegreeToRadian(rot.z);

	// ローカルトランスフォーム初期化
	newNode->local_.Initialize({ pos, rot, scale });

	// グローバル変形行列の計算
	newNode->globalMat_ = newNode->local_.m;

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
