#include "Player.h"
#include <cassert>

using YGame::Player;

void Player::Initialize(const YMath::Vector3& pos, IPet* pPet)
{
	// 開始時は武装する
	isArmed_ = true;

}

void Player::Update()
{
	// キー or ボタン 押したら
	//if ()
	//{
	//	// ジャンプ
	//	Jump();
	//}

	// 物理計算
	IGameCharacter::UpdatePhysics();
}

void Player::Draw()
{
	// 描画
	pModel_->SetDrawCommand(obj_.get(), DrawLocation::eCenter);
}

void Player::SetPointer(IPet* pPet)
{
	// nullチェック
	assert(pPet);

	// 代入
	pPet_ = pPet;
}
