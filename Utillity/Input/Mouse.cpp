#include "Mouse.h"
#include "YAssert.h"

using YInput::Mouse;

Mouse* Mouse::GetInstance()
{
	static Mouse instance;
	return &instance;
}

void Mouse::MouseState::Initialize()
{
	state_.lX = state_.lY = state_.lZ = 0;

	for (size_t i = 0; i < 4; i++) { state_.rgbButtons[i] = 0; }

	pos_ = { 0,0 };
}

void Mouse::Create(const HWND hwnd, IDirectInput8* directInput)
{
	// ����
	mouse_ = std::make_unique<MouseState>();
	elderMouse_ = std::make_unique<MouseState>();

	// �}�E�X�f�o�C�X ����
	YDX::Result(directInput->CreateDevice(GUID_SysMouse, &device_, NULL));

	// ���̓f�[�^�`���Z�b�g
	YDX::Result(device_->SetDataFormat(&c_dfDIMouse));

	// �r�����䃌�x���Z�b�g
	YDX::Result(device_->SetCooperativeLevel(
		hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY));

	Initialize();
}

void Mouse::Initialize()
{
	mouse_->Initialize();
	elderMouse_->Initialize();
}

void Mouse::Update(const HWND hwnd)
{
	// 1�t���[���O�̏���ۑ�
	*elderMouse_ = *mouse_;

	// �ŐV�̏����擾
	device_->Acquire();
	device_->Poll();

	// ���͏�Ԃ��擾
	device_->GetDeviceState(sizeof(DIMOUSESTATE), &mouse_->state_);

	// �ʒu���擾
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(hwnd, &pos);

	mouse_->pos_ = { static_cast<float>(pos.x), static_cast<float>(pos.y) };
}

bool Mouse::IsDown(const MouseClick& button)
{
	return mouse_->state_.rgbButtons[static_cast<size_t>(button)];
}
bool Mouse::IsTrigger(const MouseClick& button)
{
	return	(mouse_->state_.rgbButtons[static_cast<size_t>(button)]) &&
			(elderMouse_->state_.rgbButtons[static_cast<size_t>(button)]) == false;
}
bool Mouse::IsLongPress(const MouseClick& button)
{
	return	(mouse_->state_.rgbButtons[static_cast<size_t>(button)]) &&
			(elderMouse_->state_.rgbButtons[static_cast<size_t>(button)]);
}
bool Mouse::IsRelease(const MouseClick& button)
{
	return	(mouse_->state_.rgbButtons[static_cast<size_t>(button)]) == false &&
			(elderMouse_->state_.rgbButtons[static_cast<size_t>(button)]);
}