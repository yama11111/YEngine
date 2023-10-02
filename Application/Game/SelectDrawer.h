#pragma once
#include "EarthDrawer.h"
#include "StageDrawer.h"
#include "CardDrawer.h"
#include "SkydomeDrawer.h"

#include "UILetterBox.h"
#include "UIButton.h"

#include "Power.h"

namespace YGame
{
	class SelectDrawer
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		void Initialize();

		/// <summary>
		/// ���Z�b�g
		/// </summary>
		void Reset();

		/// <summary>
		/// �X�V
		/// </summary>
		void Update();

		/// <summary>
		/// �`��
		/// </summary>
		void Draw();

		void SetStageIndex(const int32_t index) { stageIndex_ = index; }

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		static void StaticInitialize();

	private:

		// �j
		Transform core_;


		// �n��
		Transform earthTra_;
		std::unique_ptr<EarthDrawer> earthDra_;

		// �X�e�[�W�g�����X�t�H�[�� (�g���p)
		std::array<Transform, 24> aliveStages_;

		// �X�e�[�W�g�����X�t�H�[�� (�g��Ȃ��p)
		Transform deadStage_;

		// �X�e�[�W�`��N���X
		std::vector<std::unique_ptr<StageDrawer>> stageDras_;


		// �X�e�[�W�J�[�h�p�g�����X�t�H�[�� (�e)
		std::vector<Transform> cards_;

		// �X�e�[�W�J�[�h�`��N���X
		std::vector<std::unique_ptr<CardDrawer>> cardDras_;


		// ����
		std::unique_ptr<UILetterBox> letterBox_;

		std::unique_ptr<DrawObjectForSprite2D> logoObj_;
		std::unique_ptr<DrawObjectForSprite2D> stickObj_;
		
		std::unique_ptr<UIButton> startButton_;

		// �V��
		Transform skydomeTra_;
		std::unique_ptr<SkydomeDrawer> skydome_;


		// ----- �A�j���[�V���� ----- //

		int32_t stageIndex_ = 0;

		// ���쒆��
		bool isAct_ = false;


		// �J�n����]�p�C�[�W���O
		YMath::Ease<float> startRotaEas_;

		// �J�n����]�p�^�C�}�[
		YMath::Timer startRotaTim_;


		// �X�e�[�W��]�p�C�[�W���O
		YMath::Ease<float> stageRotaEas_;

		// �X�e�[�W��]�p�p���[
		std::vector<YMath::Power> stageRotaPows_;
	
	private:

		static Sprite2D* spLogoSpr_;

		static Sprite2D* spStickSpr_;

		static Sprite2D* spButtonSpr_;

	private:

		// �A�j���[�V�����̉�]�X�V
		void UpdateRotaAnimation();

	};
}
