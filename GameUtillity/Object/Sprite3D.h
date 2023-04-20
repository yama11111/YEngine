#pragma once
#include "Vertices.h"
#include "IShaderSet.h"
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
	
#pragma region Pipeline

	public:

		// パイプラインクラス
		class Pipeline
		{

		public:

			// ルートパラメータ番号
			enum class RootParameterIndex
			{
				TransformCB	 = 0, // 行列
				ColorCB		 = 1, // 色
				TexDT		 = 2, // テクスチャ
			};

		private:

			// シェーダーセット
			class ShaderSet : public YDX::IShaderSet
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
				void Load() override;

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
			/// パイプライン描画コマンド
			/// </summary>
			static void StaticSetDrawCommond();

		};

#pragma endregion

	public:
		
		Sprite3D() = default;

		~Sprite3D() = default;
	
	};
}
