//#include "CoinDrawer.h"
//#include "SkydomeDrawer.h"
//#include "ColorConfig.h"
//#include "Lerp.h"
//#include "Def.h"
//
//using YGame::CoinDrawer;
//using YGame::Model;
//using YMath::Vector3;
//using YMath::Vector4;
//
//Model* CoinDrawer::spModel_ = nullptr;
//
//CoinDrawer* CoinDrawer::Create(Transform* pParent, const size_t drawPriority)
//{
//	CoinDrawer* newDrawer = new CoinDrawer();
//
//	newDrawer->Initialize(pParent, drawPriority);
//
//	return newDrawer;
//}
//
//void CoinDrawer::LoadResource()
//{
//	// モデル設定
//	spModel_ = Model::LoadObj("skydome", true);
//}
//
//void CoinDrawer::Initialize(Transform* pParent, const size_t drawPriority)
//{
//	// オブジェクト初期化
//	BaseDrawer::Initialize(pParent, drawPriority);
//
//	if (backTexConfig_ == nullptr)
//	{
//		backTexConfig_.reset(ConstBufferObject<CBTexConfig>::Create());
//	}
//	obj_->InsertConstBuffer(backTexConfig_.get());
//
//	backTexConfig_->data_.tiling = { 50.0f,50.0f };
//
//	//cbColor_->data_.baseColor = YGame::ColorConfig::skTurquoise[0];
//	//cbMaterial_->data_.ambient = Vector3(0.8f, 0.8f, 0.8f);
//
//	isVisibleUpdate_ = false;
//
//	// モデル挿入
//	obj_->SetModel(spModel_);
//
//	shaderKey_ = "ModelDefault";
//
//	PlayAnimation(static_cast<uint16_t>(AnimationType::eIdle), 240, true);
//}
//
//void CoinDrawer::InsertAnimationTimers()
//{
//	// アニメーションの数だけタイマー作成
//	animationTimers_.insert({ static_cast<uint16_t>(AnimationType::eIdle), AnimationTimer(YMath::Timer(), true) });
//}
//
//void CoinDrawer::UpdateAnimation()
//{
//	float ratio = animationTimers_[static_cast<uint16_t>(AnimationType::eIdle)].timer.Ratio();
//	float offsetX = YMath::Lerp(0.0f, 1.0f, ratio);
//	float offsetY = YMath::Lerp(0.0f, 1.0f, ratio);
//
//	backTexConfig_->data_.offset = { offsetX, offsetY };
//}