#pragma once
#include "Model.h"

class MapInfo
{
protected:
	// マップチップナンバー
	std::vector<std::vector<int>> chipNums_;
	// ロード済みか
	bool isLoaded_ = false;
public:
	// csv読み込み
	void Load(const std::string fileName);
};

class Map : public MapInfo 
{
private:
	// マップチップ
	std::vector<std::vector<Game::Object>> chips_;
	// マップ全体の大きさ(矩形)
	Math::Vec2 rect_;
	// チップ1個分の大きさ
	float chipSize_ = 0.0f;

	// モデルポインタ
	Game::Model* pModel_ = nullptr;
	// テクスチャインデックス
	UINT tex_ = UINT_MAX;
public:
	// 初期化ステータス
	struct InitStatus 
	{
		float chipSize_; // チップ1個分の大きさ
		Math::Vec3 leftTop_; // 左上([0][0])
		Game::Model* pModel_; // モデルポインタ
		UINT tex_; // テクスチャインデックス
	};
public:
	// 初期化
	void Initialize(const InitStatus& state);
	// リセット
	void Reset(const Math::Vec3& leftTop);
	// 更新
	void Update();
	// 描画
	void Draw(const Game::ViewProjection& vp);
public:
	// 衝突時処理
	void PerfectPixelCollision(Math::Vec3& pos, const Math::Vec3 scale, Math::Vec2& spd);
private:
	// 仮移動後のチップごとのアタリ判定
	bool TemporaryChipCollision(Math::Vec3& pos, const Math::Vec3 scale, const Math::Vec2& spd);
	// チップごとのアタリ判定
	bool ChipCollision(const float left, const float right, const float top, const float bottom);
};