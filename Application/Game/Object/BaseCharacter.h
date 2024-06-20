/**
 * @file BaseCharacter.h
 * @brief 基底キャラクタークラス
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include "GameObject.h"
#include "CharacterStatus.h"
#include "Speed.h"
#include "MapChipCollider.h"
#include "WorldKey.h"

namespace YGame
{
	class BaseCharacter :
		public GameObject
	{
	
	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="name"> : 名前</param>
		/// <param name="worldKey"> : 世界キー</param>
		/// <param name="trfmStatus"> : トランスフォームステータス</param>
		/// <param name="pParent"> : 親行列ポインタ</param>
		void Initialize(
			const std::string& name,
			const WorldKey worldKey, 
			const Transform::Status& trfmStatus);

		/// <summary>
		/// 衝突前更新
		/// </summary>
		virtual void UpdateBeforeCollision() override;

		/// <summary>
		/// 衝突後更新
		/// </summary>
		virtual void UpdateAfterCollision() override;

	public:

		/// <summary>
		/// 生存フラグ
		/// </summary>
		/// <returns></returns>
		inline bool IsAlive() const { return status_.IsAlive(); }

		/// <summary>
		/// キャラステータス取得
		/// </summary>
		/// <returns>キャラステータス</returns>
		inline CharacterStatus Status() const { return status_; }

		/// <summary>
		/// 属性取得
		/// </summary>
		/// <returns>属性</returns>
		inline AttributeType GetAttributeType() const { return attributeType_; }
	
		/// <summary>
		/// 衝突時情報取得
		/// </summary>
		/// <returns>衝突時情報</returns>
		virtual ICollisionInfomation GetCollisionInfomation() override;

		/// <summary>
		/// ワールド座標取得
		/// </summary>
		/// <returns>ワールド座標</returns>
		YMath::Vector3 WorldPos() const override;

	public:

		/// <summary>
		/// 世界キー設定
		/// </summary>
		/// <param name="worldKey"> : 世界キー</param>
		virtual void SetWorldKey(const WorldKey worldKey);

	public:

		BaseCharacter() = default;

		virtual ~BaseCharacter() = default;

	protected:

		// 今どの世界にいるか
		WorldKey worldKey_{};

		// 位置行列
		YMath::Matrix4 posMat_ = YMath::Matrix4::Identity();

		// 向き
		YMath::Vector3 direction_;

		// 移動方向
		YMath::Vector3 moveDirection_;

		// スピード
		YMath::Speed speed_;

		// キャラクターステータス
		CharacterStatus status_;

		// 属性
		AttributeType attributeType_ = AttributeType::eNone;

	protected:

		/// <summary>
		/// ステータス読み込み
		/// </summary>
		void LoadStatus(const std::string& name);

		/// <summary>
		/// 位置更新
		/// </summary>
		virtual void UpdatePos();

		/// <summary>
		/// 画面外処理
		/// </summary>
		virtual void OffScreenProcess();

		/// <summary>
		/// デバッグテキスト本文
		/// </summary>
		virtual void DrawDebugTextContent() override;
	};
}
