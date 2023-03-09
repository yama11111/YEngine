#include "PlayerDrawer.h"

using YGame::PlayerDrawerCommon;
using YGame::PlayerDrawer;
using YGame::Model;
using YGame::ObjectModel;

std::array<std::unique_ptr<Model>, PlayerDrawerCommon::PartsNum_> PlayerDrawerCommon::pModels_ =
{ nullptr, nullptr, nullptr };

void PlayerDrawerCommon::StaticInitialize(const StaticInitStatus& state)
{
	pModels_[static_cast<size_t>(Parts::Body)].reset(Model::LoadObj("player/player_body", true));
	pModels_[static_cast<size_t>(Parts::Face)].reset(Model::LoadObj("player/player_face", true));
	pModels_[static_cast<size_t>(Parts::Tail)].reset(Model::LoadObj("player/player_tail", true));
}

void PlayerDrawer::Initialize(YMath::Matrix4* pParent)
{
	for (size_t i = 0; i < objs_.size(); i++)
	{
		objs_[i].reset(ObjectModel::Create({}));
		objs_[i]->parent_ = pParent;
	}
	Reset();
}

void PlayerDrawer::Reset()
{
	for (size_t i = 0; i < objs_.size(); i++)
	{
		objs_[i]->Initialize({});
	}
	objs_[static_cast<size_t>(Parts::Tail)]->pos_ = { 0,0,-1.75f };
}

void PlayerDrawer::Update()
{
	for (size_t i = 0; i < objs_.size(); i++)
	{
		objs_[i]->UpdateMatrix();
	}
}

void PlayerDrawer::Draw(const YGame::ViewProjection& vp, YGame::LightGroup* lightGroup)
{
	for (size_t i = 0; i < pModels_.size(); i++)
	{
		pModels_[i]->Draw(objs_[i].get(), vp, lightGroup);
	}
}

