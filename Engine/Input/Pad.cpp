#include "Pad.h"
#include <cassert>

using YInput::Pad;

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

void YInput::Pad::Update()
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

bool Pad::IsDown(const PadButton& button)
{
	if (button == PadButton::XIP_LT)
	{
		return	(pad_->state_.Gamepad.bLeftTrigger >= dZone_[2]);
	}
	if (button == PadButton::XIP_RT)
	{
		return	(pad_->state_.Gamepad.bRightTrigger >= dZone_[2]);
	}
	return (pad_->state_.Gamepad.wButtons & static_cast<int>(button));
}
bool Pad::IsTrigger(const PadButton& button)
{
	if (button == PadButton::XIP_LT)
	{
		return	(pad_->state_.Gamepad.bLeftTrigger >= dZone_[2]) &&
			!(elderPad_->state_.Gamepad.bLeftTrigger >= dZone_[2]);
	}
	if (button == PadButton::XIP_RT)
	{
		return	(pad_->state_.Gamepad.bLeftTrigger >= dZone_[2]) &&
			!(elderPad_->state_.Gamepad.bLeftTrigger >= dZone_[2]);
	}
	return	(pad_->state_.Gamepad.wButtons & static_cast<int>(button)) &&
			(elderPad_->state_.Gamepad.wButtons & static_cast<int>(button)) == false;
}
bool Pad::IsLongPress(const PadButton& button)
{
	if (button == PadButton::XIP_LT)
	{
		return	(pad_->state_.Gamepad.bLeftTrigger >= dZone_[2]) &&
			(elderPad_->state_.Gamepad.bLeftTrigger >= dZone_[2]);
	}
	if (button == PadButton::XIP_RT)
	{
		return	(pad_->state_.Gamepad.bLeftTrigger >= dZone_[2]) &&
			(elderPad_->state_.Gamepad.bLeftTrigger >= dZone_[2]);
	}
	return	(pad_->state_.Gamepad.wButtons & static_cast<int>(button)) &&
			(elderPad_->state_.Gamepad.wButtons & static_cast<int>(button));
}
bool Pad::IsRelease(const PadButton& button)
{
	if (button == PadButton::XIP_LT)
	{
		return	!(pad_->state_.Gamepad.bLeftTrigger >= dZone_[2]) &&
				(elderPad_->state_.Gamepad.bLeftTrigger >= dZone_[2]);
	}
	if (button == PadButton::XIP_RT)
	{
		return	!(pad_->state_.Gamepad.bLeftTrigger >= dZone_[2]) &&
				(elderPad_->state_.Gamepad.bLeftTrigger >= dZone_[2]);
	}
	return	(pad_->state_.Gamepad.wButtons & static_cast<int>(button)) == false &&
			(elderPad_->state_.Gamepad.wButtons & static_cast<int>(button));
}

bool Pad::IsLeft(const PadStick& stick)
{
	bool result = false;
	size_t idx = static_cast<size_t>(stick);
	if (stick == PadStick::LStick) { result = (pad_->state_.Gamepad.sThumbLX <= -dZone_[idx]); }
	if (stick == PadStick::RStick) { result = (pad_->state_.Gamepad.sThumbRX <= -dZone_[idx]); }
	return result;
}
bool Pad::IsRight(const PadStick& stick)
{
	bool result = false;
	size_t idx = static_cast<size_t>(stick);
	if (stick == PadStick::LStick) { result = (pad_->state_.Gamepad.sThumbLX >= dZone_[idx]); }
	if (stick == PadStick::RStick) { result = (pad_->state_.Gamepad.sThumbRX >= dZone_[idx]); }
	return result;
}
bool Pad::IsUp(const PadStick& stick)
{
	bool result = false;
	size_t idx = static_cast<size_t>(stick);
	if (stick == PadStick::LStick) { result = (pad_->state_.Gamepad.sThumbLY >= dZone_[idx]); }
	if (stick == PadStick::RStick) { result = (pad_->state_.Gamepad.sThumbRY >= dZone_[idx]); }
	return result;
}
bool Pad::IsUnder(const PadStick& stick)
{
	bool result = false;
	size_t idx = static_cast<size_t>(stick);
	if (stick == PadStick::LStick) { result = (pad_->state_.Gamepad.sThumbLY <= -dZone_[idx]); }
	if (stick == PadStick::RStick) { result = (pad_->state_.Gamepad.sThumbRY <= -dZone_[idx]); }
	return result;
}

int Pad::Horizontal(const PadStick& stick)
{
	return IsRight(stick) - IsLeft(stick);
}
int Pad::Vertical(const PadStick& stick)
{
	return IsUnder(stick) - IsUp(stick);
}
bool Pad::IsMove(const PadStick& stick)
{
	return IsRight(stick) || IsLeft(stick) || IsUp(stick) || IsUnder(stick);
}
