#include "BaseScene.h"
#include <cassert>

#pragma region ���O��Ԑ錾

using YScene::BaseScene;
using YInput::Keys;
using YInput::Mouse;
using YInput::Pad;
using YGame::Texture;
using YGame::Audio;

#pragma endregion 

#pragma region Static

Keys* BaseScene::sKeys_ = nullptr;
Mouse* BaseScene::sMouse_ = nullptr;
Pad* BaseScene::sPad_ = nullptr;

void BaseScene::StaticInitialize()
{
	// �V���O���g��������
	sKeys_ = Keys::GetInstance();
	sMouse_ = Mouse::GetInstance();
	sPad_ = Pad::GetInstance();
}

#pragma endregion 