#pragma once
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Model.h"
#include "Audio.h"
#include "Ease.h"
#include "Power.h"
#include "Timer.h"
#include <memory>

namespace YGame
{
	// �g�����W�V�������N���X
	class BaseTransition
	{
	
	public:
		
		/// <summary>
		/// ������
		/// </summary>
		virtual void Initialize() = 0;

		/// <summary>
		/// ���Z�b�g (���g����������)
		/// </summary>
		virtual void Reset();

		/// <summary>
		/// �I������
		/// </summary>
		virtual void Finalize() = 0;

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void Update() = 0;

		/// <summary>
		/// �`��
		/// </summary>
		virtual void Draw() = 0;
	
	public:
		
		/// <summary> 
		/// ����J�n
		/// </summary>
		/// <param name="changeFrame"> : �J�ڎ���</param>
		/// <param name="loadFrame"> : �ǂݍ��ގ���</param>
		virtual void Activate(const uint32_t changeFrame, const uint32_t loadFrame) = 0;

	public:

		/// <summary>
		/// ���쒆���擾
		/// </summary>
		/// <returns>���쒆��</returns>
		bool IsAct() const { return isAct_; }

		/// <summary>
		/// ���؂ꒆ��
		/// </summary>
		/// <returns></returns>
		bool IsFalling() const { return isFalling_; }
		
		/// <summary> 
		/// �؂�ւ��̏u�Ԃ��擾
		/// </summary>
		/// <returns>�؂�ւ��̏u�Ԃ�</returns>
		bool IsChangeMoment() const { return isChangeMoment_; }

		/// <summary>
		/// ���J������
		/// </summary>
		/// <returns>�؂�ւ���Ă���r����</returns>
		bool IsRising() const { return isRising_; }

		/// <summary>
		/// �I�����Ă��邩�擾
		/// </summary>
		/// <returns>�I�����Ă��邩</returns>
		bool IsEnd() const { return isEnd_; }
	
	public:

		BaseTransition() = default;
		
		virtual ~BaseTransition() = default;

	protected:

		// �i�K
		enum class Step
		{
			Close,	 // ����
			Load,	 // ���[�h����
			Open,	 // �J��
		};
	
	protected:

		// ���삵�Ă��邩
		bool isAct_ = false;

		// ���؂ꒆ��
		bool isFalling_ = false;

		// �؂�ւ��̏u��
		bool isChangeMoment_ = false;

		// ���J������
		bool isRising_ = false;

		// �I�����Ă��邩
		bool isEnd_ = false;

		// ���[�f�B���O�p�^�C�}�[
		YMath::Timer loadTim_;

		// �i�K
		Step step_ = Step::Close;

	};
}
