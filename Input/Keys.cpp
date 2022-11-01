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
		keys[i] = std::make_unique<unsigned char>();
		elderKeys[i] = std::make_unique<unsigned char>();
	}

	// �L�[�{�[�h�f�o�C�X ����
	DX::Result(directInput->CreateDevice(GUID_SysKeyboard, &keyDevice, NULL));

	// ���̓f�[�^�`���Z�b�g
	DX::Result(keyDevice->SetDataFormat(&c_dfDIKeyboard));

	// �r�����䃌�x���Z�b�g
	DX::Result(keyDevice->SetCooperativeLevel(
		hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY));

	Initialize();
}

void Keys::Initialize()
{
	for (int i = 0; i < 256; i++)
	{
		*keys[i] = 0;
		*elderKeys[i] = 0;
	}
}

void Keys::Update()
{
	// 1�t���[���O�̏���ۑ�
	for (int i = 0; i < 256; i++)
	{
		*elderKeys[i] = *keys[i];
	}

	// �ŐV�̏����擾
	keyDevice->Acquire();

	// ���͏�Ԃ��擾
	BYTE key[256];
	keyDevice->GetDeviceState(sizeof(key), key);

	for (int i = 0; i < 256; i++)
	{
		*keys[i] = key[i];
	}
}

bool Keys::IsDown(const int key)
{
	return *keys[key];
}
bool Keys::IsTrigger(const int key)
{
	return (*keys[key] && !*elderKeys[key]);
}
bool Keys::IsLongPress(const int key)
{
	return (*keys[key] && *elderKeys[key]);
}
bool Keys::IsRelease(const int key)
{
	return (!*keys[key] && *elderKeys[key]);
}
int Keys::Horizontal()
{
	bool right = IsDown(DIK_RIGHT) || IsDown(DIK_D);
	bool left = IsDown(DIK_LEFT) || IsDown(DIK_A);
	return right - left;
}
int Keys::Vertical()
{
	bool up = IsDown(DIK_DOWN) || IsDown(DIK_S);
	bool down = IsDown(DIK_UP) || IsDown(DIK_W);
	return down - up;
}

bool Keys::IsLeft()
{
	return IsDown(DIK_LEFT) || IsDown(DIK_A);
}

bool Keys::IsRight()
{
	return IsDown(DIK_RIGHT) || IsDown(DIK_D);
}

bool Keys::IsUp()
{
	return IsDown(DIK_UP) || IsDown(DIK_W);
}

bool Keys::IsUnder()
{
	return IsDown(DIK_DOWN) || IsDown(DIK_S);
}

bool Keys::IsMove()
{
	return 	IsRight() || IsLeft() ||
			IsUp() || IsUnder();
}