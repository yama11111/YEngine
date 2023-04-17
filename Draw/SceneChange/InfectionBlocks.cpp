#include "InfectionBlocks.h"
#include "MathUtillity.h"
#include "Def.h"
#include <cassert>

using YGame::InfectionBlocks;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Clamp;

YGame::Sprite2D* InfectionBlocks::spBlockSpr_ = nullptr;

void InfectionBlocks::StaticInitialize()
{
	// �e�N�X�`���ǂݍ���
	Texture* pTex = Texture::Load("white1x1.png", false);

	// �X�v���C�g����
	spBlockSpr_ = Sprite2D::Create({}, { pTex });
}

void InfectionBlocks::Initialize(
	const uint32_t changeFrame, const uint32_t loadFrame, 
	const YMath::Vector2& leftTop, const float size, const YMath::Vector2& num, 
	const YMath::Vector2& anchor)
{
	// �v�f���� 0���� �Ȃ�e��
	assert(num.x_ > 0 && num.y_ > 0);

	// �N���A + ���T�C�Y
	blocks_.clear();
	blocks_.resize(static_cast<size_t>(num.y_));
	for (size_t y = 0; y < blocks_.size(); y++)
	{
		blocks_[y].resize(static_cast<size_t>(num.x_));
	}

	// ������
	for (size_t y = 0; y < blocks_.size(); y++)
	{
		for (size_t x = 0; x < blocks_[y].size(); x++)
		{
			// 2�u���b�N�Ԃ̋���
			Vector2 dist = { size * x, size * y };

			// �ʒu
			Vector2 p = leftTop + dist;

			// �u���b�N���� + ������
			blocks_[y][x].reset(new Block());

			blocks_[y][x]->color_.reset(Color::Create({ 0.0f,0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f,1.0f }, false));
			blocks_[y][x]->obj_.reset(Sprite2DObject::Create({}, blocks_[y][x]->color_.get(), false));
			blocks_[y][x]->obj_->pos_ = { p.x_, p.y_, 0.0f };
			blocks_[y][x]->actTim_.Initialize(changeFrame);
			blocks_[y][x]->colorStartTim_.Initialize(changeFrame * 4);
			blocks_[y][x]->colorEndTim_.Initialize(changeFrame / 4);
		}
	}

	scaleEas_[0].Initialize(0.0f, size, 4.0f);
	scaleEas_[1].Initialize(size, 0.0f, 4.0f);

	rotaEas_[0].Initialize(-PI, 0.0f, 4.0f);
	rotaEas_[1].Initialize(0.0f, +PI, 4.0f);

	colorEas_[0].Initialize(0.8f, 0.0f, 2.0f);
	colorEas_[1].Initialize(0.0f, 0.0f, 2.0f);
	
	alphaEas_[0].Initialize(0.5f, 1.0f, 2.0f);
	alphaEas_[1].Initialize(1.0f, 0.5f, 2.0f);

	loadTim_.Initialize(loadFrame);

	SetAnchorPoint(anchor);

	Reset();
}

void InfectionBlocks::Reset()
{
	// ���Z�b�g
	step_ = Step::Narrow;

	isAct_ = false;
	isPreChange_ = false;
	isChangeMoment_ = false;
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

void InfectionBlocks::Activate()
{
	// ���Z�b�g
	Reset();

	// ����J�n
	isAct_ = true;
	isPreChange_ = true;

	// �z��� x y �̑傫��
	Vector2 size =
	{
		static_cast<float>(blocks_[0].size() - 1),
		static_cast<float>(blocks_.size() - 1)
	};


	// �A���J�[�|�C���g��̈ʒu �� �n�_ �Ƃ���
	float sX = anchor_.x_ * size.x_;
	float sY = anchor_.y_ * size.y_;

	// �n�_�̃^�C�}�[�J�n
	blocks_[static_cast<size_t>(sY)][static_cast<size_t>(sX)]->SetTimerActive(true);

	// �n�_
	start_ = { sX,sY };


	// �����̒n�_
	size_t halfSizeX = static_cast<size_t>(size.x_ / 2.0f);
	size_t halfSizeY = static_cast<size_t>(size.y_ / 2.0f);

	// �n�_�̋t�� �� �I�_ �Ƃ���
	size_t eX = 0, eY = 0;
	if (sX <= halfSizeX) { eX = static_cast<size_t>(size.x_); }
	if (sY <= halfSizeY) { eY = static_cast<size_t>(size.y_); }

	// �I�_
	end_ =
	{
		static_cast<float>(eX),
		static_cast<float>(eY)
	};
}

void InfectionBlocks::SetAnchorPoint(const YMath::Vector2& anchor)
{
	// 0.0f ~ 1.0f �ɂȂ�悤��
	anchor_.x_ = Clamp<float>(anchor.x_, 0.0f, 1.0f);
	anchor_.y_ = Clamp<float>(anchor.y_, 0.0f, 1.0f);
}

void InfectionBlocks::ChangeUpdate()
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
			// �u�ԃt���O��true��
			isChangeMoment_ = true;
			// �J�ڒ��t���O��false��
			isPreChange_ = false;
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
		}
	}

}

void InfectionBlocks::BlockUpdate()
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
				BlockPropagate(x, y);
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
			float red = 0.0f;
			if (stepIndex_ == 0) { red = colorEas_[0].Out(blocks_[y][x]->colorStartTim_.Ratio()); }
			if (stepIndex_ == 1) { red = colorEas_[1].Out(blocks_[y][x]->colorEndTim_.Ratio()); }			
			
			// �A���t�@�l
			float alpha = 0.0f;
			if (stepIndex_ == 0) { alpha = alphaEas_[0].Out(blocks_[y][x]->colorStartTim_.Ratio()); }
			if (stepIndex_ == 1) { alpha = alphaEas_[1].Out(blocks_[y][x]->colorEndTim_.Ratio()); }

			// �F���
			blocks_[y][x]->color_->SetRGBA({red, 0.0f,0.0f,alpha});
		}
	}
}

void InfectionBlocks::BlockPropagate(const size_t x, const size_t y)
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

void InfectionBlocks::Update()
{
	ChangeUpdate();
	BlockUpdate();
}

void InfectionBlocks::Draw()
{
	for (size_t y = 0; y < blocks_.size(); y++)
	{
		for (size_t x = 0; x < blocks_[y].size(); x++)
		{
			spBlockSpr_->Draw(blocks_[y][x]->obj_.get());
		}
	}
}