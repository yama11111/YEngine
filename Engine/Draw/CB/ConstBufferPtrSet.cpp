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

	// ���ɂ���Ȃ����ւ�
	if (cbPtrMap_.contains(pCB->Tag()))
	{
		cbPtrMap_[pCB->Tag()] = pCB;

		return;
	}
	
	// �{�̂̃^�O�����̂܂܃L�[�ɂ��đ}��
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
