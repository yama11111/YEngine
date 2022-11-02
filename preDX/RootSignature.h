#pragma once
#include <d3d12.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")

namespace DX
{
	class RootSignature
	{
	public:
		// ���[�g�V�O�l�`���̐ݒ�
		D3D12_ROOT_SIGNATURE_DESC desc{};
	private:
		// ���[�g�V�O�l�`��
		Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature = nullptr;
	public:
		void Create(ID3DBlob* errorBrob);
		ID3D12RootSignature* Get();
	};
}