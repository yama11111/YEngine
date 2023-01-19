#pragma once
#include "SlimeActor.h"
#include "Sprite.h"
#include <array>

namespace YUIDrawer
{
	class PushUIDrawer :
		private YActor::SlimeActor
	{
	private:
		YGame::Object obj_;
		YMath::Vec3 endPos_;
		std::array<YGame::Sprite*, 2> pButtons_;
		bool isPush_ = false;
	public:
		void Initialize(const YMath::Vec3& startPos, const YMath::Vec3& endPos);
		void Reset();
		void Update();
		void Draw();
	public:
		void Push();
		void PushSlime();
	public:
		void SetSprites(YGame::Sprite* on, YGame::Sprite* off);
	};
}

