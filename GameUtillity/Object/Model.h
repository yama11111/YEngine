#pragma once
#include "Mesh.h"
#include "ShaderCommon.h"
#include "PipelineSet.h"
#include "ModelObject.h"

namespace YGame
{
	// モデルクラス
	class Model
	{
	private:
		
		// メッシュ配列
		std::vector<std::unique_ptr<Mesh>> meshes_;
		
		// 非表示
		bool isInvisible_ = false;

		// ファイルパス
		std::string fileName_;

	private:

		// 静的モデル格納用vector配列
		static std::vector<std::unique_ptr<Model>> models_;

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
		/// モデル読み込み
		/// </summary>
		/// <param name="modelFileName"> : モデルのフォルダ名 (objと同じ名前の時のみ) </param>
		/// <param name="isSmoothing"> : スムーシングするか</param>
		/// <returns>モデルポインタ</returns>
		static Model* Load(const std::string& modelFileName, const bool isSmoothing);

		/// <summary>
		/// 全削除
		/// </summary>
		static void AllClear();

	public:

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="pObj"> : オブジェクトポインタ</param>
		void Draw(ModelObject* pObj);
		
		/// <summary>
		/// 非表示設定
		/// </summary>
		/// <param name="isInvisible"> : 非表示か</param>
		void SetInvisible(const bool isInvisible) { isInvisible_ = isInvisible; }

#pragma region Common

	public:

		// コモンクラス
		class Common
		{
		public:

			// ルートパラメータ番号
			enum class RootParameterIndex
			{
				TransformCB	 = 0, // 行列
				ColorCB		 = 1, // 色
				LightCB		 = 2, // 光
				MaterialCB	 = 3, // マテリアル
				TexDT		 = 4, // テクスチャ
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
		
		Model() = default;

		~Model() = default;
	};
}
