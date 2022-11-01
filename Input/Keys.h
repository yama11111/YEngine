#pragma once
#include <dinput.h>
#include <memory>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

namespace Input
{
	class Keys
	{
	private:
		// �f�o�C�X
		IDirectInputDevice8* keyDevice = nullptr;
		// �ŐV
		std::unique_ptr<unsigned char> keys[256];
		// 1F�O
		std::unique_ptr<unsigned char> elderKeys[256];
	public:
		// ���� (�ŏ���1��Ă�)
		void Create(const HWND hwnd, IDirectInput8* directInput);
		// ���͏�� ������
		void Initialize();
		// �X�V����
		void Update();
	public:
		// �����Ă���
		bool IsDown(const int key);
		// �������u��
		bool IsTrigger(const int key);
		// ���������Ă���
		bool IsLongPress(const int key);
		// �������u��
		bool IsRelease(const int key);
	public:
		// ��(-1) �E(+1)
		int Horizontal();
		// ��(-1) ��(+1)
		int Vertical();
		// ��
		bool IsLeft();
		// �E
		bool IsRight();
		// ��
		bool IsUp();
		// ��
		bool IsUnder();
		// �ړ����Ă��邩
		bool IsMove();
	public:
		static Keys* GetInstance();
	private:
		Keys() = default;
		~Keys() = default;
		Keys(const Keys&) = delete;
		const Keys& operator=(const Keys&) = delete;
	};
}