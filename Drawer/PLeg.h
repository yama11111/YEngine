#pragma once
#include "Model.h"
#include "Lerp.h"
#include "Power.h"
#include "Timer.h"

class PLeg
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
	// 足
	Trfm foot_;
	// 足首
	Trfm ankle_;
private:
	// 歩きモーション
	Math::Ease<Math::Vec3> walkPE_[2];
	Math::Ease<Math::Vec3> walkRE_[2];
	Math::Power* pWalkP_ = nullptr;
public:
	// 初期化
	void Initialize(Math::Mat4* pParent, Math::Power* pWalkP);
	// リセット
	void Reset(Trfm::Status state);
	// 転送用リセット
	void ResetTransfer();
	// 更新
	void Update(const bool isFB);
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

