#pragma once
#include "BaseTransition.h"
#include "DrawObjectForSprite2D.h"
#include "CBColor.h"
#include <array>

namespace YGame
{
	class WaveTransition final : public BaseTransition
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

		WaveTransition() = delete;
		
		WaveTransition(const bool isReverce) : isReverce_(isReverce){}

		~WaveTransition() = default;

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		static void LoadResource();

	private:

		// �g
		struct Wave
		{
			std::unique_ptr<DrawObjectForSprite2D> obj_; // �I�u�W�F�N�g
			std::unique_ptr<ConstBufferObject<CBColor>> cbColor_; // �F�萔�o�b�t�@
			YMath::Timer actTim_; // ����^�C�}�[
		};

	private:

		// ���]�t���O
		bool isReverce_ = false;

		// �g
		std::array<std::unique_ptr<Wave>, 3> waves_;

		// �C�[�W���O
		std::array<YMath::Ease<float>, 2> scaleXEas_;

	private:

		/// <summary>
		/// �V�[���J�ڍX�V
		/// </summary>
		void UpdateChange();

		/// <summary>
		/// �u���b�N�X�V
		/// </summary>
		void UpdateBlock();

	private:

		// �X�v���C�g(2D)
		static YGame::Sprite2D* spBlockSpr_;
	};
}
