#pragma once
#include "Model.h"
#include "Sprite.h"
#include "MapChipCollider.h"

class MapChipInfo
{
protected:
	// マップチップナンバー
	std::vector<std::vector<int>> chipNums_;
	// ロード済みか
	bool isLoaded_ = false;
public:
	// csv読み込み
	void LoadData(const std::string fileName);
};

class MapChip : public MapChipInfo 
{
private:
	// マップチップ
	std::vector<std::vector<Game::Object>> chips_;
	// マップチップ2D用
	std::vector<std::vector<Game::Object>> chip2Ds_;
	// マップ全体の大きさ(矩形)
	Math::Vec2 rect_;
	// チップ1個分の大きさ
	float chipSize_ = 0.0f;
	// 左上
	Math::Vec3 leftTop_;

	// モデルポインタ
	Game::Model* pModel_ = nullptr;
	// テクスチャインデックス
	UINT tex_ = UINT_MAX;
	// スプライトポインタ
	Game::Sprite* pSprite_ = nullptr;
public:
	// ロードステータス
	struct LoadStatus
	{
		const std::string mapFileName_; // マップファイル名
		Game::Model* pModel_; // モデルポインタ
		UINT tex_; // テクスチャインデックス
		Game::Sprite* pSprite_; // スプライトポインタ
	};
	// 初期化ステータス
	struct InitStatus 
	{
		float chipSize_; // チップ1個分の大きさ
		Math::Vec3 leftTop_; // 左上([0][0])
	};
public:
	// ロード
	void Load(const LoadStatus& state);
	// 初期化
	void Initialize(const InitStatus& state);
	// リセット
	void Reset(const Math::Vec3& leftTop);
	// 更新
	void Update();
	// 描画
	void Draw(const Game::ViewProjection& vp);
	// 2D描画
	void Draw2D();
public:
	// 衝突時処理
	void PerfectPixelCollision(MapChipCollider& collider);
private:
	// 仮移動後のチップごとのアタリ判定
	bool CollisionTemporaryMap(const Math::Vec3& pos, const Math::Vec3 scale, const Math::Vec3& spd);
	// チップごとのアタリ判定
	bool CollisionMap(const float left, const float right, const float top, const float bottom);
	// チップごとのアタリ判定
	bool CollisionChip(const int x, const int y);
	// チップ描画
	void DrawChip(const size_t x, const size_t y, const Game::ViewProjection& vp);
};