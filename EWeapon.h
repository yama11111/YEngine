#pragma once
#include "Model.h"

class EWeapon
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
	// 切っ先
	Math::Vec3 top_;
	// 芯
	Math::Vec3 pith_;
private:
	// 核
	Trfm core_;
	// 刀身
	Trfm blade_;
	// 鍔
	Trfm guard_;
	// 刀身2
	Trfm sub_[2];
	// 持ち手
	Trfm grip_;
public:
	// 初期化
	void Initialize(Math::Mat4* pParent);
	// リセット
	void Reset(Trfm::Status state, Math::Vec3 pith, Math::Vec3 top);
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

