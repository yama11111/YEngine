#pragma once
#include "AttributeType.h"
#include "Vector3.h"
#include "CharacterStatus.h"
#include "BaseCharacter.h"

namespace YGame
{
	struct CollisionInfo
	{
		// 属性
		AttributeType attribute = AttributeType::eNone;

		// 位置
		YMath::Vector3 pos;

		// 半径
		float radius = 0.0f;

		// キャラステータスポインタ
		CharacterStatus* pStatus = nullptr;

		// 自身
		BaseCharacter* pSelf = nullptr;
	};
}
