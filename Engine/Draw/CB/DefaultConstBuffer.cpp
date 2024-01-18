#include "DefaultConstBuffer.h"

#include <cassert>
#include <memory>
#include <unordered_map>

#include "ConstBufferObject.h"

#include "CBModelTransform.h"
#include "CBSprite2DTransform.h"
#include "CBSprite3DTransform.h"
#include "CBPostEffectTransform.h"
#include "CBColor.h"
#include "CBMaterial.h"
#include "CBTexConfig.h"


using YGame::BaseConstBuffer;
using YGame::DefaultConstBuffer;
using YGame::ConstBufferObject;

namespace
{
	std::unordered_map<std::string, BaseConstBuffer*> defCBs;

	std::unique_ptr<ConstBufferObject<YGame::CBModelTransform>> defCBModelTransform;
	std::unique_ptr<ConstBufferObject<YGame::CBSprite2DTransform>> defCBSprite2DTransform;
	std::unique_ptr<ConstBufferObject<YGame::CBSprite3DTransform>> defCBSprite3DTransform;
	std::unique_ptr<ConstBufferObject<YGame::CBPostEffectTransform>> defCBPostEffectTransform;
	std::unique_ptr<ConstBufferObject<YGame::CBColor>> defCBColor;
	std::unique_ptr<ConstBufferObject<YGame::CBMaterial>> defCBMaterial;
	std::unique_ptr<ConstBufferObject<YGame::CBTexConfig>> defCBTexConfig;
}

void DefaultConstBuffer::StaticInitialize()
{
	if (defCBModelTransform == nullptr)
	{
		defCBModelTransform.reset(ConstBufferObject<CBModelTransform>::Create(false));
		defCBs.insert({ CBModelTransform::Tag(), defCBModelTransform.get() });
	}
	if (defCBSprite2DTransform == nullptr)
	{
		defCBSprite2DTransform.reset(ConstBufferObject<CBSprite2DTransform>::Create(false));
		defCBs.insert({ CBSprite2DTransform::Tag(), defCBSprite2DTransform.get() });
	}
	if (defCBSprite3DTransform == nullptr)
	{
		defCBSprite3DTransform.reset(ConstBufferObject<CBSprite3DTransform>::Create(false));
		defCBs.insert({ CBSprite3DTransform::Tag(), defCBSprite3DTransform.get() });
	}
	if (defCBPostEffectTransform == nullptr)
	{
		defCBPostEffectTransform.reset(ConstBufferObject<CBPostEffectTransform>::Create(false));
		defCBs.insert({ CBPostEffectTransform::Tag(), defCBPostEffectTransform.get() });
	}
	if (defCBColor == nullptr)
	{
		defCBColor.reset(ConstBufferObject<CBColor>::Create(false));
		defCBs.insert({ CBColor::Tag(), defCBColor.get() });
	}
	if (defCBMaterial == nullptr)
	{
		defCBMaterial.reset(ConstBufferObject<CBMaterial>::Create(false));
		defCBs.insert({ CBMaterial::Tag(), defCBMaterial.get() });
	}
	if (defCBTexConfig == nullptr)
	{
		defCBTexConfig.reset(ConstBufferObject<CBTexConfig>::Create(false));
		defCBs.insert({ CBTexConfig::Tag(), defCBTexConfig.get() });
	}
}

BaseConstBuffer* YGame::DefaultConstBuffer::Ptr(const std::string& tag)
{
	assert(defCBs.contains(tag));

	return defCBs[tag];
}
