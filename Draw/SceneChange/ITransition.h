#pragma once
#include "Lerp.h"
#include "Power.h"
#include "Timer.h"

namespace YGame
{
	// �g�����W�V�������N���X
	class ITransition
	{
	protected:
		// ���삵�Ă��邩
		bool isAct_ = false;
		// �؂�ւ���Ă���r����
		bool isPreChange_ = false;
		// �؂�ւ��̏u��
		bool isChangeMoment_ = false;
		// �I�����Ă��邩
		bool isEnd_ = false;
		// ���[�f�B���O�p�^�C�}�[
		YMath::Timer loadTim_;
	public:
		// ���Z�b�g(���g����������)
		virtual void Reset() = 0;
		// �X�V
		virtual void Update() = 0;
		// �`��
		virtual void Draw() = 0;
	public:
		// ����J�n
		virtual void Activate() = 0;
		// �؂�ւ���Ă���r����
		bool IsPreChange() const { return isPreChange_; }
		// �؂�ւ��̏u�Ԃ�
		bool IsChangeMoment() const { return isChangeMoment_; }
		// �I�����Ă��邩
		bool IsEnd() const { return isEnd_; }
	public:
		ITransition() = default;
		virtual ~ITransition() = default;
	};
}
