#pragma once
#include "Vertices.h"
#include "IShaderSet.h"
#include "PipelineSet.h"
#include "Texture.h"
#include "Transform.h"
#include "CBColor.h"
#include "CBTexConfig.h"
#include "ScreenDesc.h"
#include <list>
#include <array>

namespace YGame
{
	// ポストエフェクトクラス
	class PostEffect
	{

	public:

		// オブジェクトクラス前方宣言
		class Object;

		// シェーダーの種類
		enum class ShaderType
		{
			eDefault		 = 0, // デフォルト
			eColorInversion	 = 1, // 色反転
			eUVShiftBlur	 = 2, // 平均ぼかし
			eGaussianBlur	 = 3, // ガウスぼかし
			eBloom			 = 4, // ブルーム
			eEnd,
		};

	public:
		
		/// <summary>
		/// 生成
		/// </summary>
		/// <returns>ポストエフェクトポインタ</returns>
		static PostEffect* Create();

		/// <summary>
		/// 全削除
		/// </summary>
		static void AllClear();

	public:

		/// <summary>
		/// 描画コマンド
		/// </summary>
		/// <param name="pObj"> : オブジェクトポインタ</param>
		/// <param name="shaderType"> : シェーダー</param>
		void SetDrawCommand(PostEffect::Object* pObj, const ShaderType& shaderType = ShaderType::eDefault);

		/// <summary>
		/// 書き込み開始
		/// </summary>
		void StartRender();

		/// <summary>
		/// 書き込み終了
		/// </summary>
		void EndRender();

		/// <summary>
		/// 表示するか設定
		/// </summary>
		/// <param name="isVisible"> : 表示するか</param>
		inline void SetIsVisible(const bool isVisible) { isVisible_ = isVisible; }

	public:

		PostEffect() = default;

		~PostEffect() = default;

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

		// テクスチャの数
		static const size_t kTextureNum_ = 2;

		// テクスチャ
		std::array<Texture*, kTextureNum_> pTexs_;

		// 表示するか
		bool isVisible_ = true;


		// RTV用ヒープ
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap_ = nullptr;

		// DSV用ヒープ
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap_ = nullptr;

		// 深度バッファ
		YDX::GPUResource depthBuff_;


	private:

		// 静的ポストエフェクト格納用vector配列
		static std::vector<std::unique_ptr<PostEffect>> sPostEffects_;

	public:

		// パイプラインクラス前方宣言
		class Pipeline;

	private:

		void CreateRTV();

		void CreateDepthBuff(const YMath::Vector2& size);

		void CreateDSV();

	private:

		// 静的デバイスポインタ
		static ID3D12Device* spDevice_;

		// 静的コマンドリストポインタ
		static ID3D12GraphicsCommandList* spCmdList_;

		// 静的スクリーン設定ポインタ
		static YDX::ScreenDesc sScreenDesc_;

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		/// <param name="pDevice"> : デバイスポインタ</param>
		/// <param name="pCmdList"> : コマンドリストポインタ</param>
		static void StaticInitialize(
			ID3D12Device* pDevice,
			ID3D12GraphicsCommandList* pCmdList);

	};


#pragma region Object

	// スプライト2D用オブジェクトクラス
	class PostEffect::Object : public Transform
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
	class PostEffect::Pipeline
	{

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void StaticInitialize();

		/// <summary>
		/// 静的描画リストクリア
		/// </summary>
		static void StaticClearDrawSet();

		/// <summary>
		/// 静的描画セット挿入
		/// </summary>
		/// <param name="pPostEffect"> : ポストエフェクトポインタ</param>
		/// <param name="pObj"> : オブジェクトポインタ</param>
		/// <param name="shaderType"> : シェーダー</param>
		static void StaticPushBackDrawSet(
			PostEffect* pPostEffect, 
			PostEffect::Object* pObj,
			const ShaderType& shaderType);

		/// <summary>
		/// 静的描画
		/// </summary>
		static void StaticDraw();

	public:

		// ルートパラメータ番号
		enum class RootParameterIndex
		{
			eTransformCB = 0, // 行列
			eColorCB	 = 1, // 色
			eTexConfigCB = 2, // テクスチャ設定
			eTex0DT		 = 3, // テクスチャ0
			eTex1DT		 = 4, // テクスチャ1
		};

	private:

		// シェーダーセット
		class ShaderSet : public YDX::IShaderSet
		{

		public:

			// DefaultVS
			Microsoft::WRL::ComPtr<ID3DBlob> defaultVSBlob_ = nullptr;
		
		public:
			
			// DefaultPS
			Microsoft::WRL::ComPtr<ID3DBlob> defaultPSBlob_ = nullptr;

			//ColorInversionPS
			Microsoft::WRL::ComPtr<ID3DBlob> colorInversionPSBlob_ = nullptr;

			// UVShiftBlurPS
			Microsoft::WRL::ComPtr<ID3DBlob> uvShiftBlurPSBlob_ = nullptr;
			
			// GaussianPS
			Microsoft::WRL::ComPtr<ID3DBlob> gaussianBlurPSBlob_ = nullptr;

			// BloomPS
			Microsoft::WRL::ComPtr<ID3DBlob> bloomPSBlob_ = nullptr;

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

			// ポストエフェクトポインタ
			PostEffect* pPostEffect_;

			// ポストエフェクト用オブジェクト
			PostEffect::Object* pObj_;

			// パイプラインインデックス
			size_t pipelineIndex_;

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
		static std::list<std::unique_ptr<DrawSet>> sDrawSets_;

	};

#pragma endregion

}
