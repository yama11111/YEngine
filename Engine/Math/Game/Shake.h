#pragma once
#include "Vector3.h"

namespace YMath
{
	// 揺れ
	class Shake
	{
	
	private:
		
		// 揺れているか
		bool isAct_ = false;

		// 揺れる量 (乱数)
		float swing_ = 0.0f;
		
		// 減衰量
		float dekey_ = 0.0f;

		// 位
		float place_ = 0.0f;

		// 揺れている量
		Vector3 value_{};
	
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
		/// 動作開始
		/// </summary>
		/// <param name="swing"> : 揺れる量</param>
		/// <param name="dekey"> : 減衰量</param>
		/// <param name="place"> : 小数点以下の位</param>
		void Activate(const float swing, const float dekey, const float place);
	
	public:

		/// <summary>
		/// 揺れ量取得
		/// </summary>
		/// <returns> : 揺れ量</returns>
		Vector3 Value() const { return value_; }

		/// <summary>
		/// 動作中か取得
		/// </summary>
		/// <returns> : 動作中か</returns>
		bool IsAct() const { return isAct_; }
	
	};
}