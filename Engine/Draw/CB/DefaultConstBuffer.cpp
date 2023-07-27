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
#include "CBLightGroup.h"
#include "CBTexConfig.h"
#include "CBTime.h"


using YGame::BaseConstBuffer;
using YGame::DefaultConstBuffer;
using YGame::ConstBufferObject;

static std::unordered_map<std::string, BaseConstBuffer*> sDefCBs;

static std::unique_ptr<ConstBufferObject<YGame::CBModelTransform>> sDefCBModelTransform;
static std::unique_ptr<ConstBufferObject<YGame::CBSprite2DTransform>> sDefCBSprite2DTransform;
static std::unique_ptr<ConstBufferObject<YGame::CBSprite3DTransform>> sDefCBSprite3DTransform;
static std::unique_ptr<ConstBufferObject<YGame::CBPostEffectTransform>> sDefCBPostEffectTransform;
static std::unique_ptr<ConstBufferObject<YGame::CBColor>> sDefCBColor;
static std::unique_ptr<ConstBufferObject<YGame::CBMaterial>> sDefCBMaterial;
static std::unique_ptr<ConstBufferObject<YGame::CBLightGroup>> sDefCBLightGroup;
static std::unique_ptr<ConstBufferObject<YGame::CBTexConfig>> sDefCBTexConfig;
static std::unique_ptr<ConstBufferObject<YGame::CBTime>> sDefCBTime;

void DefaultConstBuffer::StaticInitialize()
{
	sDefCBModelTransform.reset(ConstBufferObject<CBModelTransform>::Create(false));
	sDefCBs.insert({ CBModelTransform::Tag(), sDefCBModelTransform.get() });

	sDefCBSprite2DTransform.reset(ConstBufferObject<CBSprite2DTransform>::Create(false));
	sDefCBs.insert({ CBSprite2DTransform::Tag(), sDefCBSprite2DTransform.get() });

	sDefCBSprite3DTransform.reset(ConstBufferObject<CBSprite3DTransform>::Create(false));
	sDefCBs.insert({ CBSprite3DTransform::Tag(), sDefCBSprite3DTransform.get() });

	sDefCBPostEffectTransform.reset(ConstBufferObject<CBPostEffectTransform>::Create(false));
	sDefCBs.insert({ CBPostEffectTransform::Tag(), sDefCBPostEffectTransform.get() });

	sDefCBColor.reset(ConstBufferObject<CBColor>::Create(false));
	sDefCBs.insert({ CBColor::Tag(), sDefCBColor.get() });

	sDefCBMaterial.reset(ConstBufferObject<CBMaterial>::Create(false));
	sDefCBs.insert({ CBMaterial::Tag(), sDefCBMaterial.get() });

	sDefCBLightGroup.reset(ConstBufferObject<CBLightGroup>::Create(false));
	sDefCBs.insert({ CBLightGroup::Tag(), sDefCBLightGroup.get() });

	sDefCBTexConfig.reset(ConstBufferObject<CBTexConfig>::Create(false));
	sDefCBs.insert({ CBTexConfig::Tag(), sDefCBTexConfig.get() });

	sDefCBTime.reset(ConstBufferObject<CBTime>::Create(false));
	sDefCBs.insert({ CBTime::Tag(), sDefCBTime.get() });
}

BaseConstBuffer* YGame::DefaultConstBuffer::Ptr(const std::string& tag)
{
	assert(sDefCBs.contains(tag));

	return sDefCBs[tag];
}
