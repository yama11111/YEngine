#pragma once
#include "Model.h"
#include <vector>

class Floor
{
private:
	// オブジェクト
	std::vector<std::vector<YGame::ObjectModel>> objs;
public:
	struct InitStatus
	{
		size_t xNum_; // X軸 枚数
		size_t yNum_; // Y軸 枚数
		YMath::Vec3 pos_;// 場所 (中心)
		YMath::Vec3 scale_;// 大きさ (1枚)
	};
public:
	// 初期化
	void Initialize(const InitStatus& state);
	// 更新
	void Update();
	// 描画
	void Draw(const YGame::ViewProjection& vp);
private:
	// 静的モデルポインタ
	static YGame::Model* pModel_;
	// 静的テクスチャインデックス
	static UINT tex_;
public:
	// 静的初期化ステータス
	struct StaticInitStatus
	{
		YGame::Model* pModel_;// モデルポインタ
		UINT tex_;// テクスチャインデックス
	};
public:
	// 静的初期化
	static void StaticIntialize(const StaticInitStatus& state);
};