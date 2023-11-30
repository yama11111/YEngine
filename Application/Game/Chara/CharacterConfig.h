#pragma once
#include <cstdint>
#include "Vector3.h"

namespace YGame
{
	static const YMath::Vector3 kMaxWorldSize = { 2000.0f, 150.0f, 150.0f };

	namespace PlayerConfig
	{
		static const YMath::Vector2 kRectSize = { 1.0f,1.0f };
		
		static const float kRadius = 1.0f;
		
		static const YMath::Vector3 kAcceleration = { 0.1f,1.5f,0.0f };
		static const YMath::Vector3 kMaxSpeed = { 0.4f,1.5f,0.0f };
		
		static const uint16_t kMaxJumpCount = 2;
		static const uint32_t kHP = 3;
		static const uint32_t kAttack = 100;
		static const uint32_t kInvincibleTime = 20;
	}

	namespace PetConfig
	{
		static const YMath::Vector2 kRectSize = { 1.0f,1.0f };
		
		static const float kRadius = 1.0f;
		
		static const YMath::Vector3 kNormalAcceleration = { 0.1f,1.5f,0.0f };
		static const YMath::Vector3 kNormalMaxSpeed = { 0.4f,1.5f,0.0f };
		
		static const uint16_t kMaxJumpCount = 2;
		static const uint32_t kHP = 1;
		static const uint32_t kAttack = 100;
		static const uint32_t kInvincibleTime = 10;

		static const YMath::Vector3 kRiddenHeight = { 0.0f,1.25f,-0.5f };
	}

	namespace SlimeConfig
	{
		static const YMath::Vector2 kRectSize = { 1.0f,1.0f };
		
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