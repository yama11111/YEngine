#pragma once
#include "Vertices.h"
#include "ShaderCommon.h"
#include "PipelineSet.h"
#include "Sprite2DObject.h"
#include "Texture.h"
#include "Vector2.h"

namespace YGame
{
	// スプライト2Dクラス
	class Sprite2D
	{
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

		// 非表示
		bool isInvisible_ = false;

	private:

		// 静的スプライト2D格納用vector配列
		static std::vector<std::unique_ptr<Sprite2D>> sprites_;

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
		/// 描画
		/// </summary>
		/// <param name="pObj"> : オブジェクトポインタ</param>
		void Draw(Sprite2DObject* pObj);

		
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
		/// 非表示設定
		/// </summary>
		/// <param name="isInvisible"> : 非表示か</param>
		void SetInvisible(const bool isInvisible) { isInvisible_ = isInvisible; }
	
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

#pragma region Common

	public:

		// コモンクラス
		class Common
		{
		public:

			// ルートパラメータ番号
			enum class RootParameterIndex
			{
				TransformCB = 0, // 行列
				ColorCB = 1, // 色
				TexDT = 2, // テクスチャ
			};

		private:

			// シェーダーセット
			class ShaderSet : public YDX::ShaderCommon
			{
			public:

				// 頂点シェーダオブジェクト
				Microsoft::WRL::ComPtr<ID3DBlob> vsBlob_ = nullptr;

				// ピクセルシェーダオブジェクト
				Microsoft::WRL::ComPtr<ID3DBlob> psBlob_ = nullptr;

			public:

				/// <summary>
				/// シェーダーファイル読み込み
				/// </summary>
				/// <param name="errorBlob"> : エラー用</param>
				void Load(ID3DBlob* errorBlob);

			};

			// パイプライン設定構造体
			struct PipelineSetStatus : public YDX::PipelineSet::IStatus
			{

				/// <summary>
				/// 初期化
				/// </summary>
				/// <param name="errorBlob_"> : エラー用</param>
				void Initialize(ID3DBlob* errorBlob_) override;

			};

		protected:

			// パイプライン設定
			static YDX::PipelineSet sPipelineSet_;

		public:

			/// <summary>
			/// 静的初期化
			/// </summary>
			static void StaticInitialize();

			/// <summary>
			/// パイプラインセット
			/// </summary>
			static void StaticSetPipeline();

		};

	private:

		// コモン
		static Common common_;

#pragma endregion

	public:

		Sprite2D() = default;

		~Sprite2D() = default;

	};
}
