#pragma once
#include "Transform.h"
#include <string>

namespace YGame
{
	struct DrawerInitSet
	{
		Transform* pParent = nullptr;

		YMath::Vector3* pParentWorldPos = nullptr;

		std::string vpKey;

		size_t drawPriority;
	};
}