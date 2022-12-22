#include "BillboardCommon.h"
#include <cassert>

using YGame::BillboardCommon;
using YGame::TextureManager;

YDX::PipelineSet BillboardCommon::pplnSet_;
TextureManager* BillboardCommon::pTexManager_ = nullptr;

void BillboardCommon::StaticInitialize(const StaticInitStatus& state)
{
	assert(state.pTexManager_);
	pTexManager_ = state.pTexManager_;
	pplnSet_.Initialize(YDX::PipelineSet::Type::BillboardT, state.rootParams_);
}

void BillboardCommon::StaticSetDrawCommand()
{
	pplnSet_.SetDrawCommand();
}
