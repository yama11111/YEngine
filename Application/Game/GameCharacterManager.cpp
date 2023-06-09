#include "GameCharacterManager.h"
#include <cassert>

using YGame::GameCharacterManager;

void GameCharacterManager::Initialize()
{
	Clear();
	collMan_.Initialize();
}

void GameCharacterManager::Update()
{
	// �I�u�W�F�N�gnull�Ȃ�폜
	characters_.remove_if([](std::unique_ptr<IGameCharacter>& character) { return character->IsAlive(); });

	for (std::unique_ptr<IGameCharacter>& character : characters_)
	{
		// ����O�X�V
		character->Update();

		// �A�^������}�l�[�W���[�ɐς�
		collMan_.PushBack(character.get());
	}

	// �A�^������}�l�[�W���[���X�V
	collMan_.Update();
}

void GameCharacterManager::Draw()
{
	for (std::unique_ptr<IGameCharacter>& character : characters_)
	{
		// �`��
		character->Draw();
	}
}

void GameCharacterManager::Clear()
{
	// �I�u�W�F�N�g�S�폜
	if (characters_.empty() == false)
	{
		characters_.clear();
	}
}

void GameCharacterManager::PushBack(IGameCharacter* character)
{
	// null�`�F�b�N
	assert(character);

	// �V�K�L�����N�^�[
	std::unique_ptr<IGameCharacter> newCharacter;
	
	// �L�����N�^�[���Z�b�g
	newCharacter.reset(character);

	// �}��
	characters_.push_back(std::move(newCharacter));
}
