#include "BaseScene.h"
#include <cassert>

#pragma region ���O��Ԑ錾

using YScene::BaseScene;
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
	// �V���O���g��������
	spKeys_ = Keys::GetInstance();
	spMouse_ = Mouse::GetInstance();
	spPad_ = Pad::GetInstance();

	spPipelineMan_ = PipelineManager::GetInstance();
}

#pragma endregion 