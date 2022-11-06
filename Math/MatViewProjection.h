#pragma once
#include "MatView.h"
#include "MatProjection.h"

namespace Math
{
	class MatViewProjection
	{
	public:
		// ビュー
		MatView view_;
		// プロジェクション
		MatProjection pro_;
	public:
		// コンストラクタ
		MatViewProjection();
		// コンストラクタ (引数有)
		MatViewProjection(const MatView::InitStatus& init);
		// 初期化
		void Initialize(const MatView::InitStatus& init);
		// ビュー行列計算
		void Update();
	};
}
