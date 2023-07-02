#pragma once
#include "Shake.h"
#include "Vector4.h"
#include <cstdint>

namespace YGame
{
	class HitActor
	{
	
	public:

		void Initialize(const YMath::Vector4& hitColor = YMath::Vector4(1.0f, 0.0f, 0.0f, 0.75f));

		void Update();

		void Hit(const float swing, const float dekey, const float place);

		inline YMath::Vector4 HitColor() const { return hitColor_; }

		inline bool IsAct() const { return isAct_; }

	public:

		HitActor() = default;
		
		virtual ~HitActor() = default;
	
	private:

		// �����Ă��邩�t���O
		bool isAct_ = false;
		
		// �h��
		YMath::Shake shake_;
		
		// �q�b�g���̐F
		YMath::Vector4 hitColor_;
	};
}
