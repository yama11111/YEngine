#include "YGameSceneFactory.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "PlayScene.h"

#include "TestScene.h"

using YScene::YGameSceneFactory;
using YScene::BaseScene;

const std::string YGameSceneFactory::Title_		 = "TITLE";
const std::string YGameSceneFactory::Select_	 = "SELECT";
const std::string YGameSceneFactory::Play_		 = "PLAY";
const std::string YGameSceneFactory::Test_		 = "TEST";

BaseScene* YGameSceneFactory::CreateScene(const std::string& sceneName)
{
	// ���̃V�[���𐶐�
	BaseScene* newScene = nullptr;

	if (sceneName == Title_)	{ newScene = new TitleScene(); }
	if (sceneName == Select_)	{ newScene = new SelectScene(); }
	if (sceneName == Play_)		{ newScene = new PlayScene(); }

	if (sceneName == Test_)		{ newScene = new TestScene(); }

	return newScene;
}
