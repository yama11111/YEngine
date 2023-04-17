#pragma once
#include "ITransitionFactory.h"

namespace YScene
{
	class YGameTransitionFactory : public ITransitionFactory
	{
	private:
		// �Ó]
		const std::string Blackout_ = "BLACKOUT";
		// ���ߐs�����u���b�N
		const std::string InfectionBlocks_ = "INFECTION";
	public:
		// �V�[���J��
		void ActivateTransition(const std::string& transitionName) override;
		// �V�[���J�ڂ̏u��
		bool IsChangeMoment() override;
	};
}
