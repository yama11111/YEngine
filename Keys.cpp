#include "Keys.h"

Keys* Keys::GetInstance()
{
	static Keys instance;
	return &instance;
}

void Keys::Update()
{
	// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
	for (int i = 0; i < 256; i++)
	{
		elderKeys[i] = keys[i];
	}
	// 最新のキーボード情報を取得
	input->GetKeyboardState(keys);
}

bool Keys::IsDown(const int key)
{
	return keys[key];
}
bool Keys::IsTrigger(const int key)
{
	return (keys[key] && !elderKeys[key]);
}
bool Keys::IsLongPress(const int key)
{
	return (keys[key] && elderKeys[key]);
}
bool Keys::IsRelease(const int key)
{
	return (!keys[key] && elderKeys[key]);
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

bool Keys::isMove()
{
	return 	IsDown(DIK_RIGHT) || IsDown(DIK_D) ||
			IsDown(DIK_LEFT)  || IsDown(DIK_A) ||
			IsDown(DIK_DOWN)  || IsDown(DIK_S) ||
			IsDown(DIK_UP)	  || IsDown(DIK_W);
}

Keys::Keys() :
	keys(new unsigned char[256]),
	elderKeys(new unsigned char[256]),
	input(DInput::GetInstance())
{
	for (int i = 0; i < 256; i++)
	{
		keys[i] = 0;
		elderKeys[i] = 0;
	}
}

Keys::~Keys()
{
	delete keys;
	keys = 0;
	delete elderKeys;
	elderKeys = 0;
}