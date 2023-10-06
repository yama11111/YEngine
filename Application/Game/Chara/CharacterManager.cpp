#include "CharacterManager.h"
#include <cassert>
#include <imgui.h>

#include "AxisDrawer.h"
#include "CollisionDrawer.h"

using YGame::CharacterManager;

void CharacterManager::Initialize()
{
	Clear();
}

void CharacterManager::Update(const bool isUpdate)
{
	// �L�����N�^�[�����񂾂�폜
	characters_.remove_if([](std::unique_ptr<BaseCharacter>& character) { return character->IsAlive() == false; });

	for (std::unique_ptr<BaseCharacter>& character : characters_)
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
		updateQueue_.top().pChara_->Update(isUpdate);

		updateQueue_.pop();
	}

	// �S�L�����A�^������`�F�b�N
	CheckAllCollision();
}

void CharacterManager::DrawDebugText()
{
	static const std::string windowName = "Character";

	ImGui::SetWindowPos(windowName.c_str(), ImVec2(20.0f, 20.0f), ImGuiCond_Once);
	ImGui::SetWindowSize(windowName.c_str(), ImVec2(240.0f, 680.0f), ImGuiCond_Once);

	ImGui::Begin(windowName.c_str());

	for (std::unique_ptr<BaseCharacter>& character : characters_)
	{
		character->DrawDebugText(false);
	}
	
	ImGui::End();

	ImGui::Begin("DebugDraw");
	ImGui::Checkbox("Axis", &isDrawAxis_);
	ImGui::Checkbox("Collision", &isDrawCollision_);
	ImGui::End();

	for (std::unique_ptr<BaseCharacter>& character : characters_)
	{
		character->SubDrawerPtr(AxisDrawer::Name())->SetIsVisible(isDrawAxis_);
		character->SubDrawerPtr(CollisionDrawer::Name())->SetIsVisible(isDrawCollision_);
	}
}

void CharacterManager::Draw()
{
	for (std::unique_ptr<BaseCharacter>& character : characters_)
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

void CharacterManager::PushBack(BaseCharacter* character)
{
	// null�`�F�b�N
	assert(character);

	// �V�K�L�����N�^�[�󂯎��p
	std::unique_ptr<BaseCharacter> newCharacter;
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
	std::list<std::unique_ptr<BaseCharacter>>::iterator itrA = characters_.begin();

	// A�̏I���܂�
	for (; itrA != characters_.end(); ++itrA)
	{
		BaseCharacter* pCharaA = itrA->get();

		// B�̏���(A + 1)����
		std::list<std::unique_ptr<BaseCharacter>>::iterator itrB = itrA;
		itrB++;

		// B�̏I���܂�
		for (; itrB != characters_.end(); ++itrB)
		{
			BaseCharacter* pCharaB = itrB->get();

			// ����`�F�b�N
			CheckCollisionCharacterPair(pCharaA, pCharaB);
		}
	}
}

void CharacterManager::CheckCollisionCharacterPair(BaseCharacter* pCharacterA, BaseCharacter* pCharacterB)
{
	// ����
	if (pCharacterA->ColliderPtr()->CheckCollision(pCharacterB->ColliderPtr()))
	{
		// ���݂��ɏՓˎ�����
		pCharacterA->OnCollision(pCharacterB->GetCollisionInfo());
		pCharacterB->OnCollision(pCharacterA->GetCollisionInfo());
	}
}

