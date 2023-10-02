#pragma once
#include "BaseTransition.h"
#include "DrawObjectForSprite2D.h"
#include "ConstBufferObject.h"
#include "CBSprite2DTransform.h"
#include "CBColor.h"
#include "CBTexConfig.h"
#include "Sprite2D.h"

namespace YGame
{
	// �Ó]
	class Blackout : public BaseTransition
	{

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

	public:

		Blackout() = default;

		~Blackout() = default;

	public:

		// �ÓI������
		static void StaticInitialize();
	
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
		std::unique_ptr<YGame::DrawObjectForSprite2D> obj_;
		
		// �F�萔�o�b�t�@
		std::unique_ptr<YGame::ConstBufferObject<YGame::CBColor>> cbColor_;

		// �i�K
		Step step_ = Step::Dark;
		

		// ���ߓx�p���[
		YMath::Power blendPow_;

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
	};
}
