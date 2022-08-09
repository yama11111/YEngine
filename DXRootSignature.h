#pragma once
#include <d3d12.h>

#pragma comment(lib, "d3d12.lib")

class DXRootSignature
{
public:
	// ルートシグネチャ
	ID3D12RootSignature* rootSignature = nullptr;
	// ルートシグネチャの設定
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
public:
	void Create(ID3DBlob* errorBrob);
};