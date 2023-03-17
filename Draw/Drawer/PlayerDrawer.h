#pragma once
#include "Model.h"
#include "SlimeActor.h"
#include <array>
#include <memory>

// プレイヤー描画用コモンクラス
class PlayerDrawerCommon
{
protected:
	// パーツの名前
	enum class Parts
	{
		Body, // 体
	};
protected:
	// パーツの総数
	static const size_t PartsNum_ = 2;
protected:
	// モデル (パーツの数だけ)
	static std::array<std::unique_ptr<YGame::Model>, PartsNum_> models_;
public:
	// 静的初期化
	static void StaticInitialize();
};

// プレイヤー描画用クラス
class PlayerDrawer :
	private PlayerDrawerCommon,
	private YGame::SlimeActor
{
private:
	// オブジェクト (親)
	std::unique_ptr <YGame::ObjectModel> obj_;
	// モデル用オブジェクト (子)
	std::array<std::unique_ptr<YGame::ObjectModel>, PartsNum_> modelObjs_;
	// 向きポインタ
	YMath::Vector3* pDirection_ = nullptr;
	// 立ちモーション用タイマー
	YMath::Timer idelTim_;
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pParent"> : 親行列ポインタ (この行列に追従する)</param>
	void Initialize(YMath::Matrix4* pParent, YMath::Vector3* pDirection);
	// リセット (中身だけ初期化)
	void Reset();
	// 更新
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="vp"> : ビュープロジェクション (const 参照)</param>
	/// <param name="lightGroup"> : ライトグループ (ポインタ)</param>
	void Draw(const YGame::ViewProjection& vp, YGame::LightGroup* lightGroup);
public:
	// 立ちモーション
	void IdleAnimation();
	// 着地モーション
	void LandingAnimation();
	// ジャンプモーション
	void JumpAnimation();
	// 色替えアニメーション
	//void ChangeColor(const );
};

