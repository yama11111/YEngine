#pragma once
#include <dxgi1_6.h>
#include <wrl.h>

#pragma comment(lib, "dxgi.lib")

namespace DX
{
	class Adapter
	{
	private:
		// �����ɓ���̖��O�����A�_�v�^�[�I�u�W�F�N�g������
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