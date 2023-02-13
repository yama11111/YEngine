#pragma once
#include "Model.h"
#include "Sprite2D.h"
#include "MapChipCollider.h"
#include <list>
#include <memory>

// マップ情報
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
	std::vector<std::unique_ptr<YGame::ObjectModel>> chips_;
	//// マップチップ2D用
	//std::vector<std::vector<YGame::Object>> chip2Ds_;
	// マップ全体の大きさ(矩形)
	YMath::Vector2 rect_;
	// チップ1個分の大きさ
	YMath::Vector3 chipSize_;
	// 左上
	YMath::Vector3 leftTop_;

	// モデルポインタ
	YGame::Model* pModel_ = nullptr;
	// テクスチャインデックス
	UINT tex_ = UINT_MAX;
	// スプライトポインタ
	YGame::Sprite2D* pSprite_ = nullptr;
public:
	// ロードステータス
	struct LoadStatus
	{
		const std::string mapFileName_; // マップファイル名
		YGame::Model* pModel_; // モデルポインタ
		UINT tex_; // テクスチャインデックス
		YGame::Sprite2D* pSprite_; // スプライトポインタ
	};
	// 初期化ステータス
	struct InitStatus 
	{
		YMath::Vector3 leftTop_; // 左上([0][0])
		YMath::Vector3 chipSize_; // チップ1個分の大きさ
	};
public:
	// ロード
	void Load(const LoadStatus& state);
	// 初期化
	void Initialize(const InitStatus& state);
	// リセット
	void Reset();
	// 更新
	void Update();
	// 描画
	void Draw(const YGame::ViewProjection& vp);
	// 2D描画
	void Draw2D();
public:
	// 衝突時処理
	void PerfectPixelCollision(MapChipCollider& collider);
private:
	// 仮移動後のチップごとのアタリ判定
	bool CollisionTemporaryMap(const YMath::Vector3& pos, const YMath::Vector3 scale, const YMath::Vector3& spd);
	// チップごとのアタリ判定
	bool CollisionMap(const float left, const float right, const float top, const float bottom);
	// チップごとのアタリ判定
	bool CollisionChip(const int x, const int y);
};