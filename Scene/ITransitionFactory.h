#pragma once
#include <string>

namespace YScene
{
	// ���ۃV�[���J�ڃt�@�N�g���[
	class ITransitionFactory
	{
	public:
		// �f�X�g���N�^
		virtual ~ITransitionFactory() = default;
		// �V�[���J��
		virtual void ActivateTransition(const std::string& transitionName) = 0;
		// �V�[���J�ڂ̏u��
		virtual bool IsChangeMoment() = 0;
	};
}