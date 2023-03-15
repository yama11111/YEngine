#include "BaseScene.h"
#include <cassert>

#pragma region ���O��Ԑ錾

using YScene::BaseScene;
using YInput::Keys;
using YInput::Mouse;
using YInput::Pad;
using YGame::TextureManager;
using YGame::AudioManager;
using YGame::WorldRuler;

#pragma endregion 

#pragma region Static�֘A

Keys* BaseScene::sKeys_ = nullptr;
Mouse* BaseScene::sMouse_ = nullptr;
Pad* BaseScene::sPad_ = nullptr;
WorldRuler* BaseScene::spWorldRuler_ = nullptr;
TextureManager* BaseScene::spTexManager_ = nullptr;
AudioManager* BaseScene::spAudioManager_ = nullptr;

void BaseScene::StaticInitialize(
	YGame::TextureManager* pTexManager,
	YGame::AudioManager* pAudioManager,
	YGame::WorldRuler* pWorldRuler)
{
	// null�`�F�b�N
	assert(pTexManager);
	assert(pAudioManager);

	// �V���O���g��������
	sKeys_ = Keys::GetInstance();
	sMouse_ = Mouse::GetInstance();
	sPad_ = Pad::GetInstance();

	// �|�C���^���
	spTexManager_ = pTexManager;
	spAudioManager_ = pAudioManager;
	spWorldRuler_ = pWorldRuler;
}

#pragma endregion 