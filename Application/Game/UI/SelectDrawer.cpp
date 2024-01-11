#include "SelectDrawer.h"
#include "StageManager.h"
#include "Lerp.h"
#include "Def.h"
#include <cassert>

using YGame::SelectDrawer;
using YMath::Vector2;
using YMath::Vector3;

YGame::ViewProjection* SelectDrawer::spVP_ = nullptr;
YGame::Sprite3D* SelectDrawer::spBackSpr_ = nullptr;

namespace 
{
	YGame::ViewProjection sVP;
}

void SelectDrawer::LoadResource()
{
	spBackSpr_ = Sprite3D::Create({ { "Texture0", Texture::Load("select/back.png")} });
}

void SelectDrawer::SetViewProjection(ViewProjection* pVP)
{
	assert(pVP);
	spVP_ = pVP;

	StageDrawer::SetViewProjection(pVP);

	sVP.Initialize();
	sVP.eye_ = { 0.0f,0.0f,-5.0f };
	sVP.UpdateMatrix();
}

void SelectDrawer::Initialize()
{
	stageIndex_ = 0;

	stages_.resize(StageManager::GetInstance()->MaxStageNum());
	for (size_t i = 0; i < stages_.size(); i++)
	{
		stages_[i].trfm.Initialize();
		
		StageManager::StageStatus status = StageManager::GetInstance()->Status(i);
		
		bool isTutotial = status.isTutorial;
		std::array<uint32_t, 3> score = status.mission;
		std::array<bool, 3> mission = status.isMissionClear;
		uint32_t stageNum = static_cast<uint32_t>(i + 1);
		
		stages_[i].stage.Initialize(&stages_[i].trfm.m_, stageNum, isTutotial, mission);
		stages_[i].status.Initialize(stageNum, isTutotial, score, mission);

		stages_[i].followPointPow_.Initialize(20);
	}
	followPointEas_.Initialize({}, Vector3(2.0f, 0.0f, 3.5f), 3.0f);
	offsetEas_.Initialize({}, Vector2(2.0f, 3.5f) / 20.0f, 3.0f);

	popTimer_.Initialize(5);

	if (back_ == nullptr)
	{
		back_.reset(DrawObjectForSprite3D::Create(Transform::Status::Default(), false, false, &sVP, spBackSpr_));
	}
	if (backColor_ == nullptr)
	{
		backColor_.reset(ConstBufferObject<CBColor>::Create());
	}
	back_->InsertConstBuffer(backColor_.get());
	if (backTexConfig_ == nullptr)
	{
		backTexConfig_.reset(ConstBufferObject<CBTexConfig>::Create());
	}
	back_->InsertConstBuffer(backTexConfig_.get());

	offsetTimer_.Initialize(240);
	
	Reset();
}

void SelectDrawer::Reset()
{
	for (size_t i = 0; i < stages_.size(); i++)
	{
		stages_[i].trfm.Initialize();
		stages_[i].trfm.pos_ = Vector3(-3.0f, -5.0f, 0.0f) + Vector3(2.0f * i, 0.0f, 3.5f * i);
		stages_[i].trfm.rota_.x_ = kPI / 2.0f;
		stages_[i].stage.Reset();

		stages_[i].status.Reset();
		
		stages_[i].isPop = false;
		
		stages_[i].followPointPow_.Reset();
	}

	popTimer_.Reset();
	
	back_->transform_.rota_ = { 0.0f,0.0f,kPI - kPI / 4.0f };
	back_->transform_.scale_ = { 8.0f,8.0f,0.0f };
	backColor_->data_.baseColor = { 0.25f,0.25f,0.25f,1.0f };
	backTexConfig_->data_.tiling = { 16.0f, 16.0f };
	
	offsetTimer_.Reset(true);
}

void SelectDrawer::SetStageIndex(const int32_t index)
{
	assert(0 <= index && index < stages_.size());

	stageIndex_ = index; 

	for (size_t i = 0; i < stages_.size(); i++)
	{
		if (i == stageIndex_)
		{
			stages_[i].stage.SelectAnimation();
			stages_[i].status.AppearAnimation();
		}
		else
		{
			stages_[i].stage.ReleseAnimation();
			stages_[i].status.DisappearAnimation();
		}
	}
}

void SelectDrawer::PopAnimation()
{
	popTimer_.Reset(true);
}

Vector3 SelectDrawer::FollowPoint() const
{
	Vector3 result;
	for (size_t i = 0; i < stages_.size(); i++)
	{
		result += followPointEas_.InOut(stages_[i].followPointPow_.Ratio());
	}

	return result;
}

void SelectDrawer::Update()
{
	popTimer_.Update();
	if (popTimer_.IsEnd())
	{
		bool isAct = false;
		for (size_t i = 0; i < stages_.size(); i++)
		{
			if(stages_[i].isPop == false)
			{
				stages_[i].stage.PopAnimation();
				stages_[i].isPop = true;
				isAct = true;
				break;
			}
			isAct = false;
		}
		popTimer_.Reset(isAct);
	}

	for (size_t i = 0; i < stages_.size(); i++)
	{
		stages_[i].trfm.UpdateMatrix();
		stages_[i].stage.Update();
		stages_[i].status.Update();

		bool isActPow = (i < stageIndex_);
		stages_[i].followPointPow_.Update(isActPow);
	}

	Vector2 offset;
	
	if (offsetTimer_.IsEnd())
	{
		offsetTimer_.Reset(true);
	}
	else
	{
		offsetTimer_.Update();
	}

	offset.x_ += YMath::Lerp(0.0f, 1.0f, offsetTimer_.Ratio());
	
	for (size_t i = 0; i < stages_.size(); i++)
	{
		offset += offsetEas_.InOut(stages_[i].followPointPow_.Ratio());
	}

	backTexConfig_->data_.offset = offset;

	back_->Update();
}

void SelectDrawer::Draw()
{
	back_->Draw("Sprite3DDefault", 2);

	for (size_t i = 0; i < stages_.size(); i++)
	{
		stages_[i].stage.Draw();
		stages_[i].status.Draw();
	}
}
