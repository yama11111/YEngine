#pragma once
#include "Vertices.h"
#include "IShaderSet.h"
#include "PipelineSet.h"
#include "Texture.h"
#include "ObjectConfig.h"
#include "Transform.h"
#include "ViewProjection.h"
#include "CBColor.h"
#include "CBTexConfig.h"
#include <list>
#include <array>

namespace YGame
{

	// スプライト3Dクラス
	class Sprite3D
	{

	public:

		// オブジェクトクラス前方宣言
		class Object;

		// シェーダーの種類
		enum class ShaderType
		{
			eDefault = 0, // デフォルト
		};

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="pTex"> : テクスチャポインタ</param>
		/// <returns>スプライトポインタ</returns>
		static Sprite3D* Create(Texture* pTex);

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
		void SetDrawCommand(Sprite3D::Object* pObj, const DrawLocation& location, const ShaderType& shaderType = ShaderType::eDefault);

		/// <summary>
		/// 表示するか設定
		/// </summary>
		/// <param name="isVisible"> : 表示するか</param>
		void SetIsVisible(const bool isVisible);

	public:

		Sprite3D() = default;

		~Sprite3D() = default;

	public:

		// 頂点データ
		struct VData
		{
			YMath::Vector3 pos_; // xyz座標
		};

	private:

		// テクスチャ
		Texture* pTex_ = nullptr;

		// 表示するか
		bool isVisible_ = true;

	private:

		// 頂点データ
		static YDX::Vertices<VData> vt_;

		// 初期化フラグ
		static bool isInitVertices_;

		// 静的スプライト3D格納用vector配列
		static std::vector<std::unique_ptr<Sprite3D>> sSprites_;

	public:

		// パイプラインクラス前方宣言
		class Pipeline;

	};

#pragma region Object

	// スプライト3D用オブジェクトクラス
	class Sprite3D::Object : public Transform
	{

	public:

		/// <summary>
		/// 生成 + 初期化 (Transform以外は nullの時 デフォルトで初期化)
		/// </summary>
		/// <param name="status"> : 位置, 回転, 大きさ</param>
		/// <param name="isXAxisBillboard"> : X軸ビルボードか</param>
		/// <param name="isYAxisBillboard"> : Y軸ビルボードか</param>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		/// <param name="pColor"> : 色ポインタ</param>
		/// <param name="pTexConfig"> : テクスチャ設定ポインタ</param>
		/// <param name="isMutable"> : シーン遷移時に開放するか</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static Object* Create(
			const Status& status = Status::Default(),
			bool isXAxisBillboard = false, bool isYAxisBillboard = false,
			ViewProjection* pVP = nullptr,
			CBColor* pColor = nullptr, 
			CBTexConfig* pTexConfig = nullptr,
			const bool isMutable = true);

	public:

		/// <summary>
		/// 描画前コマンド
		/// </summary>
		/// <param name="transformRPIndex"></param>
		/// <param name="texConfigRPIndex"> : テクスチャ設定ルートパラメータ番号</param>
		void SetDrawCommand(
			const UINT transformRPIndex, 
			const UINT colorRPIndex,
			const UINT texConfigRPIndex);


		/// <summary>
		/// ビルボード設定
		/// </summary>
		/// <param name="isXAxisBillboard"> : X軸ビルボードか</param>
		/// <param name="isYAxisBillboard"> : Y軸ビルボードか</param>
		void SetIsBillboard(bool isXAxisBillboard, bool isYAxisBillboard);
		
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
			YMath::Matrix4 matWorld_; // 3D変換行列
			YMath::Matrix4 matBill_; // ビルボード行列
		};

	private:

		// 定数バッファ (行列)
		YDX::ConstBuffer<CBData> cBuff_;

		// X軸ビルボード
		bool isXAxisBillboard_ = false;

		// Y軸ビルボード
		bool isYAxisBillboard_ = false;

		// ビュープロジェクションポインタ
		ViewProjection* pVP_ = nullptr;

		// 色ポインタ
		CBColor* pColor_ = nullptr;

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
	class Sprite3D::Pipeline
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
		/// <param name="pSprite2D"> : スプライトポインタ</param>
		/// <param name="pObj"> : オブジェクトポインタ</param>
		/// <param name="locaiton"> : 描画場所</param>
		/// <param name="shaderType"> : シェーダー</param>
		static void StaticPushBackDrawSet(
			Sprite3D* pSprite3D, 
			Sprite3D::Object* pObj, 
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
			eTexConfigCB = 2, // テクスチャ設定
			eTexDT		 = 3, // テクスチャ
		};

	private:

		// シェーダーセット
		class ShaderSet : public YDX::IShaderSet
		{

		public:

			// DefaultVS
			Microsoft::WRL::ComPtr<ID3DBlob> defaultVSBlob_ = nullptr;

			// DefaultGS
			Microsoft::WRL::ComPtr<ID3DBlob> defaultGSBlob_ = nullptr;
			
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

			// スプライト3Dポインタ
			Sprite3D* pSprite3D_;

			// スプライト3D用オブジェクト
			Sprite3D::Object* pObj_;

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

}