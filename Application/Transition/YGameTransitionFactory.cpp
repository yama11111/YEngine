#include "YGameTransitionFactory.h"
#include "TransitionManager.h"

#include "Blackout.h"
#include "InfectionBlocks.h"

using YGame::YGameTransitionFactory;
using YGame::BaseTransition;

const std::string YGameTransitionFactory::Blackout_			 = "BLACKOUT";
const std::string YGameTransitionFactory::InfectionBlocks_	 = "INFECTION";

BaseTransition* YGame::YGameTransitionFactory::CreateTransition(const std::string& transitionName)
{
	// Ÿ‚Ìƒgƒ‰ƒ“ƒWƒVƒ‡ƒ“‚ğ¶¬
	BaseTransition* newTransition = nullptr;

	if (transitionName == Blackout_)		 { newTransition = new Blackout(); }
	if (transitionName == InfectionBlocks_)	 { newTransition = new InfectionBlocks(); }

	return newTransition;
}
