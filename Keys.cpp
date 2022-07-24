#include "Keys.h"
#include "DInput.h"

Keys* Keys::GetInstance()
{
	static Keys instance;
	return &instance;
}

void Keys::Update()
{
	// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
	for (int i = 0; i < 256; i++)
	{
		elderkeys[i] = keys[i];
	}
	// �ŐV�̃L�[�{�[�h�����擾
	DInput::GetInstance()->GetKeyboardState(keys);
}

bool Keys::IsDown(const int key)
{
	return keys[key];
}
bool Keys::IsTrigger(const int key)
{
	return (keys[key] && !elderkeys[key]);
}
bool Keys::IsLongPress(const int key)
{
	return (keys[key] && elderkeys[key]);
}
bool Keys::IsRelease(const int key)
{
	return (!keys[key] && elderkeys[key]);
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

Keys::Keys() :
	keys(new unsigned char[256]),
	elderkeys(new unsigned char[256])
{
	for (int i = 0; i < 256; i++)
	{
		keys[i] = 0;
		elderkeys[i] = 0;
	}
}

Keys::~Keys()
{
	delete keys;
	keys = 0;
	delete elderkeys;
	elderkeys = 0;
}