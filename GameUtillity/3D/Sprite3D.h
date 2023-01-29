#pragma once
#include "Sprite3DCommon.h"
#include "Vertices.h"
#include "Object.h"
#include "ViewProjection.h"
#include "Color.h"

namespace YGame
{
	// モデル用オブジェクト
	typedef Object<Sprite3DCommon::CBData> ObjectSprite3D;

	class Sprite3D : private Sprite3DCommon
	{
	private:
		// 頂点データ
		YDX::Vertices<VData> vt_;
		// 色
		Color defColor_{};

		// X軸ビルボード
		bool isXAxisBillboard_ = false;
		// Y軸ビルボード
		bool isYAxisBillboard_ = false;
		
		// テクスチャ
		UINT tex_ = UINT32_MAX;

		// 非表示
		bool isInvisible_ = false;
	public:
		// 生成
		static Sprite3D* Create(const bool isXAxisBillboard, const bool isYAxisBillboard);
	public:
		// 描画
		void Draw(ObjectSprite3D& obj, const ViewProjection& vp, Color& color, const UINT tex);
		// 描画
		void Draw(ObjectSprite3D& obj, const ViewProjection& vp, const UINT tex);
		// 描画
		void Draw(ObjectSprite3D& obj, const ViewProjection& vp, Color& color);
		// 描画
		void Draw(ObjectSprite3D& obj, const ViewProjection& vp);
	private:
		YMath::Mat4 BillboardMatrix(const ViewProjection& vp);
	private:
		// コンストラクタ
		Sprite3D() = default;
	};
}
