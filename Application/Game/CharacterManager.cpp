#include "CharacterManager.h"
#include <cassert>
#include <imgui.h>

using YGame::CharacterManager;

void CharacterManager::Initialize()
{
	Clear();
}

void CharacterManager::Update()
{
	// �L�����N�^�[�����񂾂�폜
	characters_.remove_if([](std::unique_ptr<ICharacter>& character) { return character->IsAlive() == false; });

	for (std::unique_ptr<ICharacter>& character : characters_)
	{
		uint16_t priority = 0;
		if (character->ColliderPtr()->Attribute() == AttributeType::ePet)
		{
			priority = 1;
		}

		updateQueue_.push({ character.get(), priority });
	}

	while (true)
	{		
		// ��ɂȂ�����I��
		if (updateQueue_.empty()) { break; }

		// �ォ�珇�ɍX�V
		updateQueue_.top().pChara_->Update();

		updateQueue_.pop();
	}

	// �S�L�����A�^������`�F�b�N
	CheckAllCollision();
}

void CharacterManager::DrawDebugText()
{
	static const std::string windowName = "Game";

	ImGui::SetWindowPos(windowName.c_str(), ImVec2(20.0f, 20.0f), ImGuiCond_Once);
	ImGui::SetWindowSize(windowName.c_str(), ImVec2(240.0f, 680.0f), ImGuiCond_Once);

	ImGui::Begin(windowName.c_str());

	for (std::unique_ptr<ICharacter>& character : characters_)
	{
		character->DrawDebugText(false);
	}
	
	ImGui::End();
}

void CharacterManager::Draw()
{
	for (std::unique_ptr<ICharacter>& character : characters_)
	{
		character->Draw();
	}
}

void CharacterManager::Clear()
{
	if (characters_.empty() == false)
	{
		// �S�폜
		characters_.clear();
	}
}

void CharacterManager::PushBack(ICharacter* character)
{
	// null�`�F�b�N
	assert(character);

	// �V�K�L�����N�^�[�󂯎��p
	std::unique_ptr<ICharacter> newCharacter;
	newCharacter.reset(character);

	// �}��
	characters_.push_back(std::move(newCharacter));
}

CharacterManager* CharacterManager::GetInstance()
{
	static CharacterManager instance;
	return &instance;
}

void CharacterManager::CheckAllCollision()
{
	// A�̎n�߂���
	std::list<std::unique_ptr<ICharacter>>::iterator itrA = characters_.begin();

	// A�̏I���܂�
	for (; itrA != characters_.end(); ++itrA)
	{
		ICharacter* pCharaA = itrA->get();

		// B�̏���(A + 1)����
		std::list<std::unique_ptr<ICharacter>>::iterator itrB = itrA;
		itrB++;

		// B�̏I���܂�
		for (; itrB != characters_.end(); ++itrB)
		{
			ICharacter* pCharaB = itrB->get();

			// ����`�F�b�N
			CheckCollisionCharacterPair(pCharaA, pCharaB);
		}
	}
}

void CharacterManager::CheckCollisionCharacterPair(ICharacter* pCharacterA, ICharacter* pCharacterB)
{
	// ����
	if (pCharacterA->ColliderPtr()->CheckCollision(pCharacterB->ColliderPtr()))
	{
		// ���݂��ɏՓˎ�����
		pCharacterA->OnCollision(pCharacterB->GetCollisionInfo());
		pCharacterB->OnCollision(pCharacterA->GetCollisionInfo());
	}
}

