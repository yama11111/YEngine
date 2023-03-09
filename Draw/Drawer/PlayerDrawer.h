#pragma once
#include "Model.h"
#include <array>
#include <memory>

namespace YGame
{
	class PlayerDrawerCommon
	{
	protected:
		enum class Parts 
		{
			Body,
			Face,
			Tail,
		};
	protected:
		static const size_t PartsNum_ = 3;
		static std::array<std::unique_ptr<YGame::Model>, PartsNum_> pModels_;
	public:
		struct StaticInitStatus
		{
		};
	public:
		static void StaticInitialize(const StaticInitStatus& state);
	};

	class PlayerDrawer :
		private PlayerDrawerCommon
	{
	private:
		std::array<std::unique_ptr<YGame::ObjectModel>, PartsNum_> objs_;
	public:
		// ‰Šú‰» (Å‰‚Éˆê‰ñ‚¾‚¯)
		void Initialize(YMath::Matrix4* pParent);
		// ‰Šú‰»
		void Reset();
		// XV
		void Update();
		// •`‰æ
		void Draw(const YGame::ViewProjection& vp, YGame::LightGroup* lightGroup);
	};
}

