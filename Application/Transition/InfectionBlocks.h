#pragma once
#include "BaseTransition.h"
#include "Sprite2D.h"
#include <array>

namespace YScene
{
	// ��ʂ𖄂ߐs�����u���b�N
	class InfectionBlocks : public BaseTransition
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
			std::unique_ptr<YGame::Sprite2D::Object> obj_; // �I�u�W�F�N�g
			YMath::Timer actTim_; // ����^�C�}�[
			std::unique_ptr<YGame::CBColor> color_; // �F
			YMath::Timer colorStartTim_; // �F�^�C�}�[ (�n)
			YMath::Timer colorEndTim_; // �F�^�C�}�[ (�I)
			// �^�C�}�[����
			void SetTimerActive(const bool isAct)
			{
				actTim_.SetActive(isAct);
				colorStartTim_.SetActive(isAct);
				colorEndTim_.SetActive(isAct);
			};
		};

	private:

		// �u���b�N�z��
		std::vector<std::vector<std::unique_ptr<Block>>> blocks_;

		// �i�K
		Step step_ = Step::Narrow;

		// �C�[�W���O
		std::array<YMath::Ease<float>, 2> scaleEas_;
		std::array<YMath::Ease<float>, 2> rotaEas_;
		std::array<YMath::Ease<float>, 2> colorEas_;
		std::array<YMath::Ease<float>, 2> alphaEas_;

		// ���i�K�̃C���f�b�N�X
		size_t stepIndex_ = 0;


		// �J�n�ʒu (�v�f�ԍ�)
		YMath::Vector2 start_;

		// �I���ʒu (�v�f�ԍ�)
		YMath::Vector2 end_;

	public:

		/// <summary>
		/// ������
		/// </summary>
		virtual void Initialize() override;

		/// <summary>
		/// ���Z�b�g (���g����������)
		/// </summary>
		virtual void Reset() override;

		/// <summary>
		/// �I������
		/// </summary>
		virtual void Finalize() override;

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void Update() override;

		/// <summary>
		/// �`��
		/// </summary>
		virtual void Draw() override;

	public:

		/// <summary> 
		/// ����J�n
		/// </summary>
		/// <param name="loadFrame"> : �ǂݍ��ގ���</param>
		/// <param name="leftTop"> : 1�ԍ���̃u���b�N�̈ʒu</param>
		virtual void Activate(const uint32_t changeFrame, const uint32_t loadFrame) override;

	private:

		
		/// <summary>
		/// �V�[���J�ڍX�V
		/// </summary>
		void UpdateChange();
		
		/// <summary>
		/// �`�d
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		void PropagateBlock(const size_t x, const size_t y);
		
		/// <summary>
		/// �u���b�N�X�V
		/// </summary>
		void UpdateBlock();

	private:

		// �X�v���C�g(2D)
		static YGame::Sprite2D* spBlockSpr_;

		// ����
		static YMath::Vector2 sLeftTop_;

		// ��
		static YMath::Vector2 sNum_;

		// �A���J�[�|�C���g
		static YMath::Vector2 sAnchor_;

		// �傫��
		static float sSize_;

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		/// <param name="pBlockTex"> : �u���b�N�̉摜</param>
		static void StaticInitialize(YGame::Texture* pBlockTex);

	public:

		InfectionBlocks() = default;

		~InfectionBlocks() = default;
	};

}
