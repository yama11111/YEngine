#include "SelectDrawer.h"
#include "MathUtil.h"
#include "MathVector.h"
#include "Def.h"
#include "Keys.h"
#include "Pad.h"
#include <cassert>

using YGame::SelectDrawer;
using YMath::Vector3;

YGame::Sprite2D* SelectDrawer::spLogoSpr_ = nullptr;
YGame::Sprite2D* SelectDrawer::spStickSpr_ = nullptr;
YGame::Sprite2D* SelectDrawer::spButtonSpr_ = nullptr;

void SelectDrawer::StaticInitialize()
{
	spLogoSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("select/stage_logo.png")} });

	spStickSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("UI/key/stick_L.png")} });

	spButtonSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("UI/key/button_A.png")} });
}

void SelectDrawer::Initialize()
{
	core_ = Transform::Status::Default();

	// �n��
	earthTra_.Initialize();
	earthTra_.parent_ = &core_.m_;
	earthDra_.reset(EarthDrawer::Create(&earthTra_, 1));

	// �X�e�[�W�g�����X�t�H�[�� (�g���p)
	for (size_t i = 0; i < aliveStages_.size(); i++)
	{
		aliveStages_[i].Initialize();
		aliveStages_[i].parent_ = &core_.m_;
	}

	// �X�e�[�W�g�����X�t�H�[�� (�g��Ȃ��p)
	deadStage_.Initialize();

	size_t stageNum = 10;

	// �X�e�[�W�`��N���X
	stageDras_.resize(stageNum); // ���T�C�Y
	for (size_t i = 0; i < stageDras_.size(); i++)
	{
		stageDras_[i].reset(StageDrawer::Create(nullptr, 0));

		// �ԍ����g�����X�t�H�[���̐���菬�����Ȃ�
		if (i < aliveStages_.size())
		{
			// �g���p�̃g�����X�t�H�[������
			stageDras_[i]->Initialize(&aliveStages_[i], 1);
		}
		// ����ȊO�Ȃ�
		else
		{
			// �g��Ȃ��p�̃g�����X�t�H�[������
			stageDras_[i]->Initialize(&deadStage_, 1);
		}
	}


	// �X�e�[�W�J�[�h
	cards_.resize(stageNum);
	for (size_t i = 0; i < cards_.size(); i++)
	{
		cards_[i].Initialize();
	}

	// �X�e�[�W�J�[�h�`��N���X
	cardDras_.resize(stageNum);
	for (size_t i = 0; i < cardDras_.size(); i++)
	{
		cardDras_[i].reset(new CardDrawer());
		cardDras_[i]->Initialize(&cards_[i], static_cast<int>(i + 1));
	}

	letterBox_.reset(new UILetterBox());
	letterBox_->Initialize(WinSize, 96.0f, 96.0f);

	// �E�B���h�E�T�C�Y �� 3�����x�N�g���ɂ��Ă���
	Vector3 win = YMath::ConvertToVector3(WinSize);

	// ���S������
	Vector3 logoPos = (win / 2.0f) - Vector3(288.0f, 288.0f, 0.0f);
	logoObj_.reset(DrawObjectForSprite2D::Create({ logoPos, {}, {1.0f,1.0f,1.0f} }, spLogoSpr_));

	Vector3 stickPos = (win / 2.0f) + Vector3(-448.0f, 288.0f, 0.0f);
	stickObj_.reset(DrawObjectForSprite2D::Create({ stickPos, {}, {1.0f,1.0f,1.0f} }, spStickSpr_));

	Vector3 buttonPos = (win / 2.0f) + Vector3(-288.0f, 308.0f, 0.0f);
	DrawObjectForSprite2D* newStartButton = DrawObjectForSprite2D::Create({ buttonPos, {}, {1.0f,1.0f,0.0f} }, spButtonSpr_);
	startButton_.reset(UIButton::Create(newStartButton));


	// �V��
	skydomeTra_.Initialize();
	skydomeTra_.scale_ = { 32.0f,32.0f,32.0f };
	skydomeTra_.parent_ = &core_.m_;
	skydome_.reset(SkydomeDrawer::Create(&skydomeTra_, 3));

	// ----- �C�[�W���O ----- //

	// �X�e�[�W��]�p�p���[
	int32_t staNum = static_cast<int32_t>(stageNum) - 1;
	stageRotaPows_.resize(static_cast<size_t>(staNum)); // ���T�C�Y
	
	// ���Z�b�g
	Reset();
}

void SelectDrawer::Reset()
{
	// ----- �I�u�W�F�N�g������ ----- //

	// �j
	core_.Initialize();

	// �傫���̗�
	float earthScaleVal = 32.0f;
	// ��]�̗�
	float rotaVal = (PI * 2.0f) / static_cast<float>(aliveStages_.size());

	// �n��
	earthTra_.Initialize({ {},{},{earthScaleVal,earthScaleVal,earthScaleVal} });

	// ----- �X�e�[�W ----- //

	// �g�����X�t�H�[�� (�g���p)
	for (size_t i = 0; i < aliveStages_.size(); i++)
	{
		// �ʒu
		float pos = earthScaleVal - 0.5f;

		// ��] ((360 / size) * idx)
		float rota = rotaVal * i;

		// ��]�ʂɍ��킹���ʒu�ɂȂ�悤��
		aliveStages_[i].Initialize(
			{
				{ 0.0f, +pos * cosf(rota), +pos * sinf(rota) }, // �ʒu
				{ rota, 0, 0 }, // ��]
				{ 1.0f, 1.0f, 1.0f } // �傫��
			}
		);
	}
	// �g�����X�t�H�[�� (�g��Ȃ��p)
	deadStage_.Initialize({ {-2000,-2000,-2000}, {}, {} });

	// �`��N���X
	//for (size_t i = 0; i < stageDras_.size(); i++)
	//{
	//	// ���
	//	TowerDrawerCommon::Type type = TowerDrawerCommon::Type::eBlack;

	//	// �N���A���Ă���Ȃ�ύX
	//	if (spStageConfig_->GetIsClearStage((int)i))
	//	{
	//		// �N���A���Ă���Ȃ�ύX
	//		type = TowerDrawerCommon::Type::eWhite;
	//	}

	//	stageDras_[i]->Reset(type);
	//}

	// ----- �X�e�[�W�J�[�h ----- //

	// �����̕�
	float heightVal = 448.0f / static_cast<float>(10 - 1);

	// �g�����X�t�H�[�� (�e)
	for (size_t i = 0; i < cards_.size(); i++)
	{
		// y �̈ʒu
		float y = WinSize.y_ / 2.0f + 8.0f + (448 / 2.0f)
			- heightVal * static_cast<float>(i);

		cards_[i].Initialize(
			{
				{WinSize.x_ - 96.0f, y, 0.0f },
				{},
				{ 1.0f, 1.0f, 1.0f }
			}
		);
	}
	// �`��N���X
	//for (size_t i = 0; i < cardDras_.size(); i++)
	//{
	//	// �N���A���Ă���Ȃ�ύX
	//	cardDras_[i]->Reset(spStageConfig_->GetIsClearStage((int)i));
	//}

	// �V��

	// ----- ���̑������� ----- //

	// ���쒆��
	isAct_ = false;

	// �J�n����]�p�C�[�W���O
	startRotaEas_.Initialize(0.0f, -rotaVal / 2.0f, 1.4f);

	// �J�n����]�p�^�C�}�[
	startRotaTim_.Initialize(20);
	startRotaTim_.SetActive(true);


	// �X�e�[�W��]�p�C�[�W���O
	stageRotaEas_.Initialize(0.0f, -rotaVal, 1.4f);

	// �X�e�[�W��]�p�p���[
	for (size_t i = 0; i < stageRotaPows_.size(); i++)
	{
		stageRotaPows_[i].Initialize(30);
	}
}

void SelectDrawer::UpdateRotaAnimation()
{
	// ��]��
	float rotaVal = 0.0f;

	// �J�n����]�^�C�}�[�X�V
	startRotaTim_.Update();
	// �J�n����]����
	rotaVal += startRotaEas_.In(startRotaTim_.Ratio());

	// �X�e�[�W������]������
	// ��]�����̕��X�^�[�g
	for (size_t i = 0; i < stageRotaPows_.size(); i++)
	{
		//��]�����邩
		bool isRotaAct = false;

		// ���݂̃X�e�[�W�����ԍ����������Ȃ�
		if (i < static_cast<size_t>(stageIndex_))
		{
			// ���삷��
			isRotaAct = true;
		}

		// �X�V
		stageRotaPows_[i].Update(isRotaAct);

		// ��]������Ȃ�C�[�Y�C��
		if (isRotaAct) { rotaVal += stageRotaEas_.In(stageRotaPows_[i].Ratio()); }
		// ����ȊO�Ȃ�C�[�Y�A�E�g
		else { rotaVal += stageRotaEas_.Out(stageRotaPows_[i].Ratio()); }

		//rotaVal += stageRotaEas_.In(stageRotaPows_[i].Ratio());
	}

	// �j�ɑ�� (��])
	core_.rota_.x_ = rotaVal;
}

void SelectDrawer::Update()
{
	// ���쒆����Ȃ��Ȃ�e��
	//if (isAct_ == false) { return; }

	// �A�j���[�V�����̉�]�X�V
	UpdateRotaAnimation();

	// �j
	core_.UpdateMatrix();

	// �n��
	earthDra_->Update();

	// ----- �X�e�[�W ----- //

	// �g�����X�t�H�[��
	for (size_t i = 0; i < aliveStages_.size(); i++)
	{
		aliveStages_[i].UpdateMatrix();
	}
	// �`��N���X
	for (size_t i = 0; i < stageDras_.size(); i++)
	{
		stageDras_[i]->Update();
	}

	// ----- �X�e�[�W�J�[�h ----- //

	// �g�����X�t�H�[��
	for (size_t i = 0; i < cards_.size(); i++)
	{
		cards_[i].UpdateMatrix();
	}
	// �`��N���X
	for (size_t i = 0; i < cardDras_.size(); i++)
	{
		cardDras_[i]->Update();

		// �I�𒆂�
		bool isSelect = false;

		// �I�𒆂̃X�e�[�W�ԍ��̂Ƃ�
		int staIdx = stageIndex_;
		if (i == staIdx)
		{
			// �I��
			isSelect = true;
		}

		// �I�𒆂��ݒ�
		cardDras_[i]->SetSelect(isSelect);
	}

	skydome_->Update();

	letterBox_->Update();
	logoObj_->Update();
	stickObj_->Update();
	startButton_->Update(
		YInput::Keys::GetInstance()->IsTrigger(DIK_SPACE) ||
		YInput::Pad::GetInstance()->IsTrigger(YInput::PadButton::XIP_A));

}

void SelectDrawer::Draw()
{
	// �V��
	skydome_->Draw();

	// �X�e�[�W�`��
	for (size_t i = 0; i < stageDras_.size(); i++)
	{
		stageDras_[i]->Draw();
	}

	// �n��
	earthDra_->Draw();

	// ���^�[�{�b�N�X�`��
	letterBox_->Draw("Sprite2DDefault", 40);

	// �J�[�h�`�� (��납��)
	for (int i = static_cast<int>(cardDras_.size()) - 1; i >= 0; i--)
	{
		cardDras_[i]->Draw(i * 2);
	}

	logoObj_->Draw("Sprite2DDefault", 1);
	stickObj_->Draw("Sprite2DDefault", 1);
	startButton_->Draw("Sprite2DDefault", 1);
}
