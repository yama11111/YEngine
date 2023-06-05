#pragma once
#include "Vertices.h"
#include "IShaderSet.h"
#include "PipelineSet.h"
#include "Texture.h"
#include "ObjectConfig.h"
#include "Transform.h"
#include "CBColor.h"
#include "CBTexConfig.h"
#include <list>
#include <array>

namespace YGame
{
	// スプライト2Dクラス
	class Sprite2D
	{

	public:

		// オブジェクトクラス前方宣言
		class Object;

		// シェーダーの種類
		enum class ShaderType
		{
			eDefault = 0, // デフォルト
			eEnd, 
		};

	public:

		// 設定用ステータス
		struct Status
		{
			bool isDiv_ = true; // 画像サイズに合わせるか
			YMath::Vector2 size_; // サイズ
			YMath::Vector2 anchor_ = { 0.5f, 0.5f }; // アンカーポイント
			bool isFlipX_ = false; // 左右反転
			bool isFlipY_ = false; // 上下反転
		};

		// テクスチャ設定用ステータス
		struct TexStatus
		{
			Texture* pTex_; // テクスチャポインタ
			bool isDiv_ = true; // 画像サイズに合わせるか
			YMath::Vector2 leftTop_ = { 0.0f,0.0f }; // テクスチャ左上
			YMath::Vector2 size_ = { 0.0f,0.0f }; // テクスチャサイズ
		};

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="status"> : スプライト設定</param>
		/// <param name="(bool) isDiv_"> : 画像サイズに合わせるか</param>
		/// <param name="(Vector2) status.size_"> : 大きさ</param>
		/// <param name="(Vector2) status.anchor_"> : アンカーポイント (初期値は中心)</param>
		/// <param name="(bool) status.isFlipX_"> : X反転するか</param>
		/// <param name="(bool) status.isFlipY_"> : Y反転するか</param>
		/// <param name="--------------------------------"></param>
		/// <param name="texStatus"> : テクスチャ設定</param>
		/// <param name="(Texture*) texStatus.pTex_"> : テクスチャポインタ</param>
		/// <param name="(bool) isDiv_"> : 画像サイズに合わせるか</param>
		/// <param name="(Vector2) texStatus.leftTop_"> : テクスチャ左上</param>
		/// <param name="(Vector2) texStatus.size_"> : テクスチャサイズ</param>
		/// <param name="--------------------------------"></param>
		/// <returns>スプライトポインタ</returns>
		static Sprite2D* Create(const Status& status, const TexStatus& texStatus);

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
		void SetDrawCommand(Sprite2D::Object* pObj, const DrawLocation& location, const ShaderType& shaderType = ShaderType::eDefault);

		/// <summary>
		/// スプライトサイズ設定
		/// </summary>
		/// <param name="size"> : スプライトサイズ</param>
		void SetSize(const YMath::Vector2& size);

		/// <summary>
		/// アンカーポイント設定
		/// </summary>
		/// <param name="anchor"> : アンカーポイント</param>
		void SetAnchorPoint(const YMath::Vector2& anchor);

		/// <summary>
		/// フリップ設定
		/// </summary>
		/// <param name="isFlipX"> : X軸フリップ</param>
		/// <param name="isFlipY"> : Y軸フリップ</param>
		void SetFrip(const bool isFlipX, const bool isFlipY);

		/// <summary>
		/// テクスチャ左上設定
		/// </summary>
		/// <param name="leftTop"> : 左上</param>
		/// <param name="adjust"> : 調整するか</param>
		void SetTextureLeftTop(const YMath::Vector2& leftTop, const bool adjust = true);

		/// <summary>
		/// テクスチャサイズ設定
		/// </summary>
		/// <param name="texSize"> : テクスチャサイズ</param>
		void SetTextureSize(const YMath::Vector2& texSize);

		/// <summary>
		/// テクスチャ矩形設定
		/// </summary>
		/// <param name="leftTop"> : テクスチャ左上</param>
		/// <param name="texSize"> : テクスチャサイズ</param>
		void SetTextureRectangle(const YMath::Vector2& leftTop, const YMath::Vector2& texSize);

		/// <summary>
		/// 全設定
		/// </summary>
		/// <param name="status"> : スプライト設定</param>
		/// <param name="(bool) isDiv_"> : 画像サイズに合わせるか</param>
		/// <param name="(Vector2) status.size_"> : 大きさ</param>
		/// <param name="(Vector2) status.anchor_"> : アンカーポイント(中心)</param>
		/// <param name="(bool) status.isFlipX_"> : X反転するか</param>
		/// <param name="(bool) status.isFlipY_"> : Y反転するか</param>
		/// <param name="--------------------------------"></param>
		/// <param name="texStatus"> : テクスチャ設定</param>
		/// <param name="(UINT) texStatus.index_"> : テクスチャポインタ</param>
		/// <param name="(bool) isDiv_"> : 画像サイズに合わせるか</param>
		/// <param name="(Vector2) texStatus.leftTop_"> : テクスチャ左上</param>
		/// <param name="(Vector2) texStatus.size_"> : テクスチャサイズ</param>
		/// <param name="--------------------------------"></param>
		void SetAllStatus(const Status& status, const TexStatus& texStatus);

		/// <summary>
		/// 表示するか設定
		/// </summary>
		/// <param name="isVisible"> : 表示するか</param>
		void SetIsVisible(const bool isVisible);

	public:

		/// <summary>
		/// サイズ取得
		/// </summary>
		/// <returns>サイズ</returns>
		YMath::Vector2 Size() const { return size_; }

		/// <summary>
		/// アンカーポイント取得
		/// </summary>
		/// <returns>アンカーポイント</returns>
		YMath::Vector2 AnchorPoint() const { return anchor_; }

	public:

		Sprite2D() = default;

		~Sprite2D() = default;

	public:

		// 頂点データ構造体
		struct VData
		{
			YMath::Vector3 pos_; // xyz座標
			YMath::Vector2 uv_;  // uv座標
		};

	private:

		// 頂点データ
		YDX::Vertices<VData> vt_;


		// サイズ
		YMath::Vector2 size_;

		// アンカーポイント
		YMath::Vector2 anchor_;

		// 左右反転
		bool isFlipX_ = false;

		// 上下反転
		bool isFlipY_ = false;


		// テクスチャ
		Texture* pTex_ = nullptr;

		// テクスチャ左上
		YMath::Vector2 texLeftTop_;

		// テクスチャサイズ
		YMath::Vector2 texSize_;

		// 表示するか
		bool isVisible_ = true;

	private:

		// 静的スプライト2D格納用vector配列
		static std::vector<std::unique_ptr<Sprite2D>> sSprites_;
	
	public:

		// パイプラインクラス前方宣言
		class Pipeline;

	};


#pragma region Object

	// スプライト2D用オブジェクトクラス
	class Sprite2D::Object : public Transform
	{

	public:

		/// <summary>
		/// 生成 + 初期化 (Transform以外は nullの時 デフォルトで初期化)
		/// </summary>
		/// <param name="status"> : 位置, 回転, 大きさ</param>
		/// <param name="pColor"> : 色ポインタ</param>
		/// <param name="pTexConfig"> : テクスチャ設定ポインタ</param>
		/// <param name="isMutable"> : シーン遷移時に開放するか</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static Object* Create(
			const Status& status = Status::Default(),
			CBColor* pColor = nullptr,
			CBTexConfig* pTexConfig = nullptr,
			const bool isMutable = true);

	public:

		/// <summary>
		/// 描画前コマンド
		/// </summary>
		/// <param name="transformRPIndex"> : トランスフォームルートパラメータ番号</param>
		/// <param name="colorRPIndex"> : 色ルートパラメータ番号</param>
		/// <param name="texConfigRPIndex"> : テクスチャ設定ルートパラメータ番号</param>
		void SetDrawCommand(
			const UINT transformRPIndex,
			const UINT colorRPIndex,
			const UINT texConfigRPIndex);


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
		};

	private:

		// 定数バッファ (行列)
		YDX::ConstBuffer<CBData> cBuff_;

		// 色ポインタ
		CBColor* pColor_ = nullptr;

		// テクスチャ設定ポインタ
		CBTexConfig* pTexConfig_ = nullptr;

	public:

		// 既定値クラス
		class Default
		{

		public:

			// 静的射影変換行列(平行投影)
			static YMath::Matrix4 sProjection_;

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
	class Sprite2D::Pipeline
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
			Sprite2D* pSprite3D, 
			Sprite2D::Object* pObj, 
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

			// スプライト2Dポインタ
			Sprite2D* pSprite2D_;

			// スプライト2D用オブジェクト
			Sprite2D::Object* pObj_;

		public:

			/// <summary> 
			/// 描画
			/// </summary>
			void Draw();

		};

	private:

		// シェーダーの数
		static const size_t sShaderNum_ = static_cast<size_t>(ShaderType::eEnd);

		// パイプライン設定
		static std::array<YDX::PipelineSet, sShaderNum_> sPipelineSets_;

		// 描画用リスト配列
		static std::array<std::array<std::list<std::unique_ptr<DrawSet>>, sShaderNum_>, DrawLocationNum> sDrawSets_;

	};

#pragma endregion

}
