#include "Player.h"
#include <cassert>

using YGame::Player;

void Player::Initialize(const YMath::Vector3& pos, IPet* pPet)
{
	// �J�n���͕�������
	isArmed_ = true;

}

void Player::Update()
{
	// �L�[ or �{�^�� ��������
	//if ()
	//{
	//	// �W�����v
	//	Jump();
	//}

	// �����v�Z
	IGameCharacter::UpdatePhysics();
}

void Player::Draw()
{
	// �`��
	pModel_->SetDrawCommand(obj_.get(), DrawLocation::eCenter);
}

void Player::SetPointer(IPet* pPet)
{
	// null�`�F�b�N
	assert(pPet);

	// ���
	pPet_ = pPet;
}
