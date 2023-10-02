#pragma once
#include "BaseTransition.h"
#include "DrawObjectForSprite2D.h"
#include "CBColor.h"
#include <array>

namespace YGame
{
	class WindBlocks : public BaseTransition
	{

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

	public:

		WindBlocks() = default;

		~WindBlocks() = default;

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		static void StaticInitialize();
	
	private:

		// �i�K
		enum class Step
		{
			Close,	 // ����
			Load,	 // ���[�h����
			Open,	 // �J��
		};

	private:

		// �u���b�N
		struct Block
		{
			std::unique_ptr<YGame::DrawObjectForSprite2D> obj_; // �I�u�W�F�N�g
			std::unique_ptr<YGame::ConstBufferObject<YGame::CBColor>> cbColor_; // �F�萔�o�b�t�@
			YMath::Timer actTim_; // ����^�C�}�[
			bool isActColorPow_ = false;
			YMath::Power colorPow_; // �F�^�C�}�[
		};

	private:

		// �u���b�N�z��
		std::vector<std::unique_ptr<Block>> blocks_;

		// �i�K
		Step step_ = Step::Close;

		// �C�[�W���O
		std::array<YMath::Ease<float>, 2> posXEas_;
		YMath::Ease<YMath::Vector4> colorEas_;

	private:

		/// <summary>
		/// �V�[���J�ڍX�V
		/// </summary>
		void UpdateChange();

		/// <summary>
		/// �`�d
		/// </summary>
		/// <param name="index"></param>
		void PropagateBlock(const size_t index, const bool isActColorPow);

		/// <summary>
		/// �u���b�N�X�V
		/// </summary>
		void UpdateBlock();

	private:

		// �X�v���C�g(2D)
		static YGame::Sprite2D* spBlockSpr_;
	};
}
