#pragma once
#include <d3d12.h>

#pragma comment(lib, "d3d12.lib")

class DXRootSignature
{
public:
	// ���[�g�V�O�l�`��
	ID3D12RootSignature* rootSignature = nullptr;
	// ���[�g�V�O�l�`���̐ݒ�
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
public:
	void Create(ID3DBlob* errorBrob);
};