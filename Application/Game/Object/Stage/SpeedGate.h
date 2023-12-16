#pragma once
#include "GameObject.h"

namespace YGame
{
	class SpeedGate final :
		public GameObject
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="status"> : トランスフォーム情報</param>
		/// <returns>動的インスタンス</returns>
		static std::unique_ptr<SpeedGate>Create(
			const Transform::Status& status,
			GameObject* pParent = nullptr);

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="status"> : トランスフォーム情報</param>
		/// <param name="pParent"> : 親ポインタ</param>
		void Initialize(
			const Transform::Status& status,
			GameObject* pParent = nullptr);

	public:

		/// <summary>
		/// 衝突前更新
		/// </summary>
		virtual void UpdateBeforeCollision();

		/// <summary>
		/// 衝突後更新
		/// </summary>
		virtual void UpdateAfterCollision();

	public:

		SpeedGate() = default;

		~SpeedGate() = default;

	private:

		/// <summary>
		/// 衝突時情報取得
		/// </summary>
		/// <returns>衝突時情報</returns>
		InfoOnCollision GetInfoOnCollision() override;

		/// <summary>
		/// 衝突時処理
		/// </summary>
		/// <param name="info"> : 衝突情報</param>
		void OnCollision(const InfoOnCollision& info) override;

	};
}

