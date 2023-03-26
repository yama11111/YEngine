#pragma once
#include "ITransition.h"
#include "Sprite2D.h"

namespace YGame
{
	// �Ó]
	class Blackout : public ITransition
	{
	private:
		// �Ó]�i�K
		enum class Step
		{
			Dark,	 // ��
			Load,	 // ���[�h����
			Bright,	 // ��
		};
	private:
		// �I�u�W�F�N�g
		std::unique_ptr<Sprite2DObject> obj_;
		// �F
		std::unique_ptr<Color> color_;

		// �i�K
		Step step_ = Step::Dark;

		// ���ߓx�C�[�W���O
		YMath::Ease<float> blendEas_;
		// ���ߓx�p���[
		YMath::Power blendPow_;
	public:
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="changeFrame"> : �ω����鎞��</param>
		/// <param name="loadFrame"> : �ǂݍ��ގ���</param>
		void Initialize(const uint32_t changeFrame, const uint32_t loadFrame);
		// ���Z�b�g(���g����������)
		void Reset() override;
		// �X�V
		void Update() override;
		// �`��
		void Draw() override;
	public:
		// ����J�n
		void Activate() override;
		// �؂�ւ��̏u�Ԃ�
		bool IsChangeMoment() const { return isChangeMoment_; }
		// �I�����Ă��邩
		bool IsEnd() const { return isEnd_; }
	private:
		// �؂�ւ������X�V
		void UpdateChange();
		// ���ߏ����X�V
		void UpdateBlend();
	private:
		// �X�v���C�g(2D)
		static std::unique_ptr<Sprite2D> sCurtenSpr_;
	public:
		// �ÓI������
		static void StaticInitialize();
	public:
		Blackout() = default;
		~Blackout() = default;
	};
}
