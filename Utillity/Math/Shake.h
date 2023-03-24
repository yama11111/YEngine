#pragma once
#include "Vector3.h"

namespace YMath
{
	// —h‚ê
	class Shake
	{
	private:
		// —h‚ê‚Ä‚¢‚é—Ê
		Vector3 value_{};
		// —h‚ê‚Ä‚¢‚é‚©
		bool isAct_ = false;
		// —h‚ê‚é—Ê (—”)
		int swing_ = 0;
		// Œ¸Š—Ê
		int dekey_ = 0;
	public:
		// ‰Šú‰»
		void Initialize();
		// XV
		void Update();
		/// <summary>
		/// “®ìŠJn
		/// </summary>
		/// <param name="swing"> : —h‚ê‚é—Ê</param>
		/// <param name="dekey"> : Œ¸Š—Ê</param>
		void Activate(const int swing, const int dekey);
	public:
		// —h‚ê—Ê
		Vector3 Value() const { return value_; }
		// “®ì’†‚©
		bool IsAct() const { return isAct_; }
	};
}