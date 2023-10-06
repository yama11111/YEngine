#include "ConstBufferPtrSet.h"
#include "DefaultConstBuffer.h"
#include <cassert>

using YGame::ConstBufferPtrSet;

void ConstBufferPtrSet::Clear()
{
	if (cbPtrMap_.empty()) { return; }

	cbPtrMap_.clear();
}

void ConstBufferPtrSet::Insert(BaseConstBuffer* pCB)
{
	assert(pCB);

	// 既にあるなら入れ替え
	if (cbPtrMap_.contains(pCB->Tag()))
	{
		cbPtrMap_[pCB->Tag()] = pCB;

		return;
	}
	
	// 本体のタグをそのままキーにして挿入
	cbPtrMap_.insert({ pCB->Tag(), pCB });
}

void ConstBufferPtrSet::InsertDefault(const std::string& tag)
{
	Insert(DefaultConstBuffer::Ptr(tag));
}

void ConstBufferPtrSet::SetDrawCommand(const std::string& tag, const uint32_t rpIndex)
{
	assert(cbPtrMap_.contains(tag));

	cbPtrMap_[tag]->SetDrawCommand(rpIndex);
}
