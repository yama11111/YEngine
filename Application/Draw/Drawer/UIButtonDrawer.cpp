#include "UIButtonDrawer.h"

using YGame::UIButtonDrawer;

void UIButtonDrawer::Initialize(Texture* pButtonTex, Texture* pPressedTex, Texture* pDeadTex)
{
	// ----- �X�v���C�g���� ----- //

	// �{�^��
	pButtonSpr_[0] = Sprite2D::Create({}, { pButtonTex });

	// �����ꂽ�{�^��
	pButtonSpr_[1] = Sprite2D::Create({}, { pPressedTex });

	// ���񂾃{�^��
	if (pDeadTex)
	{
		pDeadButtonSpr_ = Sprite2D::Create({}, { pDeadTex });
	}

	// ----- ���̑� ----- //

	// �����ꂽ��
	isPush_ = false;

	// �����Ȃ���
	isDead_ = false;
}

void UIButtonDrawer::Update(const bool isPush)
{
	// �t���O�X�V
	isPush_ = isPush;
}

void UIButtonDrawer::Draw(Sprite2D::Object* pObject)
{
	// �{�^���`��
	pButtonSpr_[isPush_]->SetDrawCommand(pObject, DrawLocation::Front);

	// ����ł�����
	if (isDead_)
	{
		// �f�b�h�{�^���`��
		pDeadButtonSpr_->SetDrawCommand(pObject, DrawLocation::Front);
	}
}

void UIButtonDrawer::SetIsDead(const bool isDead)
{
	// ����Ȃ�
	if (pDeadButtonSpr_)
	{
		// ���
		isDead_ = isDead;
	}
}
