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
		// 初期化 (最初に一回だけ)
		void Initialize(YMath::Matrix4* pParent);
		// 初期化
		void Reset();
		// 更新
		void Update();
		// 描画
		void Draw(const YGame::ViewProjection& vp, YGame::LightGroup* lightGroup);
	};
}

