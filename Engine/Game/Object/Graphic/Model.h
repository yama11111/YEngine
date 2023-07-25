#pragma once
#include "BaseGraphic.h"
#include "Mesh.h"
#include "PipelineSetting.h"

namespace YGame
{
	// モデル
	class Model :
		public BaseGraphic
	{

	public:

		/// <summary>
		/// 生成(立方体)
		/// </summary>
		/// <param name="pTexs"> : テクスチャポインタ配列</param>
		/// <returns>モデルポインタ</returns>
		static Model* CreateCube(const std::unordered_map<std::string, Texture*>& pTexs);

		/// <summary>
		/// モデル(.obj)読み込み
		/// </summary>
		/// <param name="modelFileName"> : モデルのフォルダ名 (objと同じ名前の時のみ) </param>
		/// <param name="isSmoothing"> : スムーシングするか</param>
		/// <returns>モデルポインタ</returns>
		static Model* LoadObj(const std::string& modelFileName, const bool isSmoothing);

		/// <summary>
		/// モデル(.obj)読み込み
		/// </summary>
		/// <param name="modelFileName"> : モデルのフォルダ名 (objと同じ名前の時のみ) </param>
		/// <param name="isSmoothing"> : スムーシングするか</param>
		/// <returns>モデルポインタ</returns>
		static Model* LoadFbx(const std::string& modelFileName, const bool isSmoothing);

		/// <summary>
		/// 全削除
		/// </summary>
		static void AllClear();

		/// <summary>
		/// モデル用のパイプライン設定取得
		/// </summary>
		/// <returns>パイプライン設定</returns>
		static PipelineSetting GetPipelineSetting();

	public:

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="rpIndices"> : ルートパラメータ情報 + 番号</param>
		void SetDrawCommand(std::unordered_map<std::string, uint32_t>& rpIndices) override;

	public:

		Model() = default;

		~Model() = default;

	private:

		// メッシュ配列
		std::vector<std::unique_ptr<Mesh>> meshes_;

		// ノード配列
		std::vector<std::unique_ptr<Node>> nodes_;
	
	private:

		// 静的モデル格納用vector配列
		static std::vector<std::unique_ptr<Model>> sModels_;
	
	public:

		// FBX読み込みクラス前方宣言
		class FbxLoader;
	};

	// FBX読み込みクラス
	class Model::FbxLoader
	{

	public:

		// 静的FBXマネージャー
		static FbxManager* sFbxMan_;

		// 静的FBXインポーター
		static FbxImporter* sFbxImp_;

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void StaticInitialize();

		/// <summary>
		/// 静的終了処理
		/// </summary>
		static void StaticFinalize();

	public:

		/// <summary>
		/// 再帰的にノード構成を解析
		/// </summary>
		/// <param name="pModel"> : モデルポインタ</param>
		/// <param name="fbxNode"> : 解析するノード</param>
		/// <param name="isSmoothing"> : スムーシングするか</param>
		/// <param name="parent"> : 親ノード</param>
		static void ParseNodeRecursive(Model* pModel, FbxNode* fbxNode, const bool isSmoothing, Node* parent = nullptr);

	};
}
