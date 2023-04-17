#pragma once
#include "SkydomeDrawer.h"

class Skydome
{
private:
	// トランスフォーム
	YGame::Transform transform_;
	// 描画用クラス
	SkydomeDrawer drawer_;
public:
	// 初期化
	void Initialize();
	// リセット
	void Reset();
	// 更新
	void Update();
	// 描画
	void Draw();
};
