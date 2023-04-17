#include "YGameTransitionFactory.h"
#include "TransitionManager.h"

using YScene::YGameTransitionFactory;
using YGame::TransitionManager;
using YGame::TransitionType;

void YGameTransitionFactory::ActivateTransition(const std::string& transitionName)
{
	if (transitionName == Blackout_)
	{
		TransitionManager::GetInstance()->Activate(TransitionType::Blackout);
	}
	if (transitionName == InfectionBlocks_)
	{
		TransitionManager::GetInstance()->Activate(TransitionType::InfectionBlocks);
	}
}

bool YGameTransitionFactory::IsChangeMoment()
{
	return TransitionManager::GetInstance()->IsChangeMoment();
}
