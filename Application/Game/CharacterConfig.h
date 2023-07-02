#pragma once
#include <cstdint>
#include "Vector3.h"

namespace YGame
{
	namespace PlayerConfig
	{
		static const float kRadius = 1.0f;
		static const YMath::Vector3 kAcceleration = { 0.1f,1.25f,0.0f };
		static const YMath::Vector3 kMaxSpeed = { 0.3f,2.0f,0.0f };
		static const uint16_t kMaxJumpCount = 2;
		static const uint32_t kHP = 3;
		static const uint32_t kAttack = 20;
		static const uint32_t kInvincibleTime = 20;
	}

	namespace PetConfig
	{
		static const float kRadius = 1.0f;
		
		static const YMath::Vector3 kNormalAcceleration = { 0.1f,1.25f,0.0f };
		static const YMath::Vector3 kNormalMaxSpeed = { 0.3f,2.0f,0.0f };
		
		static const YMath::Vector3 kRunAcceleration = { 0.3f,1.25f,0.0f };
		static const YMath::Vector3 kRunMaxSpeed = { 0.6f,2.0f,0.0f };
		
		static const uint16_t kMaxJumpCount = 2;
		static const uint32_t kHP = 1;
		static const uint32_t kAttack = 20;
		static const uint32_t kInvincibleTime = 10;

		static const float kRiddenHeight = 1.0;
	}

	namespace SlimeConfig
	{
		static const float kRadius = 1.0f;
		static const YMath::Vector3 kAcceleration = { 0.1f,3.0f,0.0f };
		static const YMath::Vector3 kMaxSpeed = { 0.3f,3.0f,0.0f };
		static const uint32_t kHP = 1;
		static const uint32_t kAttack = 1;
		static const uint32_t kInvincibleTime = 10;
	}

	namespace SlashAttackConfig
	{
		static const uint32_t kAliveTime = 3;
		static const uint32_t kPower = 20;
	}

	namespace SnortAttackConfig
	{
		static const uint32_t kAliveTime = 3;
		static const uint32_t kPower = 20;
	}
}