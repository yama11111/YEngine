#include "YGameSceneFactory.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "PlayScene.h"
#include "ResultScene.h"

//#include "TestScene.h"

using YGame::YGameSceneFactory;
using YGame::BaseScene;

const std::string YGameSceneFactory::Title_		 = "TITLE";
const std::string YGameSceneFactory::Select_	 = "SELECT";
const std::string YGameSceneFactory::Play_		 = "PLAY";
const std::string YGameSceneFactory::Result_	 = "RESULT";
//const std::string YGameSceneFactory::Test_		 = "TEST";

std::unique_ptr<BaseScene> YGameSceneFactory::CreateScene(const std::string& sceneName)
{
	// 次のシーンを生成
	std::unique_ptr<BaseScene> newScene;

	if (sceneName == Title_)	{ newScene = std::make_unique<TitleScene>(); }
	if (sceneName == Select_)	{ newScene = std::make_unique<SelectScene>(); }
	if (sceneName == Play_)		{ newScene = std::make_unique<PlayScene>(); }
	if (sceneName == Result_)	{ newScene = std::make_unique<ResultScene>(); }

	return std::move(newScene);
}
