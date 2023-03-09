#pragma once
#include "Keys.h"
#include "Character.h"
#include "Sprite2D.h"

class Player : public Character
{
private:
	// ジャンプ回数
	int jumpCount_ = 0;
public:
	// 初期化
	void Initialize(const YGame::BaseObject::Status& state);
	// リセット
	void Reset(const YGame::BaseObject::Status& state);
	// 更新
	void Update();
	// 描画
	void Draw(const YGame::ViewProjection& vp, YGame::LightGroup* lightGroup);
	// 2D描画
	void Draw2D();
private:
	// ジャンプ
	void Jump();
	// 移動アップデート
	void UpdateMove();
public:
	// 位置ポインタ取得
	YMath::Vector3* PosPointer() { return &obj_->pos_; }
private:
	// 静的モデルポインタ
	static YGame::Model* pModel_;
	// 静的テクスチャインデックス
	static UINT tex_;
	// 
	static YInput::Keys* keys_;
public:
	// 静的初期化ステータス
	struct StaticInitStatus
	{
		YGame::Model* pModel_;// モデルポインタ
		UINT tex_; // テクスチャインデックス
	};
public:
	// 静的初期化
	static void StaticIntialize(const StaticInitStatus& state);
};

