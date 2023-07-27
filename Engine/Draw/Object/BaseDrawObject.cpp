#include "BaseDrawObject.h"
#include "PipelineManager.h"
#include <cassert>

using YGame::BaseDrawObject;

void BaseDrawObject::Draw(const std::string& shaderTag, const uint16_t drawPriority)
{
	PipelineManager::GetInstance()->EnqueueDrawSet(shaderTag, { drawPriority, &cbPtrSet_, pGraphic_ });
}

void BaseDrawObject::SetParent(Transform* pParent)
{
	pParent_ = pParent;

	// トランスフォームの親子関係も合わせて変更
	if (pParent_)
	{
		transform_.parent_ = &pParent->m_;
	}
	else
	{
		transform_.parent_ = nullptr;
	}
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
