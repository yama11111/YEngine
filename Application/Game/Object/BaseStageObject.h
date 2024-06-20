/**
 * @file BaseStageObject.h
 * @brief 基底ステージオブジェクトクラス
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include "GameObject.h"
#include "WorldKey.h"

namespace YGame
{
	class BaseStageObject :
		public GameObject
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="name"> : 名前</param>
		/// <param name="worldKey"> : 世界キー</param>
		/// <param name="status"> : ステータス</param>
		/// <param name="pParent"> : 親行列ポインタ</param>
		void Initialize(
			const std::string& name,
			const WorldKey worldKey,
			const Transform::Status& status);

	public:
		
		/// <summary>
		/// 世界キー設定
		/// </summary>
		/// <param name="worldKey"> : 世界キー</param>
		virtual void SetWorldKey(const WorldKey worldKey);
		
		/// <summary>
		/// ワールド座標取得
		/// </summary>
		/// <returns>ワールド座標</returns>
		YMath::Vector3 WorldPos() const override;

		/// <summary>
		/// 衝突時情報取得
		/// </summary>
		/// <returns>衝突時情報</returns>
		virtual ICollisionInfomation GetCollisionInfomation() override;
	
	public:

		BaseStageObject() = default;
		
		virtual ~BaseStageObject() = default;
	
	protected:

		// 今どの世界にいるか
		WorldKey worldKey_{};

		// 位置行列
		YMath::Matrix4 posMat_ = YMath::Matrix4::Identity();
	
	protected:

		/// <summary>
		/// 位置更新
		/// </summary>
		void UpdatePos();

	};
}
