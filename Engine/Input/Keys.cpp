#include "Keys.h"
#include "YAssert.h"

using YInput::Keys;

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
		keys_[i] = std::make_unique<unsigned char>();
		elderKeys_[i] = std::make_unique<unsigned char>();
	}

	// キーボードデバイス 生成
	YDX::Result(directInput->CreateDevice(GUID_SysKeyboard, &device_, NULL));

	// 入力データ形式セット
	YDX::Result(device_->SetDataFormat(&c_dfDIKeyboard));

	// 排他制御レベルセット
	YDX::Result(device_->SetCooperativeLevel(
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
	// 1フレーム前の情報を保存
	for (int i = 0; i < 256; i++) { *elderKeys_[i] = *keys_[i]; }

	// 最新の情報を取得
	device_->Acquire();

	// 入力状態を取得
	BYTE key[256] = {};
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
			(keyS == MoveStandard::WASD && IsDown(DIK_A)) ||
			(keyS == MoveStandard::All && (IsDown(DIK_LEFT) || IsDown(DIK_A)));
}
bool Keys::IsRight(const MoveStandard& keyS)
{
	return	(keyS == MoveStandard::Arrow && IsDown(DIK_RIGHT)) ||
			(keyS == MoveStandard::WASD && IsDown(DIK_D)) ||
			(keyS == MoveStandard::All && (IsDown(DIK_RIGHT) || IsDown(DIK_D)));
}
bool Keys::IsUp(const MoveStandard& keyS)
{
	return	(keyS == MoveStandard::Arrow && IsDown(DIK_UP)) ||
			(keyS == MoveStandard::WASD && IsDown(DIK_W)) ||
			(keyS == MoveStandard::All && (IsDown(DIK_UP) || IsDown(DIK_W)));
}
bool Keys::IsUnder(const MoveStandard& keyS)
{
	return	(keyS == MoveStandard::Arrow && IsDown(DIK_DOWN)) ||
			(keyS == MoveStandard::WASD && IsDown(DIK_S)) ||
			(keyS == MoveStandard::All && (IsDown(DIK_DOWN) || IsDown(DIK_S)));
}

int Keys::Horizontal(const MoveStandard& keyS)
{
	return IsRight(keyS) - IsLeft(keyS);
}
int Keys::Vertical(const MoveStandard& keyS)
{
	return IsUp(keyS) - IsUnder(keyS);
}
bool Keys::IsMove(const MoveStandard& keyS)
{
	return IsRight(keyS) || IsLeft(keyS) || IsUp(keyS) || IsUnder(keyS);
}