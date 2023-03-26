#pragma once
#include "ITransition.h"
#include "Sprite2D.h"
#include <array>

namespace YGame
{
	// ��ʂ𖄂ߐs�����u���b�N
	class InfectionBlocks : public ITransition
	{
	private:
		// �i�K
		enum class Step
		{
			Narrow,	 // ���܂�
			Load,	 // ���[�h����
			Spread,	 // �L����
		};
	private:
		// �u���b�N
		struct Block
		{
			std::unique_ptr<Sprite2DObject> obj_; // �I�u�W�F�N�g
			YMath::Timer actTim_; // ����^�C�}�[
		};
	private:
		// �u���b�N�z��
		std::vector<std::vector<std::unique_ptr<Block>>> blocks_;

		// �i�K
		Step step_ = Step::Narrow;

		// �C�[�W���O
		std::array<YMath::Ease<float>, 2> scaleEas_;
		std::array<YMath::Ease<float>, 2> rotaEas_;
		// ���i�K�̃C���f�b�N�X
		size_t stepIndex_ = 0;

		// �A���J�[�|�C���g
		YMath::Vector2 anchor_;
		// �J�n�ʒu (�v�f�ԍ�)
		YMath::Vector2 start_;
		// �I���ʒu (�v�f�ԍ�)
		YMath::Vector2 end_;
	public:
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="changeFrame"> : �u���b�N�P���ω����鎞��</param>
		/// <param name="loadFrame"> : �ǂݍ��ގ���</param>
		/// <param name="leftTop"> : 1�ԍ���̃u���b�N�̈ʒu</param>
		/// <param name="size"> : �u���b�N1�̑傫��</param>
		/// <param name="num"> : �v�f�� (�����_�؂�̂�)</param>
		/// <param name="anchor"> : �J�n�_�̃A���J�[�|�C���g (�����l�͒��S)</param>
		void Initialize(
			const uint32_t changeFrame, const uint32_t loadFrame, 
			const YMath::Vector2& leftTop, const float size, const YMath::Vector2& num,
			const YMath::Vector2& anchor = { 0.5f,0.5f });
		// ���Z�b�g(���g����������)
		void Reset() override;
		// �X�V
		void Update() override;
		// �`��
		void Draw() override;
	public:
		// ����J�n
		void Activate() override;
		// �A���J�[�|�C���g�ݒ�
		void SetAnchorPoint(const YMath::Vector2& anchor);
	private:
		// �V�[���J�ڍX�V
		void ChangeUpdate();
		// �u���b�N�X�V
		void BlockUpdate();
		// �`�d
		void BlockPropagate(const size_t x, const size_t y);
	private:
		// �X�v���C�g(2D)
		static std::unique_ptr<Sprite2D> sBlockSpr_;
	public:
		// �ÓI������
		static void StaticInitialize();
	public:
		InfectionBlocks() = default;
		~InfectionBlocks() = default;
	};

}
