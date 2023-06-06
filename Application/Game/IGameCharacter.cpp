#include "IGameCharacter.h"
#include "Physics.h"

using YGame::IGameCharacter;

void IGameCharacter::Jump()
{
	// ジャンプ回数 が 最大回数超えてたら 弾く
	if (jumpCounter_ >= maxJumpCount_) { return; }

	

	// ジャンプカウント
	jumpCounter_++;
}

void IGameCharacter::UpdatePhysics()
{

}
