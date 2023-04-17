#pragma once
#include "ISceneFactory.h"

namespace YScene
{
	class YGameSceneFactory : public ISceneFactory
	{
	private:
		// タイトル
		const std::string Title_	 = "TITLE";
		// ステージセレクト
		const std::string Select_	 = "SELECT";
		// プレイ
		const std::string Play_		 = "PLAY";
		// リザルト
		const std::string Result_	 = "RESULT";

		// エディター
		const std::string Edit_	 = "EDIT";

		// テスト
		const std::string Test_	 = "TEST";

	public:
		// シーン生成
		BaseScene* CreateScene(const std::string& sceneName) override;
	};
}
