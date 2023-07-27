#pragma once
#include "ITransitionFactory.h"

namespace YGame
{
	class YGameTransitionFactory : public ITransitionFactory
	{
	
	public:
		
		// ˆÃ“]
		static const std::string Blackout_;
		
		// –„‚ßs‚­‚·ƒuƒƒbƒN
		static const std::string InfectionBlocks_;
	
	public:
		
		/// <summary> 
		/// ƒV[ƒ“‘JˆÚ¶¬
		/// </summary>
		/// <param name="transitionName"> : ‘JˆÚ–¼</param>
		/// <returns>ƒV[ƒ“‘JˆÚ</returns>
		virtual BaseTransition* CreateTransition(const std::string& transitionName) override;
	};
}
