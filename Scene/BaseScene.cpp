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
using YGame::ViewProjection;
using YGame::LightGroup;
using YGame::Sprite2DObjectCommon;
using YGame::Sprite3DObjectCommon;
using YGame::ModelObjectCommon;

#pragma endregion 

#pragma region Static

Keys* BaseScene::sKeys_ = nullptr;
Mouse* BaseScene::sMouse_ = nullptr;
Pad* BaseScene::sPad_ = nullptr;
WorldRuler* BaseScene::spWorldRuler_ = nullptr;
TextureManager* BaseScene::spTexManager_ = nullptr;
AudioManager* BaseScene::spAudioManager_ = nullptr;

void BaseScene::StaticInitialize(YGame::WorldRuler* pWorldRuler)
{
	// null�`�F�b�N
	assert(pWorldRuler);

	// �V���O���g��������
	sKeys_ = Keys::GetInstance();
	sMouse_ = Mouse::GetInstance();
	sPad_ = Pad::GetInstance();

	spTexManager_ = TextureManager::GetInstance();
	spAudioManager_ = AudioManager::GetInstance();
	
	// �|�C���^���
	spWorldRuler_ = pWorldRuler;
}

#pragma endregion 