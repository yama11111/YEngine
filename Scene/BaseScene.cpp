#include "BaseScene.h"
#include <cassert>

#pragma region –¼‘O‹óŠÔéŒ¾

using YScene::BaseScene;
using YInput::Keys;
using YInput::Mouse;
using YInput::Pad;
using YGame::TextureManager;
using YGame::AudioManager;

#pragma endregion 

#pragma region StaticŠÖ˜A

Keys* BaseScene::keys_ = nullptr;
Mouse* BaseScene::mouse_ = nullptr;
Pad* BaseScene::pad_ = nullptr;
TextureManager* BaseScene::pTexManager_ = nullptr;
AudioManager* BaseScene::pAudioManager_ = nullptr;

void BaseScene::StaticInitialize(TextureManager* pTexManager, AudioManager* pAudioManager)
{
	assert(pTexManager);
	assert(pAudioManager);
	pTexManager_ = pTexManager;
	pAudioManager_ = pAudioManager;

	keys_ = Keys::GetInstance();
	mouse_ = Mouse::GetInstance();
	pad_ = Pad::GetInstance();
}

#pragma endregion 