#pragma once
#include "BaseDrawObject.h"
#include "SlimeActor.h"

namespace YGame
{
	class UIButton :
		public SlimeActor
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="obj"> : オブジェクト (動的インスタンス)</param>
		void Initialize(BaseDrawObject* obj);

		/// <summary>
		/// 更新
		/// </summary>
		void Update();
		
		/// <summary>
		/// 押す (瞬間)
		/// </summary>
		void PressTrigger();
		
		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="shaderTag"> : シェーダータグ</param>
		/// <param name="priority"> : 描画優先度</param>
		void Draw(const std::string& shaderTag, const uint16_t priority);

	public:

		// オブジェクト
		std::unique_ptr<BaseDrawObject> obj_;
	};
}
