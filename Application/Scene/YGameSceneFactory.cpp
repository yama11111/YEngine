#include "YGameSceneFactory.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "PlayScene.h"

#include "TestScene.h"

using YGame::YGameSceneFactory;
using YGame::BaseScene;

const std::string YGameSceneFactory::Title_		 = "TITLE";
const std::string YGameSceneFactory::Select_	 = "SELECT";
const std::string YGameSceneFactory::Play_		 = "PLAY";
const std::string YGameSceneFactory::Test_		 = "TEST";

BaseScene* YGameSceneFactory::CreateScene(const std::string& sceneName)
{
	// éüÇÃÉVÅ[ÉìÇê∂ê¨
	BaseScene* newScene = nullptr;

	if (sceneName == Title_)	{ newScene = new TitleScene(); }
	if (sceneName == Select_)	{ newScene = new SelectScene(); }
	if (sceneName == Play_)		{ newScene = new PlayScene(); }

	if (sceneName == Test_)		{ newScene = new TestScene(); }

	return newScene;
}
