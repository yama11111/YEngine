#include "DefaultConstBuffer.h"

#include <cassert>
#include <memory>
#include <unordered_map>

#include "ConstBuffer.h"

#include "CBModelTransform.h"
#include "CBSprite2DTransform.h"
#include "CBSprite3DTransform.h"
#include "CBPostEffectTransform.h"
#include "CBColor.h"
#include "CBMaterial.h"
#include "CBLightGroup.h"
#include "CBTexConfig.h"
#include "CBTime.h"


using YDX::BaseConstBuffer;
using YGame::DefaultConstBuffer;
using YGame::ConstBuffer;

static std::unordered_map<std::string, BaseConstBuffer*> sDefCBs;

static std::unique_ptr<ConstBuffer<YGame::CBModelTransform>> sDefCBModelTransform;
static std::unique_ptr<ConstBuffer<YGame::CBSprite2DTransform>> sDefCBSprite2DTransform;
static std::unique_ptr<ConstBuffer<YGame::CBSprite3DTransform>> sDefCBSprite3DTransform;
static std::unique_ptr<ConstBuffer<YGame::CBPostEffectTransform>> sDefCBPostEffectTransform;
static std::unique_ptr<ConstBuffer<YGame::CBColor>> sDefCBColor;
static std::unique_ptr<ConstBuffer<YGame::CBMaterial>> sDefCBMaterial;
static std::unique_ptr<ConstBuffer<YGame::CBLightGroup>> sDefCBLightGroup;
static std::unique_ptr<ConstBuffer<YGame::CBTexConfig>> sDefCBTexConfig;
static std::unique_ptr<ConstBuffer<YGame::CBTime>> sDefCBTime;

void DefaultConstBuffer::StaticInitialize()
{
	sDefCBModelTransform.reset(ConstBuffer<CBModelTransform>::Create(false));
	sDefCBs.insert({ CBModelTransform::TypeName(), sDefCBModelTransform.get() });

	sDefCBSprite2DTransform.reset(ConstBuffer<CBSprite2DTransform>::Create(false));
	sDefCBs.insert({ CBSprite2DTransform::TypeName(), sDefCBSprite2DTransform.get() });

	sDefCBSprite3DTransform.reset(ConstBuffer<CBSprite3DTransform>::Create(false));
	sDefCBs.insert({ CBSprite3DTransform::TypeName(), sDefCBSprite3DTransform.get() });

	sDefCBPostEffectTransform.reset(ConstBuffer<CBPostEffectTransform>::Create(false));
	sDefCBs.insert({ CBPostEffectTransform::TypeName(), sDefCBPostEffectTransform.get() });

	sDefCBColor.reset(ConstBuffer<CBColor>::Create(false));
	sDefCBs.insert({ CBColor::TypeName(), sDefCBColor.get() });

	sDefCBMaterial.reset(ConstBuffer<CBMaterial>::Create(false));
	sDefCBs.insert({ CBMaterial::TypeName(), sDefCBMaterial.get() });

	sDefCBLightGroup.reset(ConstBuffer<CBLightGroup>::Create(false));
	sDefCBs.insert({ CBLightGroup::TypeName(), sDefCBLightGroup.get() });

	sDefCBTexConfig.reset(ConstBuffer<CBTexConfig>::Create(false));
	sDefCBs.insert({ CBTexConfig::TypeName(), sDefCBTexConfig.get() });

	sDefCBTime.reset(ConstBuffer<CBTime>::Create(false));
	sDefCBs.insert({ CBTime::TypeName(), sDefCBTime.get() });
}

BaseConstBuffer* YGame::DefaultConstBuffer::Ptr(const std::string& typeName)
{
	assert(sDefCBs.contains(typeName));

	return sDefCBs[typeName];
}
