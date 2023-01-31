#pragma once
#include "ISceneFactory.h"

namespace YScene
{
	class YGameSceneFactory : public ISceneFactory
	{
	private:
		// タイトル
		const std::string Title	 = "TITLE";
		// ステージセレクト
		const std::string Select = "SELECT";
		// プレイ
		const std::string Play	 = "PLAY";
		// リザルト
		const std::string Result = "RESULT";
	public:
		// シーン生成
		BaseScene* CreateScene(const std::string& sceneName) override;
	};
}
