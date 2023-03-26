#pragma once
#include "ModelCommon.h"
#include "Transform.h"

namespace YGame
{
	// モデル用オブジェクトクラス
	class ModelObject :
		public Transform, 
		private ModelObjectCommon
	{
	private:
		// 定数バッファ (行列)
		YDX::ConstBuffer<ModelObjectCommon::CBData> cBuff_;
		// ビュープロジェクションポインタ
		ViewProjection* pVP_ = nullptr;
		// 色ポインタ
		Color* pColor_ = nullptr;
		// 光源ポインタ
		LightGroup* pLightGroup_ = nullptr;
	public:
		/// <summary>
		/// 生成 + 初期化 (デフォルト初期化)
		/// </summary>
		/// <param name="status"> : 設定用ステータス</param>
		/// <param name="(Vector3) status.pos_"> : 位置</param>
		/// <param name="(Vector3) status.rota_"> : 回転</param>
		/// <param name="(Vector3) status.scale_"> : 大きさ</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static ModelObject* Create(const Status& status);
		/// <summary>
		/// 生成 + 初期化 (Transform以外は nullの時 デフォルトで初期化)
		/// </summary>
		/// <param name="status"> : 設定用ステータス</param>
		/// <param name="(Vector3) status.pos_"> : 位置</param>
		/// <param name="(Vector3) status.rota_"> : 回転</param>
		/// <param name="(Vector3) status.scale_"> : 大きさ</param>
		/// <param name="-------------------------------------"></param>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		/// <param name="pColor"> : 色ポインタ</param>
		/// <param name="pLightGroup"> : 光源ポインタ</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static ModelObject* Create(const Status& status, ViewProjection* pVP, Color* pColor, LightGroup* pLightGroup);
	public:
		// ビュープロジェクション設定 (null = Default)
		void SetViewProjection(ViewProjection* pVP);
		// 色設定 (null = Default)
		void SetColor(Color* pColor);
		// ライトグループ設定 (null = Default)
		void SetLightGroup(LightGroup* pLightGroup);
	public:
		// 描画前コマンド
		void SetDrawCommand();
	private:
		ModelObject() = default;
	public:
		~ModelObject() override = default;
	};

	// モデルクラス
	class Model : private ModelCommon
	{
	private:
		// メッシュ配列
		std::vector<Mesh> meshes_;
		
		// 非表示
		bool isInvisible_ = false;
	public:
		// 読み込み設定構造体
		struct LoadStatus
		{
			std::string directoryPath_;  // ディレクトリパス
			std::string modelFileName_;  // モデル名
			bool isSmoothing_ = false;   // スムーシングするか
			bool isInverseU_ = false;    // U反転設定
			bool isInverseV_ = true;     // V反転設定
			bool isNormalized_ = false;  // 法線計算するか
			std::string extension_ = ""; // 拡張子
		};
	public:
		// 生成(立方体)
		static Model* Create();
		/// <summary>
		/// モデル読み込み
		/// </summary>
		/// <param name="modelFileName"> : モデルのフォルダ名 (objと同じ名前の時のみ) </param>
		/// <param name="isSmoothing"> : スムーシングするか</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static Model* LoadObj(const std::string& modelFileName, const bool isSmoothing);
		/// <summary>
		/// モデル読み込み(assimp)
		/// </summary>
		/// <param name="status"> 読み込み設定</param>
		/// <param name="(string) status.directoryPath_"> : ファイルまでのパス名</param>
		/// <param name="(string) status.modelFileName_">  :モデルファイル名</param>
		/// <param name="(bool) status.isSmoothing_"> : スムーシングするか</param>
		/// <param name="(bool) status.isInverseU_"> : U反転設定</param>
		/// <param name="(bool) status.isInverseV_"> : V反転設定</param>
		/// <param name="(bool) status.isNormalized_"> : 法線を計算するか</param>
		/// <param name="(string) status.extension_"> : 拡張子</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static Model* Load(const LoadStatus& status);
	public:
		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="pObj"> : オブジェクトポインタ</param>
		void Draw(ModelObject* pObj);
	public:
		// 非表示設定
		void SetInvisible(const bool isInvisible) { isInvisible_ = isInvisible; }
	private:
		Model() = default;
	public:
		~Model() = default;
	};
}
