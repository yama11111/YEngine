#pragma once
#include "ITransitionFactory.h"

namespace YScene
{
	class YGameTransitionFactory : public ITransitionFactory
	{
	private:
		// 暗転
		const std::string Blackout_ = "BLACKOUT";
		// 埋め尽くすブロック
		const std::string InfectionBlocks_ = "INFECTION";
	public:
		// シーン遷移
		void ActivateTransition(const std::string& transitionName) override;
		// シーン遷移の瞬間
		bool IsChangeMoment() override;
	};
}
