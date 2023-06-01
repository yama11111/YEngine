#pragma once
#include "BaseTransition.h"
#include <string>

namespace YScene
{
	// 抽象シーン遷移ファクトリー
	class ITransitionFactory
	{
	
	public:
		
		// シーン遷移生成
		virtual BaseTransition* CreateTransition(const std::string& transitionName) = 0;
	
	public:
		
		// デストラクタ
		virtual ~ITransitionFactory() = default;
	};
}