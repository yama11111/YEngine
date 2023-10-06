#pragma once
#include "DrawObjectForSprite2D.h"
#include "CBColor.h"
#include "Ease.h"
#include "Power.h"
#include <array>

namespace YGame
{
	class PauseDrawer
	{

	public:

		// �I��
		enum class Selection : size_t
		{
			Resume, // �߂�
			ReStart, // ���X�^�[�g
			Change, // �J��
			End,
		};

		// �I�����̐�
		static const size_t kSelectionNum = static_cast<size_t>(Selection::End);

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

	public:

		/// <summary>
		/// �N���A�j���[�V����
		/// </summary>
		void BootAnimation();
		
		/// <summary>
		/// ��~�A�j���[�V����
		/// </summary>
		void ShutdownAnimation();

		/// <summary>
		/// �I�����ݒ�
		/// </summary>
		/// <param name="select"> : �I��</param>
		void SetSelection(const Selection select);

	public:

		/// <summary>
		/// ���\�[�X�ǂݍ���
		/// </summary>
		static void LoadResource();

	private:
		
		// �I�����\����
		struct SelectionObject
		{
			// �I�u�W�F�N�g
			std::unique_ptr<DrawObjectForSprite2D> obj_;
			std::unique_ptr<ConstBufferObject<CBColor>> color_;

			// ���o�p
			bool isActPos_ = false;
			YMath::Power posXPow_;
			YMath::Ease<float> posXEas_;
			YMath::Power scalePow_;
		};
	
	private:

		// �I��
		Selection selection_ = Selection::Resume;

		// �A�j���[�V����
		bool isAct_ = false;
		YMath::Power animePow_;

		// �|�[�Y���S
		std::unique_ptr<DrawObjectForSprite2D> pauseLogo_;
		YMath::Ease<float> pauseLogoPosXEas_;
		
		// �I����
		std::array<SelectionObject, kSelectionNum> selectionObjs_;
		YMath::Ease<YMath::Vector3> selectScaleEas_;
		
		// ���E��
		std::unique_ptr<DrawObjectForSprite2D> border_;
		YMath::Ease<float> borderScaleYEas_;

		// �w�i�J�[�e��
		std::unique_ptr<DrawObjectForSprite2D> curten_;
		std::unique_ptr<ConstBufferObject<CBColor>> curtenColor_;
		YMath::Power curtenAlphaPow_;
		YMath::Ease<float> curtenAlphaEas_;

	private:

		// �|�[�Y���S�X�v���C�g
		static Sprite2D* spPauseLogo_;

		// �I�������S�X�v���C�g
		static std::array<Sprite2D*, kSelectionNum> spSelectionSprites_;
		
		// ���E���X�v���C�g
		static Sprite2D* spBorder_;
		
		// �J�[�e���X�v���C�g
		static Sprite2D* spCurten_;

	private:

		/// <summary>
		/// �`�d
		/// </summary>
		void PropagateSelection(const size_t index);
	};
}

