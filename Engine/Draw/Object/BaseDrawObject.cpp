#include "BaseDrawObject.h"
#include "PipelineManager.h"
#include <cassert>

using YGame::BaseDrawObject;

void BaseDrawObject::Draw()
{
	if (isVisible_ == false) { return; }

	PipelineManager::GetInstance()->EnqueueDrawSet(shaderTag_, drawPriority_, { &cbPtrSet_, pGraphic_ });
}

void BaseDrawObject::Draw(const std::string& shaderTag, const size_t drawPriority)
{
	if (isVisible_ == false) { return; }

	PipelineManager::GetInstance()->EnqueueDrawSet(shaderTag, drawPriority, { &cbPtrSet_, pGraphic_ });
}

void BaseDrawObject::Draw(const std::string& shaderTag, const size_t drawPriority, BaseGraphic* pGraphic)
{
	if (isVisible_ == false) { return; }

	PipelineManager::GetInstance()->EnqueueDrawSet(shaderTag, drawPriority, { &cbPtrSet_, pGraphic });
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