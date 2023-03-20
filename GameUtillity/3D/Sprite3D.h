#pragma once
#include "Sprite3DCommon.h"
#include "Vertices.h"
#include "BaseObject.h"
#include "ViewProjection.h"
#include "Color.h"

namespace YGame
{
	// スプライト3D用オブジェクト
	class ObjectSprite3D : public BaseObject
	{
	public:
		// 定数バッファ
		YDX::ConstBuffer<Sprite3DCommon::CBData> cBuff_;
	public:
		/// <summary>
		/// 生成 + 初期化
		/// </summary>
		/// <param name="state"> : 設定用ステータス</param>
		/// <param name="(Vector3) state.pos_"> : 位置</param>
		/// <param name="(Vector3) state.rota_"> : 回転</param>
		/// <param name="(Vector3) state.scale_"> : 大きさ</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static ObjectSprite3D* Create(const Status& state);
	private:
		ObjectSprite3D() = default;
	public:
		~ObjectSprite3D() override = default;
	};

	// スプライト3Dクラス
	class Sprite3D : private Sprite3DCommon
	{
	private:
		// 頂点データ
		YDX::Vertices<VData> vt_;
		// 色
		std::unique_ptr<Color> defColor_;

		// X軸ビルボード
		bool isXAxisBillboard_ = false;
		// Y軸ビルボード
		bool isYAxisBillboard_ = false;

		// テクスチャ
		UINT tex_ = UINT32_MAX;

		// 非表示
		bool isInvisible_ = false;
	public:
		// ビルボード設定用ステータス
		struct Status
		{
			bool isXAxisBillboard_ = false; // X軸ビルボード
			bool isYAxisBillboard_ = false; // Y軸ビルボード
		};
	public:
		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="state"> : ビルボード設定用ステータス</param>
		/// <param name="(bool) state.isXAxisBillboard_"> : X軸ビルボード</param>
		/// <param name="(bool) state.isYAxisBillboard_"> : Y軸ビルボード</param>
		/// <param name="--------------------------------"></param>
		/// <param name="texIndex"> : テクスチャインデックス</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static Sprite3D* Create(const Status& state, const UINT texIndex);
	public:
		/// <summary>
		/// 描画 (テクスチャ + 色 有)
		/// </summary>
		/// <param name="pObj"> : オブジェクトポインタ</param>
		/// <param name="vp"> : ビュープロジェクション</param>
		/// <param name="pColor"> : 色ポインタ</param>
		/// <param name="tex"> : テクスチャインデックス</param>
		void Draw(ObjectSprite3D* pObj, const ViewProjection& vp, Color* pColor, const UINT tex);
		/// <summary>
		/// 描画 (テクスチャ 有)
		/// </summary>
		/// <param name="pObj"> : オブジェクトポインタ</param>
		/// <param name="vp"> : ビュープロジェクション</param>
		/// <param name="tex"> : テクスチャインデックス</param>
		void Draw(ObjectSprite3D* pObj, const ViewProjection& vp, const UINT tex);
		/// <summary>
		/// 描画 (色 有)
		/// </summary>
		/// <param name="pObj"> : オブジェクトポインタ</param>
		/// <param name="vp"> : ビュープロジェクション</param>
		/// <param name="pColor"> : 色ポインタ</param>
		void Draw(ObjectSprite3D* pObj, const ViewProjection& vp, Color* pColor);
		/// <summary>
		/// 描画 (デフォルト)
		/// </summary>
		/// <param name="pObj"> : オブジェクトポインタ</param>
		/// <param name="vp"> : ビュープロジェクション</param>
		void Draw(ObjectSprite3D* pObj, const ViewProjection& vp);
	private:
		// ビルボード行列計算
		YMath::Matrix4 BillboardMatrix(const ViewProjection& vp);
	private:
		Sprite3D() = default;
	public:
		~Sprite3D() = default;
	};
}
