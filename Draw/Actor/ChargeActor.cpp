//#include "ChargeActor.h"
//
//using YActor::ChargeActor;
//using YMath::Vec3;
//using YMath::Vec4;
//
//const float ShakeRange = 100.0f;
//
//void ChargeActor::InitializeChargeAction()
//{
//	isAct_ = false;
//	isElderAct_ = false;
//	shake_.Initialize();
//	shakeVal_ = 0;
//	color_ = {};
//	isFliclering_ = false;
//}
//
//void ChargeActor::ActivateChargeAction()
//{
//	if (isElderAct_ == false)
//	{
//		InitializeChargeAction();
//	}
//
//	shakeVal_ += MaxShakeValue / MaxFrame;
//	if (shakeVal_ >= MaxShakeValue)
//	{
//		shakeVal_ = MaxShakeValue;
//	}
//
//	isAct_ = true;
//}
//
//void ChargeActor::UpdateChargeAction()
//{
//	if (isAct_ == false) 
//	{
//		InitializeChargeAction();
//		return; 
//	}
//
//	shake_.Activate(shakeVal_, 0);
//
//	shake_.Update();
//	isFliclering_ = !isFliclering_;
//
//	if (shake_.IsAct() == false)
//	{
//		InitializeChargeAction();
//	}
//
//	isElderAct_ = isAct_;
//	isAct_ = false;
//}
//
//Vec3 ChargeActor::ChargeActionShakeValue()
//{
//	Vec3 result = shake_.Value();
//
//	result /= ShakeRange;
//
//	return result;
//}
//
//Vec4 ChargeActor::ChargeActionColor()
//{
//	Vec4 result = isFliclering_ ? Color : Vec4(1.0f, 1.0f, 1.0f, 1.0f);
//
//	return result;
//}
