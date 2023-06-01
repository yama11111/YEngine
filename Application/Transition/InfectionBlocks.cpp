#include "InfectionBlocks.h"
#include "MathUtillity.h"
#include "Def.h"
#include <cassert>

using YScene::InfectionBlocks;
using YGame::Transform;
using YGame::Sprite2D;
using YGame::CBColor;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Clamp;

YGame::Sprite2D* InfectionBlocks::spBlockSpr_ = nullptr;
YMath::Vector2 InfectionBlocks::sLeftTop_;
YMath::Vector2 InfectionBlocks::sNum_;
YMath::Vector2 InfectionBlocks::sAnchor_;
float InfectionBlocks::sSize_ = 0.0f;

void InfectionBlocks::StaticInitialize(YGame::Texture* pBlockTex)
{
	// �X�v���C�g����
	spBlockSpr_ = Sprite2D::Create({}, { pBlockTex });

	// ����
	sLeftTop_ = {};

	// ��
	sNum_ = { 15.0f,8.0f };

	// �A���J�[�|�C���g
	sAnchor_ = { 0.0f,1.0f };

	// �傫��
	sSize_ = 128.0f;
}

void InfectionBlocks::Initialize()
{
	// �N���A + ���T�C�Y
	blocks_.clear();
	blocks_.resize(static_cast<size_t>(sNum_.y_));
	for (size_t y = 0; y < blocks_.size(); y++)
	{
		blocks_[y].resize(static_cast<size_t>(sNum_.x_));
	}

	// ������
	for (size_t y = 0; y < blocks_.size(); y++)
	{
		for (size_t x = 0; x < blocks_[y].size(); x++)
		{
			// �u���b�N���� + ������
			blocks_[y][x].reset(new Block());

			blocks_[y][x]->color_.reset(CBColor::Create({ 0.0f,0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f,1.0f }, false));
			blocks_[y][x]->obj_.reset(Sprite2D::Object::Create(Transform::Status::Default(), blocks_[y][x]->color_.get(), nullptr, false));

			// 2�u���b�N�Ԃ̋���
			Vector2 dist = { sSize_ * x, sSize_ * y };
			// �ʒu
			Vector2 p = sLeftTop_ + dist;
			// ���
			blocks_[y][x]->obj_->pos_ = { p.x_, p.y_, 0.0f };
		}
	}

	scaleEas_[0].Initialize(0.0f, sSize_, 4.0f);
	scaleEas_[1].Initialize(sSize_, 0.0f, 4.0f);

	rotaEas_[0].Initialize(-PI, 0.0f, 4.0f);
	rotaEas_[1].Initialize(0.0f, +PI, 4.0f);

	colorEas_[0].Initialize(0.7f, 0.0f, 2.0f);
	colorEas_[1].Initialize(0.0f, 0.0f, 2.0f);

	alphaEas_[0].Initialize(0.5f, 1.0f, 2.0f);
	alphaEas_[1].Initialize(1.0f, 0.5f, 2.0f);

	Reset();
}

void InfectionBlocks::Reset()
{
	// ���Z�b�g
	step_ = Step::Narrow;

	isAct_ = false;
	isFalling_ = false;
	isChangeMoment_ = false;
	isRising_ = false;
	isEnd_ = false;

	loadTim_.Reset(false);

	for (size_t y = 0; y < blocks_.size(); y++)
	{
		for (size_t x = 0; x < blocks_[y].size(); x++)
		{
			blocks_[y][x]->obj_->rota_ = {};
			blocks_[y][x]->obj_->scale_ = {};
			blocks_[y][x]->actTim_.Reset(false);
			blocks_[y][x]->colorStartTim_.Reset(false);
			blocks_[y][x]->colorEndTim_.Reset(false);
		}
	}

	stepIndex_ = 0;

	start_ = {};
}

void InfectionBlocks::Finalize()
{
}

void InfectionBlocks::Activate(const uint32_t changeFrame, const uint32_t loadFrame)
{
	// ���Z�b�g
	Reset();

	// �ǂݍ��݃^�C�}�[������
	loadTim_.Initialize(loadFrame);


	// �^�C�}�[������ + �J�n
	for (size_t y = 0; y < blocks_.size(); y++)
	{
		for (size_t x = 0; x < blocks_[y].size(); x++)
		{
			blocks_[y][x]->actTim_.Initialize(changeFrame);

			blocks_[y][x]->colorStartTim_.Initialize(changeFrame * 4);

			blocks_[y][x]->colorEndTim_.Initialize(changeFrame / 4);
		}
	}

	// ����J�n
	isAct_ = true;
	isFalling_ = true;

	// �z��� x y �̑傫��
	Vector2 size =
	{
		static_cast<float>(blocks_[0].size() - 1),
		static_cast<float>(blocks_.size() - 1)
	};


	// �A���J�[�|�C���g��̈ʒu �� �n�_ �Ƃ���
	float sX = sAnchor_.x_ * size.x_;
	float sY = sAnchor_.y_ * size.y_;

	// �n�_
	start_ = { sX,sY };

	// �n�_�̃^�C�}�[�J�n
	blocks_[static_cast<size_t>(sY)][static_cast<size_t>(sX)]->SetTimerActive(true);


	// �����̒n�_
	Vector2 halfSize =
	{
		size.x_ / 2.0f,
		size.y_ / 2.0f
	};

	// �n�_�̋t�� �� �I�_ �Ƃ���
	float eX = 0, eY = 0;
	if (sX <= halfSize.x_) { eX = size.x_; }
	if (sY <= halfSize.y_) { eY = size.y_; }

	// �I�_
	end_ = { eX, eY };
}

void InfectionBlocks::UpdateChange()
{
	// ���쒆����Ȃ��Ȃ�e��
	if (isAct_ == false) { return; }

	// �u�ԃt���O��false��
	isChangeMoment_ = false;

	// ���܂��Ă��� �Ȃ�
	if (step_ == Step::Narrow)
	{
		// �v�f�ԍ�
		size_t x = blocks_[0].size() - 1;
		size_t y = blocks_.size() - 1;

		// �^�C�}�[���I�������Ȃ�
		if (blocks_[y][x]->actTim_.IsEnd())
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
		// �ǂݍ��݃^�C�}�[�X�V
		loadTim_.Update();

		// �ǂݍ��݃^�C�}�[���I��������
		if (loadTim_.IsEnd())
		{
			// �i�K �� ���]
			step_ = Step::Spread;

			// ���i�K�̃C���f�b�N�X�� 1 ��
			stepIndex_ = 1;


			// �u�ԃt���O��false��
			isChangeMoment_ = false;

			// ���J���t���O��true��
			isRising_ = true;


			// �u���b�N���Ƃ�
			for (size_t i = 0; i < blocks_.size(); i++)
			{
				for (size_t j = 0; j < blocks_[i].size(); j++)
				{
					// �^�C�}�[���Z�b�g
					blocks_[i][j]->actTim_.Reset(false);
					blocks_[i][j]->colorStartTim_.Reset(false);
					blocks_[i][j]->colorEndTim_.Reset(false);
				}
			}

			// �v�f�ԍ�
			size_t x = static_cast<size_t>(start_.x_);
			size_t y = static_cast<size_t>(start_.y_);

			// �^�C�}�[�X�^�[�g
			blocks_[y][x]->SetTimerActive(true);
		}
	}
	// �L�����Ă��� �Ȃ�
	else if (step_ == Step::Spread)
	{
		// �u���b�N�̏I�[
		size_t x = static_cast<size_t>(end_.x_);
		size_t y = static_cast<size_t>(end_.y_);

		// �u���b�N�I�[�̃^�C�}�[���I��������
		if (blocks_[y][x]->actTim_.IsEnd())
		{
		
			// �I��
			Reset();

			// �I���t���O��true��
			isEnd_ = true;

		}
	}
}

void InfectionBlocks::PropagateBlock(const size_t x, const size_t y)
{
	// X �͈͐����p
	bool moreX = (x >= blocks_[y].size() - 1);
	bool lessX = (x <= 0);
	// Y �͈͐����p
	bool moreY = (y >= blocks_.size() - 1);
	bool lessY = (y <= 0);

	// �S�Ẵp�^�[���Ń^�C�}�[�J�n (��������)
	// �͈͓��Ȃ� �v�f + 1 or �v�f - 1
	if (!moreX) { blocks_[y][x + 1]->SetTimerActive(true); }
	if (!moreY && !moreX) { blocks_[y + 1][x + 1]->SetTimerActive(true); }
	if (!moreY) { blocks_[y + 1][x]->SetTimerActive(true); }
	if (!moreY && !lessX) { blocks_[y + 1][x - 1]->SetTimerActive(true); }
	if (!lessX) { blocks_[y][x - 1]->SetTimerActive(true); }
	if (!lessY && !lessX) { blocks_[y - 1][x - 1]->SetTimerActive(true); }
	if (!lessY) { blocks_[y - 1][x]->SetTimerActive(true); }
	if (!lessY && !moreX) { blocks_[y - 1][x + 1]->SetTimerActive(true); }
}

void InfectionBlocks::UpdateBlock()
{
	// ���쒆����Ȃ��Ȃ�e��
	if (isAct_ == false) { return; }

	// �u���b�N�̐�����
	for (size_t y = 0; y < blocks_.size(); y++)
	{
		for (size_t x = 0; x < blocks_[y].size(); x++)
		{
			// �^�C�}�[���I��������
			if (blocks_[y][x]->actTim_.IsEnd())
			{
				// �ׂ̃u���b�N�ɓ`�d
				PropagateBlock(x, y);
			}

			// �u���b�N�̃^�C�}�[�X�V
			blocks_[y][x]->actTim_.Update();
			blocks_[y][x]->colorStartTim_.Update();
			blocks_[y][x]->colorEndTim_.Update();

			// �C�[�W���O
			// stepIndex_ �� 0 �Ȃ�C�[�Y�A�E�g
			// stepIndex_ �� 1 �Ȃ�C�[�Y�C��

			// �g�k
			float s = 0.0f;
			if (stepIndex_ == 0) { s = scaleEas_[0].Out(blocks_[y][x]->actTim_.Ratio()); }
			if (stepIndex_ == 1) { s = scaleEas_[1].In(blocks_[y][x]->actTim_.Ratio()); }

			// ��]
			float r = 0.0f;
			if (stepIndex_ == 0) { r = rotaEas_[0].Out(blocks_[y][x]->actTim_.Ratio()); }
			if (stepIndex_ == 1) { r = rotaEas_[1].In(blocks_[y][x]->actTim_.Ratio()); }

			// �I�u�W�F�N�g�ɑ�� + �X�V
			blocks_[y][x]->obj_->scale_ = { s, s, 0.0f };
			blocks_[y][x]->obj_->rota_.z_ = r;

			blocks_[y][x]->obj_->UpdateMatrix();


			// �F (��)
			float blue = 0.0f;
			if (stepIndex_ == 0) { blue = colorEas_[0].Out(blocks_[y][x]->colorStartTim_.Ratio()); }
			if (stepIndex_ == 1) { blue = colorEas_[1].In(blocks_[y][x]->colorEndTim_.Ratio()); }

			// �A���t�@�l
			float alpha = 0.0f;
			if (stepIndex_ == 0) { alpha = alphaEas_[0].Out(blocks_[y][x]->colorStartTim_.Ratio()); }
			if (stepIndex_ == 1) { alpha = alphaEas_[1].In(blocks_[y][x]->colorEndTim_.Ratio()); }

			// �F���
			blocks_[y][x]->color_->SetRGBA({ 0.0f, 0.0f, blue, alpha });
		}
	}
}

void InfectionBlocks::Update()
{
	UpdateChange();
	UpdateBlock();
}

void InfectionBlocks::Draw()
{
	for (size_t y = 0; y < blocks_.size(); y++)
	{
		for (size_t x = 0; x < blocks_[y].size(); x++)
		{
			spBlockSpr_->SetDrawCommand(blocks_[y][x]->obj_.get(), YGame::DrawLocation::Front);
		}
	}
}
