#pragma once
#include "YFramework.h"

namespace YBase
{
	class MyGame : public YFramework
	{
	public:

		/// <summary>
		/// ‰Šú‰»
		/// </summary>
		/// <returns>¬Œ÷‚µ‚½‚©</returns>
		bool Initialize() override;
		
		/// <summary>
		/// I—¹ˆ—
		/// </summary>
		void Finalize() override;
		
		/// <summary>
		/// XV
		/// </summary>
		void Update() override;

		/// <summary>
		/// •`‰æ
		/// </summary>
		void Draw() override;
	};
}
