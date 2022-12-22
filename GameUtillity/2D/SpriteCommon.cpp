#include "SpriteCommon.h"
#include "CalcTransform.h"
#include <cassert>

using YGame::SpriteCommon;

YMath::Mat4 SpriteCommon::projection_ = YMath::Mat4::Identity();
YDX::PipelineSet SpriteCommon::pplnSet_;
YGame::TextureManager* SpriteCommon::pTexManager_ = nullptr;

void SpriteCommon::StaticInitialize(const StaticInitStatus& state)
{
	assert(state.pTexManager_);
	pTexManager_ = state.pTexManager_;
	projection_ = YMath::MatOrthoGraphic();
	pplnSet_.Initialize(YDX::PipelineSet::Type::SpriteT, state.rootParams_);
}

void SpriteCommon::StaticSetDrawCommand()
{
	pplnSet_.SetDrawCommand();
}
