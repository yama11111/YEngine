#include "IGameCharacter.h"
#include "Physics.h"

using YGame::IGameCharacter;

void IGameCharacter::Jump()
{
	// �W�����v�� �� �ő�񐔒����Ă��� �e��
	if (jumpCounter_ >= maxJumpCount_) { return; }

	

	// �W�����v�J�E���g
	jumpCounter_++;
}

void IGameCharacter::UpdatePhysics()
{

}
