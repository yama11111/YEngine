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
		// 生成
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
		struct Status 
		{
			bool isXAxisBillboard_ = false;
			bool isYAxisBillboard_ = false;
		};
	public:
		// 生成
		static Sprite3D* Create(const Status& state, const UINT texIndex = UINT32_MAX);
	public:
		// 描画
		void Draw(ObjectSprite3D* obj, const ViewProjection& vp, Color* color, const UINT tex);
		// 描画
		void Draw(ObjectSprite3D* obj, const ViewProjection& vp, const UINT tex);
		// 描画
		void Draw(ObjectSprite3D* obj, const ViewProjection& vp, Color* color);
		// 描画
		void Draw(ObjectSprite3D* obj, const ViewProjection& vp);
	private:
		YMath::Matrix4 BillboardMatrix(const ViewProjection& vp);
	private:
		Sprite3D() = default;
	public:
		~Sprite3D() = default;
	};
}
