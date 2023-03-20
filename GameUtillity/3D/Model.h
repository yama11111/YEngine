#pragma once
#include "ModelCommon.h"
#include "BaseObject.h"
#include "ViewProjection.h"
#include "LightGroup.h"

namespace YGame
{
	// モデル用オブジェクト
	class ObjectModel : public BaseObject
	{
	public:
		// 定数バッファ
		YDX::ConstBuffer<ModelCommon::CBData> cBuff_;
	public:
		/// <summary>
		/// 生成 + 初期化
		/// </summary>
		/// <param name="state"> : 設定用ステータス</param>
		/// <param name="(Vector3) state.pos_"> : 位置</param>
		/// <param name="(Vector3) state.rota_"> : 回転</param>
		/// <param name="(Vector3) state.scale_"> : 大きさ</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static ObjectModel* Create(const Status& state);
	private:
		ObjectModel() = default;
	public:
		~ObjectModel() override = default;
	};

	// モデルクラス
	class Model : private ModelCommon
	{
	private:
		// メッシュ配列
		std::vector<Mesh> meshes_;
		// 色
		std::unique_ptr<Color> defColor_;
		
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
		/// <param name="state"> 読み込み設定</param>
		/// <param name="(string) state.directoryPath_"> : ファイルまでのパス名</param>
		/// <param name="(string) state.modelFileName_">  :モデルファイル名</param>
		/// <param name="(bool) state.isSmoothing_"> : スムーシングするか</param>
		/// <param name="(bool) state.isInverseU_"> : U反転設定</param>
		/// <param name="(bool) state.isInverseV_"> : V反転設定</param>
		/// <param name="(bool) state.isNormalized_"> : 法線を計算するか</param>
		/// <param name="(string) state.extension_"> : 拡張子</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static Model* Load(const LoadStatus& state);
	public:
		/// <summary>
		/// 描画 (テクスチャ + 色 有)
		/// </summary>
		/// <param name="pObj"> : オブジェクトポインタ</param>
		/// <param name="vp"> : ビュープロジェクション</param>
		/// <param name="pLightGroup"> : 光源グループポインタ</param>
		/// <param name="pColor"> : 色ポインタ</param>
		/// <param name="tex"> : テクスチャインデックス</param>
		void Draw(ObjectModel* pObj, const ViewProjection& vp, LightGroup* pLightGroup, Color* pColor, const UINT tex);
		/// <summary>
		/// 描画 (テクスチャ 有)
		/// </summary>
		/// <param name="pObj"> : オブジェクトポインタ</param>
		/// <param name="vp"> : ビュープロジェクション</param>
		/// <param name="pLightGroup"> : 光源グループポインタ</param>
		/// <param name="tex"> : テクスチャインデックス</param>
		void Draw(ObjectModel* pObj, const ViewProjection& vp, LightGroup* pLightGroup, const UINT tex);
		/// <summary>
		/// 描画 (色 有)
		/// </summary>
		/// <param name="pObj"> : オブジェクトポインタ</param>
		/// <param name="vp"> : ビュープロジェクション</param>
		/// <param name="pLightGroup"> : 光源グループポインタ</param>
		/// <param name="pColor"> : 色ポインタ</param>
		void Draw(ObjectModel* pObj, const ViewProjection& vp, LightGroup* pLightGroup, Color* pColor);
		/// <summary>
		/// 描画 (デフォルト)
		/// </summary>
		/// <param name="pObj"> : オブジェクトポインタ</param>
		/// <param name="vp"> : ビュープロジェクション</param>
		/// <param name="pLightGroup"> : 光源グループポインタ</param>
		void Draw(ObjectModel* pObj, const ViewProjection& vp, LightGroup* pLightGroup);
	public:
		// 非表示設定
		void SetInvisible(const bool isInvisible) { isInvisible_ = isInvisible; }
	private:
		Model() = default;
	public:
		~Model() = default;
	};
}
