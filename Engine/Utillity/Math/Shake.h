#pragma once
#include "Vector3.h"

namespace YMath
{
	// —h‚ê
	class Shake
	{
	
	private:
		
		// —h‚ê‚Ä‚¢‚é‚©
		bool isAct_ = false;

		// —h‚ê‚é—Ê (—”)
		float swing_ = 0.0f;
		
		// Œ¸Š—Ê
		float dekey_ = 0.0f;

		// ˆÊ
		float place_ = 0.0f;

		// —h‚ê‚Ä‚¢‚é—Ê
		Vector3 value_{};
	
	public:

		/// <summary>
		/// ‰Šú‰»
		/// </summary>
		void Initialize();

		/// <summary>
		/// XV
		/// </summary>
		void Update();
		
		/// <summary>
		/// “®ìŠJn
		/// </summary>
		/// <param name="swing"> : —h‚ê‚é—Ê</param>
		/// <param name="dekey"> : Œ¸Š—Ê</param>
		/// <param name="place"> : ¬”“_ˆÈ‰º‚ÌˆÊ</param>
		void Activate(const float swing, const float dekey, const float place);
	
	public:

		/// <summary>
		/// —h‚ê—Êæ“¾
		/// </summary>
		/// <returns> : —h‚ê—Ê</returns>
		Vector3 Value() const { return value_; }

		/// <summary>
		/// “®ì’†‚©æ“¾
		/// </summary>
		/// <returns> : “®ì’†‚©</returns>
		bool IsAct() const { return isAct_; }
	
	};
}