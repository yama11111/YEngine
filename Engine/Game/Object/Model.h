#pragma once
#include "Mesh.h"
#include "IShaderSet.h"
#include "PipelineSet.h"
#include "ObjectConfig.h"
#include "ViewProjection.h"
#include "CBColor.h"
#include "CBLightGroup.h"
#include "CBMaterial.h"
#include "CBTexConfig.h"

namespace YGame
{
	// モデルクラス
	class Model
	{
	
	public:

		// オブジェクトクラス前方宣言
		class Object;

		// シェーダーの種類
		enum class ShaderType
		{
			ePhong	 = 0, // Phong
			eToon	 = 1, // Toon
			eDefault = 2, // デフォルト
		};

	public:

		/// <summary>
		/// 生成(立方体)
		/// </summary>
		/// <returns>モデルポインタ</returns>
		static Model* CreateCube();

		/// <summary>
		/// 生成(立方体)
		/// </summary>
		/// <param name="texFileName"> : 画像のファイル名</param>
		/// <returns>モデルポインタ</returns>
		static Model* CreateCube(const std::string& texFileName);

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

	public:

		/// <summary>
		/// 描画コマンド
		/// </summary>
		/// <param name="pObj"> : オブジェクトポインタ</param>
		/// <param name="locaiton"> : 描画場所</param>
		/// <param name="shaderType"> : シェーダー</param>
		void SetDrawCommand(
			Model::Object* pObj, 
			const DrawLocation& location, 
			const ShaderType& shaderType = ShaderType::eDefault);

		/// <summary>
		/// 表示するか設定
		/// </summary>
		/// <param name="isVisible"> : 表示するか</param>
		void SetIsVisible(const bool isVisible);

	public:

		Model() = default;

		~Model() = default;

	private:

		// メッシュ配列
		std::vector<std::unique_ptr<Mesh>> meshes_;

		// ノード配列
		std::vector<std::unique_ptr<Node>> nodes_;

		// 表示するか
		bool isVisible_ = true;

		// ファイルパス
		std::string fileName_;

	private:

		// 静的モデル格納用vector配列
		static std::vector<std::unique_ptr<Model>> sModels_;
	
	public:

		// パイプラインクラス前方宣言
		class Pipeline;

		// FBX読み込みクラス前方宣言
		class FbxLoader;

	};


#pragma region Object

	// モデル用オブジェクトクラス
	class Model::Object : public Transform
	{

	public:

		/// <summary>
		/// 生成 + 初期化 (Transform以外は nullの時 デフォルトで初期化)
		/// </summary>
		/// <param name="status"> : 位置, 回転, 大きさ</param>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		/// <param name="pColor"> : 色ポインタ</param>
		/// <param name="pMaterial"> : マテリアルポインタ</param>
		/// <param name="pLightGroup"> : 光源ポインタ</param>
		/// <param name="pTexConfig"> : テクスチャ設定ポインタ</param>
		/// <param name="isMutable"> : シーン遷移時に開放するか</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static Object* Create(
			const Status& status = Status::Default(),
			ViewProjection* pVP = nullptr,
			CBColor* pColor = nullptr,
			CBMaterial* pMaterial = nullptr,
			CBLightGroup* pLightGroup = nullptr,
			CBTexConfig* pTexConfig = nullptr,
			const bool isMutable = true);

	public:

		/// <summary>
		/// 描画前コマンド
		/// </summary>
		/// <param name="transformRPIndex"> : トランスフォームルートパラメータ番号</param>
		/// <param name="colorRPIndex"> : 色ルートパラメータ番号</param>
		/// <param name="materialRPIndex"> : マテリアルルートパラメータ番号</param>
		/// <param name="lightRPIndex"> : ライトグループルートパラメータ番号</param>
		/// <param name="texConfigRPIndex"> : テクスチャ設定ルートパラメータ番号</param>
		void SetDrawCommand(
			const UINT transformRPIndex,
			const UINT colorRPIndex,
			const UINT materialRPIndex,
			const UINT lightRPIndex,
			const UINT texConfigRPIndex);


		/// <summary>
		/// ビュープロジェクション設定 (null = Default)
		/// </summary>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		void SetViewProjection(ViewProjection* pVP);

		/// <summary>
		/// 色設定 (null = Default)
		/// </summary>
		/// <param name="pColor"> : 色ポインタ</param>
		void SetColor(CBColor* pColor);

		/// <summary>
		/// マテリアル設定 (null = Default)
		/// </summary>
		/// <param name="pMaterial"> : マテリアルポインタ</param>
		void SetMaterial(CBMaterial* pMaterial);

		/// <summary>
		/// 光源設定 (null = Default)
		/// </summary>
		/// <param name="pLightGroup"> : 光源ポインタ</param>
		void SetLightGroup(CBLightGroup* pLightGroup);

		/// <summary>
		/// テクスチャ設定 (null = Default)
		/// </summary>
		/// <param name="pTexConfig"> : テクスチャ設定ポインタ</param>
		void SetTexConfig(CBTexConfig* pTexConfig);

	private:

		Object() = default;

	public:

		~Object() = default;


	private:

		// 定数バッファデータ構造体
		struct CBData
		{
			YMath::Matrix4 matWorld_;	 // ワールド行列
			YMath::Matrix4 matViewProj_; // ビュープロジェクション行列
			YMath::Vector3 cameraPos_;	 // カメラ座標
			float pad_;
		};

	private:

		// 定数バッファ
		YDX::ConstBuffer<CBData> cBuff_;

		// ビュープロジェクションポインタ
		ViewProjection* pVP_ = nullptr;

		// 色ポインタ
		CBColor* pColor_ = nullptr;

		// マテリアルポインタ
		CBMaterial* pMaterial_ = nullptr;

		// 光源ポインタ
		CBLightGroup* pLightGroup_ = nullptr;

		// テクスチャ設定ポインタ
		CBTexConfig* pTexConfig_ = nullptr;

	public:

		// 既定値クラス
		class Default
		{

		public:

			// ビュープロジェクションポインタ (デフォルト)
			static std::unique_ptr<ViewProjection> sVP_;

			// 色 (デフォルト)
			static std::unique_ptr<CBColor> sColor_;

			// マテリアル (デフォルト)
			static std::unique_ptr<CBMaterial> sMaterial_;

			// 光源ポインタ (デフォルト)
			static std::unique_ptr<CBLightGroup> sLightGroup_;

			// テクスチャ設定 (デフォルト)
			static std::unique_ptr<CBTexConfig> sTexConfig_;

		public:

			/// <summary>
			/// 静的初期化
			/// </summary>
			static void StaticInitialize();

		};

	};

#pragma endregion


#pragma region Pipeline

	// パイプラインクラス
	class Model::Pipeline
	{

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void StaticInitialize();

		/// <summary>
		/// 静的描画リストクリア
		/// </summary>
		/// <param name="locaiton"> : 描画場所</param>
		static void StaticClearDrawSet(const DrawLocation& location);

		/// <summary>
		/// 静的描画セット挿入
		/// </summary>
		/// <param name="pModel"> : モデルポインタ</param>
		/// <param name="pObj"> : オブジェクトポインタ</param>
		/// <param name="locaiton"> : 描画場所</param>
		static void StaticPushBackDrawSet(
			Model* pModel, 
			Model::Object* pObj, 
			const DrawLocation& location, 
			const ShaderType& shaderType);

		/// <summary>
		/// 静的描画
		/// </summary>
		/// <param name="locaiton"> : 描画場所</param>
		static void StaticDraw(const DrawLocation& location);

	public:

		// ルートパラメータ番号
		enum class RootParameterIndex
		{
			eTransformCB = 0, // 行列
			eColorCB	 = 1, // 色
			eMaterialCB	 = 2, // マテリアル
			eLightCB	 = 3, // 光
			eTexConfigCB = 4, // テクスチャ設定
			eTexDT		 = 5, // テクスチャ
		};

	private:

		// シェーダーセット
		class ShaderSet : public YDX::IShaderSet
		{

		public:

			// PhongVS
			Microsoft::WRL::ComPtr<ID3DBlob> phongVSBlob_ = nullptr;

			// PhongPS
			Microsoft::WRL::ComPtr<ID3DBlob> phongPSBlob_ = nullptr;


			// ToonVS
			Microsoft::WRL::ComPtr<ID3DBlob> toonVSBlob_ = nullptr;

			// ToonPS
			Microsoft::WRL::ComPtr<ID3DBlob> toonPSBlob_ = nullptr;


			// DefaultVS
			Microsoft::WRL::ComPtr<ID3DBlob> defaultVSBlob_ = nullptr;

			// DefaultPS
			Microsoft::WRL::ComPtr<ID3DBlob> defaultPSBlob_ = nullptr;

		public:

			/// <summary>
			/// シェーダーファイル読み込み
			/// </summary>
			void Load() override;

		};

	public:

		// 描画セット
		struct DrawSet
		{

		public:

			// モデルポインタ
			Model* pModel_;

			// モデル用オブジェクト
			Model::Object* pObj_;

		public:

			/// <summary> 
			/// 描画
			/// </summary>
			void Draw();

		};

	private:

		// シェーダーの数
		static const size_t sShaderNum_ = static_cast<size_t>(ShaderType::eDefault) + 1;

		// パイプライン設定
		static std::array<YDX::PipelineSet, sShaderNum_> sPipelineSets_;

		// 描画用リスト配列
		static std::array<std::array<std::list<std::unique_ptr<DrawSet>>, sShaderNum_>, DrawLocationNum> sDrawSets_;

	};

#pragma endregion


#pragma region FbxLoader

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

#pragma endregion

}
