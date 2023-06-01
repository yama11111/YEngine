#pragma once
#include "ITransitionFactory.h"

namespace YScene
{
	class YGameTransitionFactory : public ITransitionFactory
	{
	
	public:
		
		// �Ó]
		static const std::string Blackout_;
		
		// ���ߐs�����u���b�N
		static const std::string InfectionBlocks_;
	
	public:
		
		/// <summary> 
		/// �V�[���J�ڐ���
		/// </summary>
		/// <param name="transitionName"> : �J�ږ�</param>
		/// <returns>�V�[���J��</returns>
		virtual BaseTransition* CreateTransition(const std::string& transitionName) override;
	};
}
