#include "BaseDrawer.h"
#include <cassert>

using YGame::BaseDrawer;

YGame::ViewProjection* BaseDrawer::spVP_ = nullptr;

void BaseDrawer::StaticInitialize(ViewProjection* pVP)
{
	assert(pVP);

	spVP_ = pVP;
}

void BaseDrawer::Initialize(Transform* pParent, YMath::Vector3* pParentWorldPos, const size_t drawPriority)
{	
	if (cbColor_ == nullptr)
	{
		cbColor_.reset(ConstBufferObject<CBColor>::Create());
	}
	if (cbMaterial_ == nullptr)
	{
		cbMaterial_.reset(ConstBufferObject<CBMaterial>::Create());
	}

	transform_.Initialize();

	InitializeObjects();

	assert(0 < objs_.size());

	InsertConstBuffer(cbColor_.get());
	InsertConstBuffer(cbMaterial_.get());
	
	SetParent(pParent);
	SetParentWorldPos(pParentWorldPos);

	SetDrawPriority(drawPriority);

	SetIsVisible(true);

	isVisibleUpdate_ = true;

	animationBitFlag_ = 0;

	InitializeTimers();

	for (auto itr = animationTimers_.begin(); itr != animationTimers_.end(); ++itr)
	{
		itr->second.timer.Reset();
	}

	animeStatus_ = {};
}

void BaseDrawer::InitializeTimers()
{
}

void BaseDrawer::PlayAnimation(const uint32_t index, const bool isTimerReset)
{
	assert(animationTimers_.contains(index));

	GetReadyForAnimation(index);

	if (isTimerReset)
	{
		animationTimers_[index].timer.Reset();
	}

	animationTimers_[index].timer.SetActive(true);

	// フラグを立てる
	animationBitFlag_ |= index;
}

void BaseDrawer::StopAnimation(const uint32_t index)
{
	assert(animationTimers_.contains(index));

	animationTimers_[index].timer.SetActive(false);

	// フラグをおろす
	animationBitFlag_ &= ~index;
}

void BaseDrawer::GetReadyForAnimation(const uint32_t index)
{
	index;
}

void BaseDrawer::UpdateAnimationTimer()
{
	for (auto itr = animationTimers_.begin(); itr != animationTimers_.end(); ++itr)
	{
		// アニメーションしないなら飛ばす
		if ((animationBitFlag_ & itr->first) == 0) { continue; }

		YMath::Timer& timer = itr->second.timer;

		timer.Update();

		if (timer.IsEnd())
		{
			if (itr->second.isRoop)
			{
				// アニメーションをもう一度始める
				GetReadyForAnimation(itr->first);
				timer.Reset(true);
			}
			else
			{
				// フラグをおろす
				animationBitFlag_ &= ~itr->first;
			}
		}
	}
}

void BaseDrawer::UpdateAnimation()
{
}

void BaseDrawer::VisibleUpdate()
{
	if (isVisibleUpdate_ == false) { return; }

	// 視点との距離
	float distance = YMath::Vector3(spVP_->eye_ - pParent_->pos_).Length();

	// 描画範囲
	static const float kRange = 750.0f;

	// 視点との距離の比率でアルファ値変化(遠いほど薄く)
	float distanceRate = 1.0f - distance / kRange;
	if (distanceRate >= 1.0f) { distanceRate = 1.0f; }

	cbColor_->data_.texColorRate.w = distanceRate;

	// 一定値以下は描画切る
	SetIsVisible((distanceRate >= 0.01f));
}

void BaseDrawer::Update()
{
	animeStatus_ = {};

	animeStatus_.pos_ += offset_;

	UpdateAnimationTimer();

	UpdateAnimation();

	transform_.UpdateMatrix(animeStatus_);

	for (auto itr = objs_.begin(); itr != objs_.end(); ++itr)
	{
		itr->second->Update();
	}

	VisibleUpdate();
}

void BaseDrawer::Draw()
{
	for (auto itr = objs_.begin(); itr != objs_.end(); ++itr)
	{
		itr->second->Draw();
	}
}

void BaseDrawer::DrawDebugTextContent()
{
}

void BaseDrawer::SetParent(Transform* pParent)
{
	pParent_ = pParent;
	
	if (pParent)
	{
		transform_.parent_ = &pParent->m;
	}
	else
	{
		transform_.parent_ = nullptr;
	}
}

void BaseDrawer::SetParentWorldPos(YMath::Vector3* pParentWorldPos)
{
	pParentWorldPos_ = pParentWorldPos;
}

void BaseDrawer::InsertObject(const std::string& objTag, BaseDrawObject* pObj)
{
	assert(pObj);

	// 初期設定
	pObj->Initialize();
	pObj->SetParent(&transform_.m);
	pObj->InsertConstBuffer(cbColor_.get());
	pObj->InsertConstBuffer(cbMaterial_.get());

	// 無ければ新規挿入
	if (objs_.contains(objTag) == false)
	{
		objs_.insert({ objTag, nullptr});
	}

	objs_[objTag].reset(pObj);
}

void BaseDrawer::InsertConstBuffer(BaseConstBuffer* pCB)
{
	for (auto itr = objs_.begin(); itr != objs_.end(); ++itr)
	{
		itr->second->InsertConstBuffer(pCB);
	}
}
void BaseDrawer::InsertConstBuffer(const std::string& objTag, BaseConstBuffer* pCB)
{
	assert(objs_.contains(objTag));

	objs_[objTag]->InsertConstBuffer(pCB);
}

void BaseDrawer::SetShaderTag(const std::string& shaderTag)
{
	for (auto itr = objs_.begin(); itr != objs_.end(); ++itr)
	{
		itr->second->SetShaderTag(shaderTag);
	}
}
void BaseDrawer::SetShaderTag(const std::string& objTag, const std::string& shaderTag)
{
	assert(objs_.contains(objTag));

	objs_[objTag]->SetShaderTag(shaderTag);
}

void BaseDrawer::SetDrawPriority(const size_t drawPriority)
{
	for (auto itr = objs_.begin(); itr != objs_.end(); ++itr)
	{
		itr->second->SetDrawPriority(drawPriority);
	}
}

void BaseDrawer::SetIsVisible(const bool isVisible)
{
	for (auto itr = objs_.begin(); itr != objs_.end(); ++itr)
	{
		itr->second->SetIsVisible(isVisible);
	}
}

void BaseDrawer::InsertAnimationTimer(const uint32_t index, const AnimationTimer& timer)
{
	// 既にあるなら入れ替え
	if (animationTimers_.contains(index))
	{
		animationTimers_[index] = timer;

		return;
	}

	animationTimers_.insert({ index, timer });
}

bool BaseDrawer::IsEndTimer(const uint32_t index)
{
	assert(animationTimers_.contains(index));

	return animationTimers_[index].timer.IsEnd();
}

bool BaseDrawer::IsActAnimation(const uint32_t index)
{
	return animationBitFlag_ & index;
}
