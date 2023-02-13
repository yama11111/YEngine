//#include "ChargeActor.h"
//
//using YActor::ChargeActor;
//using YMath::Vector3;
//using YMath::Vector4;
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
//Vector3 ChargeActor::ChargeActionShakeValue()
//{
//	Vector3 result = shake_.Value();
//
//	result /= ShakeRange;
//
//	return result;
//}
//
//Vector4 ChargeActor::ChargeActionColor()
//{
//	Vector4 result = isFliclering_ ? Color : Vector4(1.0f, 1.0f, 1.0f, 1.0f);
//
//	return result;
//}
