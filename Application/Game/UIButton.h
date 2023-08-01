#pragma once
#include "BaseDrawObject.h"

namespace YGame
{
	class UIButton
	{

	public:

		/// <summary>
		/// 動的インスタンス生成
		/// </summary>
		/// <param name="obj"> : オブジェクト (動的インスタンス)</param>
		/// <param name="isClearWhenTransition"> : 遷移時クリアするか</param>
		/// <returns>動的インスタンス</returns>
		static UIButton* Create(BaseDrawObject* obj, const bool isClearWhenTransition = true);

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="obj"> : オブジェクト (動的インスタンス)</param>
		/// <param name="isClearWhenTransition"> : 遷移時クリアするか</param>
		virtual void Initialize(BaseDrawObject* obj, const bool isClearWhenTransition = true) = 0;

		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="isDown"> : 押しているか</param>
		virtual void Update(const bool isDown) = 0;
		
		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="shaderTag"> : シェーダータグ</param>
		/// <param name="priority"> : 描画優先度</param>
		virtual void Draw(const std::string& shaderTag, const uint16_t priority) = 0;
	
	public:

		UIButton() = default;
		
		virtual ~UIButton() = default;

	};
}
