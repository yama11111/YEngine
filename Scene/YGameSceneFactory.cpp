#include "YGameSceneFactory.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "PlayScene.h"
#include "ResultScene.h"

using YScene::YGameSceneFactory;
using YScene::BaseScene;

BaseScene* YGameSceneFactory::CreateScene(const std::string& sceneName)
{
	// éüÇÃÉVÅ[ÉìÇê∂ê¨
	BaseScene* newScene = nullptr;

	if (sceneName == Title)		{ newScene = new TitleScene(); }
	if (sceneName == Select)	{ newScene = new SelectScene(); }
	if (sceneName == Play)		{ newScene = new PlayScene(); }
	if (sceneName == Result)	{ newScene = new ResultScene(); }

	return newScene;
}
