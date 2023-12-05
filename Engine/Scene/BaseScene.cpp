#include "BaseScene.h"
#include <cassert>

#pragma region 名前空間宣言

using YGame::BaseScene;
using YInput::Keys;
using YInput::Mouse;
using YInput::Pad;
using YGame::PipelineManager;
using YGame::Texture;
using YGame::Audio;

#pragma endregion 

#pragma region Static

Keys* BaseScene::spKeys_ = nullptr;
Mouse* BaseScene::spMouse_ = nullptr;
Pad* BaseScene::spPad_ = nullptr;

PipelineManager* BaseScene::spPipelineMan_ = nullptr;

void BaseScene::StaticInitialize()
{
	// シングルトン初期化
	spKeys_ = Keys::GetInstance();
	spMouse_ = Mouse::GetInstance();
	spPad_ = Pad::GetInstance();

	spPipelineMan_ = PipelineManager::GetInstance();
}

#pragma endregion 