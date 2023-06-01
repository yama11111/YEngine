#pragma once
#include "BaseTransition.h"
#include "Sprite2D.h"

namespace YScene
{
	// �Ó]
	class Blackout : public BaseTransition
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
		std::unique_ptr<YGame::Sprite2D::Object> obj_;
		
		// �F
		std::unique_ptr<YGame::CBColor> color_;

		// �i�K
		Step step_ = Step::Dark;
		

		// ���ߓx�p���[
		YMath::Power blendPow_;
	
	public:

		/// <summary>
		/// ������
		/// </summary>
		virtual void Initialize() override;

		/// <summary>
		/// �I������
		/// </summary>
		virtual void Finalize() override;

		/// <summary>
		/// ���Z�b�g (���g����������)
		/// </summary>
		virtual void Reset() override;

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
		
		// �؂�ւ������X�V
		void UpdateChange();
		
		// ���ߏ����X�V
		void UpdateBlend();
	
	private:
		
		// �X�v���C�g(2D)
		static YGame::Sprite2D* spCurtenSpr_;

		// ���ߓx�C�[�W���O
		static YMath::Ease<float> sBlendEas_;
	
	public:
		
		// �ÓI������
		static void StaticInitialize();
	
	public:
		
		Blackout() = default;
		
		~Blackout() = default;
	};
}
