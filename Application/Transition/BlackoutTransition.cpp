#include "BlackoutTransition.h"
#include "Def.h"
#include "PipelineManager.h"
#include "MathVector.h"

using YGame::BlackoutTransition;
using YMath::Vector2;

YGame::Sprite2D* BlackoutTransition::spCurtenSpr_ = nullptr;
YMath::Ease<float> BlackoutTransition::sBlendEas_;

void BlackoutTransition::LoadResource()
{
	// �e�N�X�`���ǂݍ���
	Texture* pTex = Texture::Load("white1x1.png", false);
	
	// �X�v���C�g����
	spCurtenSpr_ = Sprite2D::Create({ {"Texture0", pTex} });

	// ���߃C�[�W���O������
	sBlendEas_.Initialize(0.0f, 1.0f, 3.0f);
}

void BlackoutTransition::Initialize()
{
	if (obj_ == nullptr)
	{
		obj_.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), spCurtenSpr_, false));
	}
	if (cbColor_ == nullptr)
	{
		cbColor_.reset(ConstBufferObject<CBColor>::Create(false));
		obj_->InsertConstBuffer(cbColor_.get());
	}

	Reset();
}

void BlackoutTransition::Finalize()
{
}

void BlackoutTransition::Reset()
{
	BaseTransition::Reset();

	blendPow_.Reset();

	// ��ʒ���
	Vector2 p = WinSize / 2.0f;
	obj_->transform_.pos_ = { p.x_, p.y_, 0.0f };
	obj_->transform_.scale_ = { WinSize.x_, WinSize.y_, 0.0f };
	obj_->Update();
	
	cbColor_->data_.baseColor = { 0.0f,0.0f,0.0f,0.0f };
}

void BlackoutTransition::Activate(const uint32_t changeFrame, const uint32_t loadFrame)
{
	// ���Z�b�g
	Reset();
	
	// ����J�n
	isAct_ = true;
	isFalling_ = true;

	blendPow_.Initialize(changeFrame);

	loadTim_.Initialize(loadFrame);
}

void BlackoutTransition::UpdateChange()
{
	// ���쒆����Ȃ��Ȃ�e��
	if (isAct_ == false) { return; }

	// �u�ԃt���O��false��
	isChangeMoment_ = false;
	
	// �u�����h����(�Ó])�t���O
	bool act = false;

	// �Ó]�� �Ȃ�
	if (step_ == Step::Close)
	{
		// �u�����h����
		act = true;
		
		// �u�����h���ő�(�^����)�Ȃ�
		if (blendPow_.IsMax())
		{
			// �i�K �� �ǂݍ���
			step_ = Step::Load;
			
			
			// ���J���t���O��tfalse��
			isFalling_ = false;

			// �u�ԃt���O��true��
			isChangeMoment_ = true;
			
			
			// �ǂݍ��݃^�C�}�[�J�n
			loadTim_.SetActive(true);
		}
	}
	// �ǂݍ��ݒ� �Ȃ�
	else if (step_ == Step::Load)
	{
		// �u�����h����
		act = true;
		
		// �ǂݍ��݃^�C�}�[�X�V
		loadTim_.Update();
		
		// �ǂݍ��݃^�C�}�[���I��������
		if (loadTim_.IsEnd())
		{
			// �i�K �� ���]
			step_ = Step::Open;


			// �u�ԃt���O��false��
			isChangeMoment_ = false;

			// ���J���t���O��true��
			isRising_ = true;
		}
	}
	// ���]�� �Ȃ�
	else if (step_ == Step::Open)
	{
		// �u�����h���Ȃ�
		act = false;
		
		// �u�����h���ŏ�(����) �Ȃ�
		if (blendPow_.IsZero())
		{
			
			// ���Z�b�g
			Reset();
			
			// �I���t���O��true��
			isEnd_ = true;
		
		}
	}

	// �u�����h�l�X�V
	blendPow_.Update(act);
}

void BlackoutTransition::UpdateBlend()
{
	// ���쒆����Ȃ��Ȃ�e��
	if (isAct_ == false) { return; }

	// �u�����h�l������
	float blendVal = 0.0f;
	
	// �Ó] or �ǂݍ��ݒ� �Ȃ�
	if (step_ == Step::Close || step_ == Step::Load)
	{
		// �C�[�Y�C��
		blendVal = sBlendEas_.In(blendPow_.Ratio());
	}
	// ���]�� �Ȃ�
	else if (step_ == Step::Open)
	{
		// �C�[�Y�A�E�g
		blendVal = sBlendEas_.Out(blendPow_.Ratio());
	}

	// �F�ύX
	cbColor_->data_.baseColor = { 0.0f,0.0f,0.0f,blendVal };
}

void BlackoutTransition::Update()
{
	UpdateChange();
	UpdateBlend();
}

void BlackoutTransition::Draw()
{
	obj_->Draw("Sprite2DDefault", 0);
}