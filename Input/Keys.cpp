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
	// 生成
	for (size_t i = 0; i < 256; i++)
	{
		keys[i] = std::make_unique<unsigned char>();
		elderKeys[i] = std::make_unique<unsigned char>();
	}

	// キーボードデバイス 生成
	DX::Result(directInput->CreateDevice(GUID_SysKeyboard, &keyDevice, NULL));

	// 入力データ形式セット
	DX::Result(keyDevice->SetDataFormat(&c_dfDIKeyboard));

	// 排他制御レベルセット
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
	// 1フレーム前の情報を保存
	for (int i = 0; i < 256; i++)
	{
		*elderKeys[i] = *keys[i];
	}

	// 最新の情報を取得
	keyDevice->Acquire();

	// 入力状態を取得
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