#include "Object.h"
#include <cassert>

using YGame::Object;
using YGame::BaseConstBuffer;
using YGame::BaseGraphic;

void Object::Clear()
{
	pCBuffs_.clear();

	pGraphic_ = nullptr;
}

BaseConstBuffer* Object::ConstBufferPtr(const std::string& key)
{
	// –³‚¢‚È‚ç null
	if (pCBuffs_.find(key) == pCBuffs_.end())
	{
		return nullptr;
	}

	return pCBuffs_[key];
}

BaseGraphic* Object::GraphicPtr() const
{
	return pGraphic_;
}

void Object::InsertConstBuffer(BaseConstBuffer* pCBuff)
{
	assert(pCBuff);

	pCBuffs_.insert({ pCBuff->KeyName(), pCBuff});
}

void Object::SetGraphic(BaseGraphic* pGraphic)
{
	assert(pGraphic);

	pGraphic_ = pGraphic;
}
