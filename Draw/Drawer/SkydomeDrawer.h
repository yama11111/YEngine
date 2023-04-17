#pragma once
#include "Model.h"

class SkydomeDrawerCommon
{
protected:
	// 静的モデル
	static YGame::Model* spModel_;
public:
	// 静的初期化
	static void StaticInitialize();
public:
	virtual ~SkydomeDrawerCommon() = default;
};

class SkydomeDrawer :
	public SkydomeDrawerCommon
{
private:
	// オブジェクト
	std::unique_ptr<YGame::ModelObject> obj_;
	// 色
	std::unique_ptr<YGame::Color> color_;

public:
	// 初期化
	void Initalize(YMath::Matrix4* pParent);
	// リセット
	void Reset();
	// 更新
	void Update();
	// 描画
	void Draw();
};

