#pragma once
#include "UIButton.h"
#include "UILetterBox.h"

namespace YGame
{
	class UIManager final
	{

	public:

		void Initialize();

		void Update();
		
		void StartAnimation();

		void Draw();
	
	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void StaticIntialize();

	public:

		// ジャンプボタン
		std::unique_ptr<UIButton> buttonJump_;
		
		// ジャンプUI
		std::unique_ptr<BaseDrawObject> jumpUI_;
		

		// 攻撃ボタン
		std::unique_ptr<UIButton> buttonAttack_;

		// 攻撃UI
		std::unique_ptr<BaseDrawObject> attackUI_;
		
		
		// レターボックス
		std::unique_ptr<UILetterBox> letterBox_;


		// 開始できるか
		bool isStartable_ = false;
	};
}

