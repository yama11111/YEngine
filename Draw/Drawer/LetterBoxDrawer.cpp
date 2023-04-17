#include "LetterBoxDrawer.h"
#include "Def.h"
#include <cassert>

using YGame::LetterBoxDrawerCommon;
using YGame::LetterBoxDrawer;
using YGame::Texture;
using YGame::Sprite2DObject;
using YGame::Sprite2D;
using YGame::Color;

Sprite2D* LetterBoxDrawerCommon::spSpr_ = nullptr;

void LetterBoxDrawerCommon::StaticInitialize()
{
	// �e�N�X�`���擾 (��1x1)
	Texture* pTex = Texture::Load("white1x1.png", false);

	// �X�v���C�g�쐬
	spSpr_ = Sprite2D::Create({ false, { WinSize.x_, 1.0f } }, { pTex });
}

void LetterBoxDrawer::Initialize(const float topHeight, const float bottomHeight)
{
	// 0�ǂ��������Ȃ�e��
	assert(topHeight_ >= 0);
	assert(bottomHeight_ >= 0);

	// ���
	topHeight_ = topHeight;
	bottomHeight_ = bottomHeight;

	// ----- ���� ----- //
	
	// �F����
	color_.reset(Color::Create());

	// �� (�� : �E�B���h�E�A�ʒu : �w��)
	sprObjs_[0].reset(Sprite2DObject::Create({}, color_.get()));
	// �� (�� : �E�B���h�E�A�ʒu : �E�B���h�E - �w��)
	sprObjs_[1].reset(Sprite2DObject::Create({}, color_.get()));

	// ���Z�b�g
	Reset();
}

void LetterBoxDrawer::Reset()
{
	// �F������ (��)
	color_->SetRGBA({ 0.0f,0.0f,0.0f,1.0f });
	
	// ----- �I�u�W�F�N�g������ ----- //
	
	// �� (�� : �E�B���h�E�A�ʒu : �w��)
	sprObjs_[0]->Initialize(
		{
			{ 0.0f, +topHeight_ / 2.0f, 0.0f },
			{},
			{ WinSize.x_, topHeight_, 0.0f }
		}
	);
	// �� (�� : �E�B���h�E�A�ʒu : �E�B���h�E - �w��)
	sprObjs_[1]->Initialize(
		{
			{ 0.0f, WinSize.y_ - (bottomHeight_ / 2.0f), 0.0f },
			{},
			{ WinSize.x_, bottomHeight_, 0.0f }
		}
	);
}

void LetterBoxDrawer::Update()
{
	// �X�V
	for (size_t i = 0; i < sprObjs_.size(); i++)
	{
		sprObjs_[i]->UpdateMatrix();
	}
}

void LetterBoxDrawer::Draw()
{
	// �`��
	for (size_t i = 0; i < sprObjs_.size(); i++)
	{
		spSpr_->Draw(sprObjs_[i].get());
	}
}
