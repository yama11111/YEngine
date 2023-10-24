#pragma once
#include <cstdint>
#include "Vector3.h"

namespace YGame
{
	static const YMath::Vector3 kMaxWorldSize = { 2000.0f, 150.0f, 150.0f };

	namespace PlayerConfig
	{
		static const float kRadius = 1.0f;
		static const YMath::Vector3 kAcceleration = { 0.1f,1.25f,0.0f };
		static const YMath::Vector3 kMaxSpeed = { 0.3f,2.0f,0.0f };
		static const uint16_t kMaxJumpCount = 2;
		static const uint32_t kHP = 3;
		static const uint32_t kAttack = 100;
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
		static const uint32_t kAttack = 100;
		static const uint32_t kInvincibleTime = 10;

		static const YMath::Vector3 kRiddenHeight = { 0.0f,1.25f,-0.5f };
	}

	namespace SlimeConfig
	{
		static const float kRadius = 1.0f;
		static const YMath::Vector3 kAcceleration = { 0.5f,0.5f,0.0f };
		static const YMath::Vector3 kMaxSpeed = { 0.5f,0.5f,0.0f };
		static const uint32_t kHP = 100;
		static const uint32_t kAttack = 1;
		static const uint32_t kInvincibleTime = 20;
		static const uint32_t kBlowTime = 2;
	}

	namespace NeedleAttackConfig
	{
		static const uint32_t kAliveTime = 30;
		static const YMath::Vector3 kAcceleration = { 0.3f,0.0f,0.0f };
		static const YMath::Vector3 kMaxSpeed = { 1.0f,0.0f,0.0f };
		static const float kRadius = 2.0f;
		static const uint32_t kPower = 50;
	}

	namespace SlashAttackConfig
	{
		static const uint32_t kAliveTime = 5;
		static const YMath::Vector3 kOffset = { +3.0f,+1.0f,0.0f };
		static const float kRadius = 3.0f;
		static const uint32_t kPower = 20;
	}

	namespace SnortAttackConfig
	{
		static const uint32_t kAliveTime = 20;
		static const YMath::Vector3 kAcceleration = { 0.3f,0.0f,0.0f };
		static const YMath::Vector3 kMaxSpeed = { 0.6f,0.0f,0.0f };
		static const float kRadius = 2.0f;
		static const uint32_t kPower = 20;
	}

	namespace CoinConfig
	{
		static const float kRadius = 2.0f;
	}
}