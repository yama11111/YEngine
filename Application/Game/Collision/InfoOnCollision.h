#pragma once
#include "AttributeType.h"
#include "Transform.h"
#include "Vector3.h"
#include "CharacterStatus.h"

namespace YGame
{
	struct InfoOnCollision
	{
		// 属性
		AttributeType attribute = AttributeType::eNone;

		// トランスフォームポインタ
		Transform* pTrfm = nullptr;

		// 半径
		float radius = 0.0f;

		// 移動方向
		YMath::Vector3* pMoveDirection_ = nullptr;

		// キャラステータスポインタ
		CharacterStatus* pStatus = nullptr;
	};
}
