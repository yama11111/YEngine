#pragma once
#include "Sprite.h"

namespace YUIDrawer
{
	class CountUIDrawer
	{
	private:
		YGame::Object obj_;
		YMath::Vec4 endColor_;
		YGame::Sprite* pCounter_ = nullptr;
	public:
		void Initialize(const YMath::Vec3& startPos, const YMath::Vec4& endColor);
		void Reset();
		void Update();
		void Draw();
	public:
		void Push();
		void PushSlime();
	public:
		void SetSprites(YGame::Sprite* pCounter);
	};
}
