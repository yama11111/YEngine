#pragma once
#include "Vertices.h"
#include "ShaderCommon.h"
#include "PipelineSet.h"
#include "Sprite3DObject.h"
#include "Texture.h"

namespace YGame
{
	// スプライト3Dクラス
	class Sprite3D
	{
	public:
		
		// 頂点データ
		struct VData
		{
			YMath::Vector3 pos_; // xyz座標
		};

	private:
		
		// 頂点データ
		YDX::Vertices<VData> vt_;


		// テクスチャ
		Texture* pTex_ = nullptr;

		// 非表示
		bool isInvisible_ = false;

	private:

		// 静的スプライト3D格納用vector配列
		static std::vector<std::unique_ptr<Sprite3D>> sprites_;

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
		/// 描画
		/// </summary>
		/// <param name="pObj"> : オブジェクトポインタ</param>
		void Draw(Sprite3DObject* pObj);
	
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

				// ジオメトリシェーダオブジェクト
				Microsoft::WRL::ComPtr<ID3DBlob> gsBlob_ = nullptr;

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
		
		Sprite3D() = default;

		~Sprite3D() = default;
	
	};
}
