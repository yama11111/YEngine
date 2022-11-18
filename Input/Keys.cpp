#include "Keys.h"
#include "YAssert.h"

using Input::Keys;

Keys* Keys::GetInstance()
{
	static Keys instance;
	return &instance;
}

void Keys::Create(const HWND hwnd, IDirectInput8* directInput)
{
	// ����
	for (size_t i = 0; i < 256; i++)
	{
		keys_[i] = std::make_unique<unsigned char>();
		elderKeys_[i] = std::make_unique<unsigned char>();
	}

	// �L�[�{�[�h�f�o�C�X ����
	DX::Result(directInput->CreateDevice(GUID_SysKeyboard, &device_, NULL));

	// ���̓f�[�^�`���Z�b�g
	DX::Result(device_->SetDataFormat(&c_dfDIKeyboard));

	// �r�����䃌�x���Z�b�g
	DX::Result(device_->SetCooperativeLevel(
		hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY));

	Initialize();
}

void Keys::Initialize()
{
	for (int i = 0; i < 256; i++)
	{
		*keys_[i] = *elderKeys_[i] = 0;
	}
}

void Keys::Update()
{
	// 1�t���[���O�̏���ۑ�
	for (int i = 0; i < 256; i++) { *elderKeys_[i] = *keys_[i]; }

	// �ŐV�̏����擾
	device_->Acquire();

	// ���͏�Ԃ��擾
	BYTE key[256];
	device_->GetDeviceState(sizeof(key), key);

	for (int i = 0; i < 256; i++) { *keys_[i] = key[i]; }
}

bool Keys::IsDown(const int key)
{
	return *keys_[key];
}
bool Keys::IsTrigger(const int key)
{
	return (*keys_[key] && !*elderKeys_[key]);
}
bool Keys::IsLongPress(const int key)
{
	return (*keys_[key] && *elderKeys_[key]);
}
bool Keys::IsRelease(const int key)
{
	return (!*keys_[key] && *elderKeys_[key]);
}

bool Keys::IsLeft(const MoveStandard& keyS)
{
	return	(keyS == MoveStandard::Arrow && IsDown(DIK_LEFT)) ||
		(keyS == MoveStandard::WASD && IsDown(DIK_A));
}
bool Keys::IsRight(const MoveStandard& keyS)
{
	return	(keyS == MoveStandard::Arrow && IsDown(DIK_RIGHT)) ||
		(keyS == MoveStandard::WASD && IsDown(DIK_D));
}
bool Keys::IsUp(const MoveStandard& keyS)
{
	return	(keyS == MoveStandard::Arrow && IsDown(DIK_UP)) ||
		(keyS == MoveStandard::WASD && IsDown(DIK_W));
}
bool Keys::IsUnder(const MoveStandard& keyS)
{
	return	(keyS == MoveStandard::Arrow && IsDown(DIK_DOWN)) ||
		(keyS == MoveStandard::WASD && IsDown(DIK_S));
}

int Keys::Horizontal(const MoveStandard& keyS)
{
	return IsRight(keyS) - IsLeft(keyS);
}
int Keys::Vertical(const MoveStandard& keyS)
{
	return IsUnder(keyS) - IsUp(keyS);
}
bool Keys::IsMove(const MoveStandard& keyS)
{
	return IsRight(keyS) || IsLeft(keyS) || IsUp(keyS) || IsUnder(keyS);
}