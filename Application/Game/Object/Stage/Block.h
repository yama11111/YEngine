#pragma once
#include "BaseStageObject.h"

namespace YGame
{
	class Block final :
		public BaseStageObject
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="status"> : トランスフォーム情報</param>
		/// <param name="key"> : キー</param>		
		/// <param name="isBackground"> : 背景フラグ</param>
		/// <returns>動的インスタンス</returns>
		static std::unique_ptr<Block>Create(
			const Transform::Status& status, const WorldKey key, const bool isBackground);

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="status"> : トランスフォーム情報</param>
		/// <param name="key"> : キー</param>
		/// <param name="isBackground"> : 背景フラグ</param>
		void Initialize(const Transform::Status& status, const WorldKey key, const bool isBackground);
	
	public:
		
		/// <summary>
		/// 衝突前更新
		/// </summary>
		void UpdateBeforeCollision() override;
		
		/// <summary>
		/// 衝突後更新
		/// </summary>
		void UpdateAfterCollision() override;
	
	public:

		Block() = default;
		
		~Block() = default;

	private:

		/// <summary>
		/// 衝突時情報取得
		/// </summary>
		/// <returns>衝突時情報</returns>
		ICollisionInfomation GetCollisionInfomation() override;
	};
}

