#pragma once
#include "BaseTransition.h"
#include "Object.h"
#include "ConstBuffer.h"
#include "CBSprite2DTransform.h"
#include "CBColor.h"
#include "CBTexConfig.h"
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
		
		// �g�����X�t�H�[��
		std::unique_ptr<YGame::Transform> transform_;
		
		// �I�u�W�F�N�g
		std::unique_ptr<YGame::Object> obj_;
		
		// �g�����X�t�H�[���萔�o�b�t�@
		std::unique_ptr<YGame::ConstBuffer<YGame::CBSprite2DTransform::CBData>> cbTransform_;
		
		// �F�萔�o�b�t�@
		std::unique_ptr<YGame::ConstBuffer<YGame::CBColor::CBData>> cbColor_;
		
		// �e�N�X�`���ݒ�萔�o�b�t�@
		std::unique_ptr<YGame::ConstBuffer<YGame::CBTexConfig::CBData>> cbTexConfig_;

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
