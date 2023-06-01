#pragma once
#include "BaseTransition.h"
#include <string>

namespace YScene
{
	// ���ۃV�[���J�ڃt�@�N�g���[
	class ITransitionFactory
	{
	
	public:
		
		// �V�[���J�ڐ���
		virtual BaseTransition* CreateTransition(const std::string& transitionName) = 0;
	
	public:
		
		// �f�X�g���N�^
		virtual ~ITransitionFactory() = default;
	};
}