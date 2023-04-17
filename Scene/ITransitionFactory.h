#pragma once
#include <string>

namespace YScene
{
	// 抽象シーン遷移ファクトリー
	class ITransitionFactory
	{
	public:
		// デストラクタ
		virtual ~ITransitionFactory() = default;
		// シーン遷移
		virtual void ActivateTransition(const std::string& transitionName) = 0;
		// シーン遷移の瞬間
		virtual bool IsChangeMoment() = 0;
	};
}