#include "DefaultGraphic.h"

#include <cassert>
#include <unordered_map>

#include "Model.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "PostEffect.h"

using YGame::DefaultGraphic;
using YGame::BaseGraphic;

static std::unordered_map<std::string, BaseGraphic*> sDefGraphics;

static YGame::Model* spModel = nullptr;
static YGame::Sprite2D* spSprite2D = nullptr;
static YGame::Sprite3D* spSprite3D = nullptr;
static YGame::PostEffect* spPostEffect = nullptr;

void DefaultGraphic::LoadResource()
{
	sDefGraphics.clear();

	Texture* pTex = Texture::Load("white1x1.png");

	spModel = Model::CreateCube({ { "Texture0", pTex } });
	sDefGraphics.insert({ GraphicType::kModelTag, spModel });

	spSprite2D = Sprite2D::Create({ { "Texture0", pTex } });
	sDefGraphics.insert({ GraphicType::kSprite2DTag, spSprite2D });

	spSprite3D = Sprite3D::Create({ { "Texture0", pTex } });
	sDefGraphics.insert({ GraphicType::kSprite3DTag, spSprite3D });

	spPostEffect = PostEffect::Create({ { "Texture0" } });
	sDefGraphics.insert({ GraphicType::kPostEffectTag, spPostEffect });
}

BaseGraphic* DefaultGraphic::Ptr(const std::string& tag)
{
	assert(sDefGraphics.contains(tag));

	return sDefGraphics[tag];
}
