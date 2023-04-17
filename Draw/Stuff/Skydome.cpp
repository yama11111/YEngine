#include "Skydome.h"
#include <cassert>

void Skydome::Initialize()
{
	// 初期化
	transform_.Initialize({});
	drawer_.Initalize(&transform_.m_);

	// リセット
	Reset();
}

void Skydome::Reset()
{
	transform_.Initialize({});
	drawer_.Reset();
}

void Skydome::Update()
{
	// 更新
	transform_.UpdateMatrix();

	drawer_.Update();
}

void Skydome::Draw()
{
	// 描画
	drawer_.Draw();
}