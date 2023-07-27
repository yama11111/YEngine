#pragma once
#include "BaseDrawer.h"
namespace YGame
{
	class DefaultDrawer :
		public BaseDrawer
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		void Initialize(Transform* pParent, const uint16_t drawPriority) override;

		/// <summary>
		/// 更新
		/// </summary>
		void Update() override;

		/// <summary>
		/// 描画
		/// </summary>
		void Draw() override;

		/// <summary>
		/// アニメーション再生
		/// </summary>
		/// <param name="index"> : アニメーション番号</param>
		/// <param name="frame"> : 再生フレーム</param>
		void PlayAnimation(const uint16_t index, const uint32_t frame) override;

	public:

		DefaultDrawer() = default;

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="drawPriority"> : 描画優先度</param>
		DefaultDrawer(const uint16_t drawPriority);

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		DefaultDrawer(Transform* pParent, const uint16_t drawPriority);

		~DefaultDrawer() = default;

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void StaticInitialize();

	private:

		// モデルポインタ
		static Model* spModel_;

	};
}
