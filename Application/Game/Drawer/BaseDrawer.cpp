#include "BaseDrawer.h"
#include <cassert>

using YGame::BaseDrawer;

YGame::ViewProjection* BaseDrawer::spVP_ = nullptr;

void BaseDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{	
	if (obj_ == nullptr)
	{
		// オブジェクト + 定数バッファ生成
		obj_.reset(DrawObjectForModel::Create({}, spVP_, nullptr));
		
		cbColor_.reset(ConstBufferObject<CBColor>::Create());

		cbMaterial_.reset(ConstBufferObject<CBMaterial>::Create());
	}

	obj_->Initialize();

	// オブジェクトに定数バッファを設定
	obj_->InsertConstBuffer(cbColor_.get());
	obj_->InsertConstBuffer(cbMaterial_.get());
	
	SetParent(pParent);
	
	// 環境光を暗めに
	cbMaterial_->data_.ambient = { 0.2f,0.2f,0.2f };

	drawPriority_ = drawPriority;

	isVisible_ = true;

	isVisibleUpdate_ = true;

	animationBitFlag_ = 0;

	// タイマークリア後、再挿入 + 初期化
	animationTimers_.clear();

	InsertAnimationTimers();

	for (auto itr = animationTimers_.begin(); itr != animationTimers_.end(); ++itr)
	{
		itr->second.timer.Initialize(0);
	}

	animeStatus_ = {};
}

void BaseDrawer::PlayAnimation(const uint16_t index, const uint32_t frame, const bool isRoop)
{
	assert(animationTimers_.contains(index));

	PlaySubAnimation(index, frame);

	animationTimers_[index].timer.Initialize(frame, true);
	animationTimers_[index].isRoop = isRoop;

	// フラグを立てる
	animationBitFlag_ |= index;
}

void BaseDrawer::AbortAnimation(const uint16_t index)
{
	assert(animationTimers_.contains(index));
	
	animationTimers_[index].timer.Initialize(0);
	
	// フラグをおろす
	animationBitFlag_ &= ~index;
}

void BaseDrawer::Update()
{
	animeStatus_ = {};

	animeStatus_.pos_ += offset_;

	UpdateAnimationTimer();

	UpdateAnimation();

	obj_->Update(animeStatus_);

	VisibleUpdate();
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
				PlaySubAnimation(itr->first, timer.EndFrame());
				timer.Reset(true);
			}
			else
			{
				timer.Initialize(0);

				// フラグをおろす
				animationBitFlag_ &= ~itr->first;
			}
		}
	}
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
	if (distanceRate >= 0.8f) { distanceRate = 1.0f; }

	cbColor_->data_.texColorRate.a_ = distanceRate;

	// 一定値以下は描画切る
	isVisible_ = (distanceRate >= 0.25f);
}

void BaseDrawer::Draw()
{
	if (isVisible_ == false) { return; }

	obj_->Draw(shaderKey_, drawPriority_);
}

void BaseDrawer::DrawDebugTextContent()
{
}

void BaseDrawer::SetParent(Transform* pParent)
{
	if (pParent)
	{
		pParent_ = pParent;

		obj_->SetParent(&pParent->m_);
	}
	else
	{
		pParent_ = nullptr;

		obj_->SetParent(nullptr);
	}
}

void BaseDrawer::StaticInitialize(ViewProjection* pVP)
{
	assert(pVP);

	spVP_ = pVP;
}
