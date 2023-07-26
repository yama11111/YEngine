#include "Object.h"
#include <cassert>

using YGame::Object;
using YDX::BaseConstBuffer;
using YGame::BaseGraphic;

void Object::Clear()
{
	cbPtrMap_.clear();

	pGraphic_ = nullptr;
}

BaseConstBuffer* Object::ConstBufferPtr(const std::string& key)
{
	// –³‚¢‚È‚ç null
	if (cbPtrMap_.find(key) == cbPtrMap_.end())
	{
		return nullptr;
	}

	return cbPtrMap_[key];
}

BaseGraphic* Object::GraphicPtr() const
{
	return pGraphic_;
}

void Object::InsertConstBuffer(BaseConstBuffer* pCBuff)
{
	assert(pCBuff);

	cbPtrMap_.insert({ pCBuff->TypeName(), pCBuff});
}

void Object::SetGraphic(BaseGraphic* pGraphic)
{
	assert(pGraphic);

	pGraphic_ = pGraphic;
}
