#pragma once
#include <cstdint>
#include "Vector3.h"

namespace YGame
{
	namespace PlayerConfig
	{
		static const YMath::Vector2 kPhysicsRect = { 1.0f,1.0f };
		static const YMath::Vector2 kCollRect = { 1.5f,1.5f };
		
		static const float kRadius = 1.0f;
		
		static const YMath::Vector3 kAcceleration = { 0.1f,0.3f,0.0f };
		static const YMath::Vector3 kMaxSpeed = { 0.4f,2.0f,0.0f };
		static const float kJumpSpeed = 1.5f;
		
		static const uint16_t kMaxJumpCount = 2;
		static const uint32_t kHP = 100;
		static const uint32_t kAttack = 100;
		static const uint32_t kInvincibleTime = 40;
	}

	namespace SlimeConfig
	{
		static const YMath::Vector2 kRectSize = { 1.0f,1.0f };
		
		static const float kRadius = 1.0f;
		
		static const YMath::Vector3 kAcceleration = { 0.5f,0.5f,0.0f };
		static const YMath::Vector3 kMaxSpeed = { 0.5f,0.5f,0.0f };
		
		static const uint32_t kHP = 100;
		static const uint32_t kAttack = 20;
		static const uint32_t kInvincibleTime = 20;
	}

	namespace NeedleAttackConfig
	{
		static const uint32_t kAliveTime = 30;
		static const YMath::Vector3 kAcceleration = { 0.3f,0.0f,0.0f };
		static const YMath::Vector3 kMaxSpeed = { 1.0f,0.0f,0.0f };
		static const float kRadius = 4.0f;
		static const uint32_t kPower = 50;
	}

	namespace CoinConfig
	{
		static const float kRadius = 2.5f;
		static const YMath::Vector3 kAcceleration = { 0.2f,0.2f,0.0f };
		static const YMath::Vector3 kMaxSpeed = { 0.6f,0.6f,0.0f };
	}

	namespace MagnetConfig
	{
		static const float kCollRadius = 2.5f;
		static const float kSuctionRadius = 12.0f;
	}
}