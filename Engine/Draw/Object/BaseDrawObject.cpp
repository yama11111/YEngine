#include "BaseDrawObject.h"
#include "PipelineManager.h"
#include <cassert>

using YGame::BaseDrawObject;

void BaseDrawObject::Draw(const std::string& shaderTag, const uint16_t drawPriority)
{
	if (isVisible_ == false) { return; }

	PipelineManager::GetInstance()->EnqueueDrawSet(shaderTag, { drawPriority, &cbPtrSet_, pGraphic_ });
}

void BaseDrawObject::SetParent(YMath::Matrix4* pParent)
{
	transform_.parent_ = pParent;
}

void BaseDrawObject::InsertConstBuffer(BaseConstBuffer* pCBuff)
{
	cbPtrSet_.Insert(pCBuff);
}

void BaseDrawObject::InsertDefaultConstBuffer(const std::string& cbTag)
{
	cbPtrSet_.InsertDefault(cbTag);
}

void BaseDrawObject::SetGraphic(BaseGraphic* pGraphic)
{
	assert(pGraphic);

	pGraphic_ = pGraphic;
}
