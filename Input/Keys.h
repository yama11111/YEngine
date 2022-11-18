#pragma once
#include <dinput.h>
#include <wrl.h>
#include <memory>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

namespace Input
{
	class Keys
	{
	private:
		// デバイス
		Microsoft::WRL::ComPtr<IDirectInputDevice8> device_ = nullptr;
		// 最新
		std::unique_ptr<unsigned char> keys_[256];
		// 1F前
		std::unique_ptr<unsigned char> elderKeys_[256];
	public:
		// 生成 (最初に1回呼ぶ)
		void Create(const HWND hwnd, IDirectInput8* directInput);
		// 入力情報 初期化
		void Initialize();
		// 更新処理
		void Update();
	public:
		// 押している
		bool IsDown(const int key);
		// 押した瞬間
		bool IsTrigger(const int key);
		// 押し続けている
		bool IsLongPress(const int key);
		// 離した瞬間
		bool IsRelease(const int key);
	public:
		// 移動キー基準
		enum class MoveStandard
		{
			WASD,
			Arrow,
		};
	public:
		// 左
		bool IsLeft(const MoveStandard& keyS);
		// 右
		bool IsRight(const MoveStandard& keyS);
		// 上
		bool IsUp(const MoveStandard& keyS);
		// 下
		bool IsUnder(const MoveStandard& keyS);
		// 左(-1) 右(+1)
		int Horizontal(const MoveStandard& keyS);
		// 上(-1) 下(+1)
		int Vertical(const MoveStandard& keyS);
		// 移動しているか
		bool IsMove(const MoveStandard& keyS);
	public:
		static Keys* GetInstance();
	private:
		Keys() = default;
		~Keys() = default;
		Keys(const Keys&) = delete;
		const Keys& operator=(const Keys&) = delete;
	};
}