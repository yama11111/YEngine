#pragma once

namespace YGame
{
	class PauseSelection
	{
	
	public:

		// タイトルシーン用
		enum class TitleScene
		{
			Resume,		// 戻る
			ReStart,	// リスタート
			Change,		// 遷移
			End, // リサイズ用
		};

		// セレクトシーン用
		enum class SelectScene
		{
			Resume,		// 戻る
			ReStart,	// リスタート
			Change,		// 遷移
			End, // リサイズ用
		};

		// プレイシーン用
		enum class PlayScene
		{
			Resume,		// 戻る
			ReStart,	// リスタート
			Change,		// 遷移
			End, // リサイズ用
		};
	};
}