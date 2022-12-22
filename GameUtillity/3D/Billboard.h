#pragma once
#include "BillboardCommon.h"
#include "Vertices.h"
#include "Object.h"
#include "ViewProjection.h"

namespace YGame
{
	class Billboard : private BillboardCommon
	{
	private:
		// 頂点データ
		YDX::Vertices<VData> vt_;
		// Y軸ビルボード
		bool isAxisY_ = false;
		
		// 非表示
		bool isInvisible_ = false;

		// 定数バッファ(ビルボード)
		YDX::ConstBuffer<YDX::BillboardCBData> cbBlbd_;
	public:
		// 生成
		static Billboard* Create(const bool isYAxisBillboard);
	public:
		// 描画
		void Draw(Object& obj, const ViewProjection& vp, const UINT tex);
	private:
		// コンストラクタ
		Billboard() = default;
	};
}
