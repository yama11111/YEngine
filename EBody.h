#pragma once
#include "Model.h"

class EBody
{
private:
	// Transform 省略
	using Trfm = Game::Transform;
public:
	// 転送用Pos
	Math::Vec3 tPos_;
	// 転送用Rota
	Math::Vec3 tRota_;
	// 転送用Scale
	Math::Vec3 tScale_;
private:
	// 核
	Trfm core_;
	// 体
	Trfm body_;
	// 角
	Trfm horn_;
	// 耳
	Trfm ears1_[2];
	Trfm ears2_[2];
public:
	// 初期化
	void Initialize(Math::Mat4* pParent);
	// リセット
	void Reset(Trfm::Status state);
	// 転送用リセット
	void ResetTransfer();
	// 更新
	void Update();
	// 描画
	void Draw(Game::ViewProjection& vp, const UINT tex);
public:
	// 全体サイズ
	Math::Vec3 Size();
private:
	// 静的モデルポインタ
	static Game::Model* pModel_;
public:
	// 静的初期化
	static void StaticInitialize(Game::Model* pModel);
};

