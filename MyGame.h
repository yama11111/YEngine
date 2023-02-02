#pragma once
#include "YFramework.h"

namespace YBase
{
	class MyGame : public YFramework
	{
	public:
		// ‰Šú‰»
		bool Initialize() override;
		// I—¹ˆ—
		void Finalize() override;
		// XV
		void Update() override;
		// •`‰æ
		void Draw() override;
	};
}
