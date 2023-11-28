#pragma once
#include "BaseDrawer.h"
namespace YGame
{
	class GoalDrawer final :
		public BaseDrawer
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		/// <returns>プレイヤー描画クラスポインタ (動的インスタンス)</returns>
		static std::unique_ptr<GoalDrawer> Create(Transform* pParent, const size_t drawPriority);

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void LoadResource();

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		void Initialize(Transform* pParent, const size_t drawPriority) override;

	public:

		GoalDrawer() = default;

		~GoalDrawer() = default;

	private:

	private:

		/// <summary>
		/// オブジェクト初期化
		/// </summary>
		void InitializeObjects() override;
	};
}
