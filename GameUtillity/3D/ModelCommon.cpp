#include "ModelCommon.h"

using YGame::ModelCommon;

YDX::PipelineSet ModelCommon::pplnSet_;

void ModelCommon::StaticInitialize(const StaticInitStatus& state)
{
	pplnSet_.Initialize(YDX::PipelineSet::Type::ModelT, state.rootParams_);
}

void ModelCommon::StaticSetDrawCommand()
{
	pplnSet_.SetDrawCommand();
}