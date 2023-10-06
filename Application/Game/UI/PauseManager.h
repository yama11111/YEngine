#pragma once
#include "PauseDrawer.h"

namespace YGame
{
	class PauseManager final
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();

		/// <summary>
		/// リセット
		/// </summary>
		void Reset();

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();

	public:

		/// <summary>
		/// ポーズ中か
		/// </summary>
		/// <returns>ポーズ中か</returns>
		bool IsPause() const { return isPause_; }

		/// <summary>
		/// ポーズ中だったか
		/// </summary>
		/// <returns>ポーズ中か</returns>
		bool IsElderPause() const { return isElderPause_; }

	private:

		void ChangeSelect();

		void ResumeReset();

	private:

		// ポーズ中か
		bool isPause_ = false;

		// ポーズ中だったか
		bool isElderPause_ = false;

		// 現在の選択
		PauseDrawer::Selection current_ = PauseDrawer::Selection::Resume;
	
		// 描画クラス
		PauseDrawer pauseDra_;

	};
}
