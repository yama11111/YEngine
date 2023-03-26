#pragma once
#include "Model.h"
#include "SlimeActor.h"
#include <array>
#include <memory>

// ブロック描画用コモンクラス
class BlockDrawerCommon
{
protected:
	// パーツの名前
	enum class Parts
	{
		Cube, // 正方形
	};
protected:
	// パーツの総数
	static const size_t PartsNum_ = 2;
protected:
	// モデル (パーツの数だけ)
	static std::array<std::unique_ptr<YGame::Model>, PartsNum_> sModels_;
public:
	// 静的初期化
	static void StaticInitialize();
};

// ブロック描画用クラス
class BlockDrawer :
	private BlockDrawerCommon,
	private YGame::SlimeActor
{
private:
	// トランスフォーム 
	std::unique_ptr<YGame::Transform> transform_;
	// モデル用オブジェクト (子)
	std::array<std::unique_ptr<YGame::ModelObject>, PartsNum_> modelObjs_;
	// 立ちモーション用タイマー
	YMath::Timer idelTim_;
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pParent"> : 親行列ポインタ (この行列に追従する)</param>
	void Initialize(YMath::Matrix4* pParent);
	// リセット (中身だけ初期化)
	void Reset();
	// 更新
	void Update();
	// 描画
	void Draw();
public:
	// 立ちモーション
	void IdleAnimation();
};

