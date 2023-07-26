#include "Blackout.h"
#include "Def.h"
#include "PipelineManager.h"
#include "MathVector.h"

using YScene::Blackout;
using YGame::PipelineManager;
using YGame::Transform;
using YGame::Object;
using YGame::Sprite2D;
using YGame::Texture;
using YGame::ConstBuffer;
using YGame::CBSprite2DTransform;
using YGame::CBColor;
using YGame::CBTexConfig;
using YMath::Vector2;

YGame::Sprite2D* Blackout::spCurtenSpr_ = nullptr;
YMath::Ease<float> Blackout::sBlendEas_;

void Blackout::StaticInitialize()
{
	// �e�N�X�`���ǂݍ���
	Texture* pTex = Texture::Load("white1x1.png", false);
	
	// �X�v���C�g����
	spCurtenSpr_ = Sprite2D::Create({ {"Texture0", pTex} });

	// ���߃C�[�W���O������
	sBlendEas_.Initialize(0.0f, 1.0f, 3.0f);
}

void Blackout::Initialize()
{
	// ������
	transform_.reset(new Transform());
	obj_.reset(new Object());
	cbTransform_.reset(ConstBuffer<CBSprite2DTransform>::Create(false));
	obj_->InsertConstBuffer(cbTransform_.get());
	cbColor_.reset(ConstBuffer<CBColor>::Create(false));
	obj_->InsertConstBuffer(cbColor_.get());
	cbTexConfig_.reset(ConstBuffer<CBTexConfig>::Create(false));
	obj_->InsertConstBuffer(cbTexConfig_.get());

	obj_->SetGraphic(spCurtenSpr_);

	Reset();
}

void Blackout::Finalize()
{
}

void Blackout::Reset()
{
	// ���Z�b�g
	step_ = Step::Dark;
	
	isAct_ = false;
	isFalling_ = false;
	isChangeMoment_ = false;
	isRising_ = false;
	isEnd_ = false;
	loadTim_.Reset(false);

	blendPow_.Reset();

	// ��ʒ���
	Vector2 p = WinSize / 2.0f;
	transform_->pos_ = { p.x_, p.y_, 0.0f };
	transform_->scale_ = { WinSize.x_, WinSize.y_, 0.0f };
	transform_->UpdateMatrix();
	cbTransform_->data_.matWorld = transform_->m_ * YMath::MatOrthoGraphic();
	
	cbColor_->data_.baseColor = { 0.0f,0.0f,0.0f,0.0f };
}

void Blackout::Activate(const uint32_t changeFrame, const uint32_t loadFrame)
{
	// ���Z�b�g
	Reset();
	
	// ����J�n
	isAct_ = true;
	isFalling_ = true;

	blendPow_.Initialize(changeFrame);

	loadTim_.Initialize(loadFrame);
}

void Blackout::UpdateChange()
{
	// ���쒆����Ȃ��Ȃ�e��
	if (isAct_ == false) { return; }

	// �u�ԃt���O��false��
	isChangeMoment_ = false;
	
	// �u�����h����(�Ó])�t���O
	bool act = false;

	// �Ó]�� �Ȃ�
	if (step_ == Step::Dark)
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
			step_ = Step::Bright;


			// �u�ԃt���O��false��
			isChangeMoment_ = false;

			// ���J���t���O��true��
			isRising_ = true;
		}
	}
	// ���]�� �Ȃ�
	else if (step_ == Step::Bright)
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

void Blackout::UpdateBlend()
{
	// ���쒆����Ȃ��Ȃ�e��
	if (isAct_ == false) { return; }

	// �u�����h�l������
	float blendVal = 0.0f;
	
	// �Ó] or �ǂݍ��ݒ� �Ȃ�
	if (step_ == Step::Dark || step_ == Step::Load)
	{
		// �C�[�Y�C��
		blendVal = sBlendEas_.In(blendPow_.Ratio());
	}
	// ���]�� �Ȃ�
	else if (step_ == Step::Bright)
	{
		// �C�[�Y�A�E�g
		blendVal = sBlendEas_.Out(blendPow_.Ratio());
	}

	// �F�ύX
	cbColor_->data_.baseColor = { 0.0f,0.0f,0.0f,blendVal };
}

void Blackout::Update()
{
	UpdateChange();
	UpdateBlend();
}

void Blackout::Draw()
{
	PipelineManager::GetInstance()->EnqueueDrawSet("Sprite2DDefault", 2, obj_.get());
}
