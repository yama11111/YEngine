/**
 * @file GameCamera.h
 * @brief ゲームカメラクラス
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include "Camera.h"
#include "Power.h"

namespace YGame
{
	class GameCamera final
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// デバッグ描画
		/// </summary>
		void DrawDebugText();

	public:

		/// <summary>
		/// カメラシェイク
		/// </summary>
		/// <param name="swing"></param>
		/// <param name="dekey"></param>
		/// <param name="place"></param>
		void Shaking(const float swing, const float dekey, const float place);

	public:
		
		/// <summary>
		/// アニメーションの種類
		/// </summary>
		enum class AnimationType
		{
			eJump, eDrop, ePass, eNormal,
		};

		/// <summary>
		/// アニメーション再生
		/// </summary>
		/// <param name="type"> : 種類</param>
		void PlayAnimation(const AnimationType type);
	
	public:
		
		/// <summary>
		/// 位置取得
		/// </summary>
		/// <returns></returns>
		YMath::Vector3 Pos() const;

		/// <summary>
		/// ビュープロジェクション取得
		/// </summary>
		/// <returns></returns>
		ViewProjection GetViewProjection() const;
	
	public:

		/// <summary>
		/// プレイヤー位置設定
		/// </summary>
		/// <param name="playerPos"> : プレイヤー位置</param>
		void SetPlayerPos(const YMath::Vector3& playerPos);

	public:

		enum class Type
		{
			eInit,
			eNormal,
			ePass,
		};

		struct CameraPoint
		{
			// 注視点
			YMath::Vector3 target;
			// 距離
			YMath::Vector3 distance;
		};

	private:

		// 位置の種類
		Type type_ = Type::eNormal;
		
		// 位置の種類
		Type elderType_ = Type::eNormal;

		// カメラ
		Camera camera_;
		
		// 注視点
		YMath::Vector3 target_;

		// カメラ位置
		YMath::Vector3 cameraPos_;
		
		// ターゲット位置
		YMath::Vector3 targetPos_;


		// 現在のカメラポイント
		CameraPoint point_;

		// カメラ移動タイマー
		YMath::Timer pointMoveTim_;

		
		// プレイヤー位置
		YMath::Vector3 playerPos_;
		
		// 過去プレイヤー位置
		YMath::Vector3 elderPlayerPos_;

		// ジャンプ速度割合
		YMath::Timer jumpSpeedRatioTim_;


		// 落下アニメフラグ
		bool isDrop = false;
		
		// 落下アニメパワー
		YMath::Power dropAnimePow_;

	private:
		
		/// <summary>
		/// 位置更新
		/// </summary>
		void UpdatePos();

		/// <summary>
		/// 注視点更新
		/// </summary>
		void UpdateTarget();

		/// <summary>
		/// タイプ変更
		/// </summary>
		/// <param name="type"> : タイプ</param>
		void ChangeType(const Type type);

	};
}
