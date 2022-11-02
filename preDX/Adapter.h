#pragma once
#include <dxgi1_6.h>
#include <wrl.h>

#pragma comment(lib, "dxgi.lib")

namespace DX
{
	class Adapter
	{
	private:
		// ここに特定の名前を持つアダプターオブジェクトが入る
		Microsoft::WRL::ComPtr<IDXGIAdapter4> tmpAdapter = nullptr;
	public:
		void Selection(IDXGIFactory7* dxgiFactory);
		IDXGIAdapter4* Get();
	public:
		static Adapter* GetInstance();
	private:
		Adapter() = default;
		~Adapter() = default;
		Adapter(const Adapter&) = delete;
		const Adapter& operator=(const Adapter&) = delete;
	};
}