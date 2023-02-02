#pragma once
#include "YFramework.h"

namespace YBase
{
	class MyGame : public YFramework
	{
	public:
		// 初期化
		bool Initialize() override;
		// 終了処理
		void Finalize() override;
		// 更新
		void Update() override;
		// 描画
		void Draw() override;
	};
}
