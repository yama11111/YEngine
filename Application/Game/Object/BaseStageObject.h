#pragma once
#include "GameObject.h"

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
			const std::string& worldKey,
			const Transform::Status& status, 
			YMath::Matrix4* pParent);

		/// <summary>
		/// 世界キー設定
		/// </summary>
		/// <param name="worldKey"> : 世界キー</param>
		virtual void SetWorldKey(const std::string& worldKey);

		/// <summary>
		/// 位置更新
		/// </summary>
		void UpdatePos();
		
		/// <summary>
		/// ワールド座標取得
		/// </summary>
		/// <returns>ワールド座標</returns>
		YMath::Vector3 WorldPos() const override;
	
	protected:

		// 今どの世界にいるか
		std::string worldKey_;

		// 位置行列
		YMath::Matrix4 posMat_ = YMath::Matrix4::Identity();

	};
}
