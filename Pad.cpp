#include "Pad.h"
#include <cassert>

using Input::Pad;

Pad* Pad::GetInstance()
{
	static Pad instance;
	return &instance;
}

void Pad::PadState::Initialize()
{
	state_.Gamepad.bLeftTrigger = state_.Gamepad.bRightTrigger = 0;

	state_.Gamepad.sThumbLX = state_.Gamepad.sThumbLY = 0;
	state_.Gamepad.sThumbRX = state_.Gamepad.sThumbRY = 0;

	state_.Gamepad.wButtons = 0;

	vibration_.wLeftMotorSpeed = vibration_.wRightMotorSpeed = 0;

	index_ = 0;

	isConnect_ = false;
}

void Pad::PadState::Connect(const DWORD index)
{
	if (index < 0 && 3 < index)
	{
		assert(false);
		return;
	}

	Initialize();

	index_ = index;
	isConnect_ = true;
}

void Pad::Create()
{
	// 生成
	pad_ = std::make_unique<PadState>();
	elderPad_ = std::make_unique<PadState>();

	dZone_[0] = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	dZone_[1] = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
	dZone_[2] = XINPUT_GAMEPAD_TRIGGER_THRESHOLD;

	Initialize();

	pad_->Connect(0);
}

void Pad::Initialize()
{
	pad_->Initialize();
	elderPad_->Initialize();
}

void Input::Pad::Update()
{
	if (!pad_->isConnect_) { return; }

	// 1フレーム前の情報を保存
	*elderPad_ = *pad_;

	// 最新の情報を取得
	DWORD result = XInputGetState(pad_->index_, &pad_->state_);
	// エラーなら初期化
	if (result != ERROR_SUCCESS) 
	{
		pad_->Initialize(); 
		elderPad_->Initialize();
	}
}

bool Pad::IsDown(const int button)
{	
	if (button == XIP_LT) 
	{
		return	(pad_->state_.Gamepad.bLeftTrigger  >= dZone_[2]); 
	}
	if (button == XIP_RT) 
	{
		return	(pad_->state_.Gamepad.bRightTrigger >= dZone_[2]); 
	}
	return (pad_->state_.Gamepad.wButtons & button);
}
bool Pad::IsTrigger(const int button)
{
	if (button == XIP_LT)
	{
		return	(pad_->state_.Gamepad.bLeftTrigger >= dZone_[2]) &&
				!(elderPad_->state_.Gamepad.bLeftTrigger >= dZone_[2]);
	}
	if (button == XIP_RT)
	{
		return	(pad_->state_.Gamepad.bLeftTrigger >= dZone_[2]) &&
				!(elderPad_->state_.Gamepad.bLeftTrigger >= dZone_[2]);
	}
	return	(pad_->state_.Gamepad.wButtons & button) && 
			!(elderPad_->state_.Gamepad.wButtons & button);
}
bool Pad::IsLongPress(const int button)
{
	if (button == XIP_LT)
	{
		return	(pad_->state_.Gamepad.bLeftTrigger >= dZone_[2]) &&
				(elderPad_->state_.Gamepad.bLeftTrigger >= dZone_[2]);
	}
	if (button == XIP_RT)
	{
		return	(pad_->state_.Gamepad.bLeftTrigger >= dZone_[2]) &&
				(elderPad_->state_.Gamepad.bLeftTrigger >= dZone_[2]);
	}
	return	(pad_->state_.Gamepad.wButtons & button) &&
			(elderPad_->state_.Gamepad.wButtons & button);
}
bool Pad::IsRelease(const int button)
{
	if (button == XIP_LT)
	{
		return	!(pad_->state_.Gamepad.bLeftTrigger >= dZone_[2]) &&
				(elderPad_->state_.Gamepad.bLeftTrigger >= dZone_[2]);
	}
	if (button == XIP_RT)
	{
		return	!(pad_->state_.Gamepad.bLeftTrigger >= dZone_[2]) &&
				(elderPad_->state_.Gamepad.bLeftTrigger >= dZone_[2]);
	}
	return	!(pad_->state_.Gamepad.wButtons & button) &&
			(elderPad_->state_.Gamepad.wButtons & button);
}

bool Pad::IsLeft(const int stick)
{
	bool result = false;
	if (stick == LStick) { result = (pad_->state_.Gamepad.sThumbLX <= -dZone_[stick]); }
	if (stick == RStick) { result = (pad_->state_.Gamepad.sThumbRX <= -dZone_[stick]); }
	return result;
}
bool Pad::IsRight(const int stick)
{
	bool result = false;
	if (stick == LStick) { result = (pad_->state_.Gamepad.sThumbLX >=  dZone_[stick]); }
	if (stick == RStick) { result = (pad_->state_.Gamepad.sThumbRX >=  dZone_[stick]); }
	return result;
}
bool Pad::IsUp(const int stick)
{
	bool result = false;
	if (stick == LStick) { result = (pad_->state_.Gamepad.sThumbLY >=  dZone_[stick]); }
	if (stick == RStick) { result = (pad_->state_.Gamepad.sThumbRY >=  dZone_[stick]); }
	return result;
}
bool Pad::IsUnder(const int stick)
{
	bool result = false;
	if (stick == LStick) { result = (pad_->state_.Gamepad.sThumbLY <= -dZone_[stick]); }
	if (stick == RStick) { result = (pad_->state_.Gamepad.sThumbRY <= -dZone_[stick]); }
	return result;
}

int Pad::Horizontal(const int stick)
{
	return IsRight(stick) - IsLeft(stick);
}
int Pad::Vertical(const int stick)
{
	return IsUnder(stick) - IsUp(stick);
}
bool Pad::IsMove(const int stick)
{
	return IsRight(stick) || IsLeft(stick) || IsUp(stick) || IsUnder(stick);
}
