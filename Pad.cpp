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
	return	(pad_->state_.Gamepad.wButtons & button);
}
bool Pad::IsTrigger(const int button)
{
	return	(pad_->state_.Gamepad.wButtons & button) && 
			!(elderPad_->state_.Gamepad.wButtons & button);
}
bool Pad::IsLongPress(const int button)
{
	return	(pad_->state_.Gamepad.wButtons & button) &&
			(elderPad_->state_.Gamepad.wButtons & button);
}
bool Pad::IsRelease(const int button)
{
	return	!(pad_->state_.Gamepad.wButtons & button) &&
			(elderPad_->state_.Gamepad.wButtons & button);
}

bool Pad::IsLeft()
{
	return pad_->state_.Gamepad.sThumbLX >=  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
}
bool Pad::IsRight()
{
	return pad_->state_.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
}
bool Pad::IsUp()
{
	return pad_->state_.Gamepad.sThumbLY >=  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
}
bool Pad::IsUnder()
{
	return pad_->state_.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
}

int Pad::Horizontal()
{
	return IsRight() - IsLeft();
}
int Pad::Vertical()
{
	return IsUnder() - IsUp();
}
bool Pad::IsMove()
{
	return IsRight() || IsLeft() || IsUp() || IsUnder();
}
