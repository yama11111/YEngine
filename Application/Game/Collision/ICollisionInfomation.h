#pragma once
#include "AttributeType.h"
#include "Transform.h"
#include "Vector3.h"
#include "CharacterStatus.h"
#include <string>

namespace YGame
{
	struct ICollisionInfomation
	{
		// 属性
		AttributeType attribute = AttributeType::eNone;

		// トランスフォームポインタ
		Transform* pTrfm = nullptr;

		// 半径
		float radius = 0.0f;

		// ワールド座標
		YMath::Vector3* pWorldPos = nullptr;

		// 移動方向
		YMath::Vector3* pMoveDirection = nullptr;

		// キャラステータスポインタ
		CharacterStatus* pStatus = nullptr;

		// キー
		std::string oppositeKey;
	};
}
