#include "RootSignature.h"
#include "Device.h"
#include "RootParameterManager.h"
#include "SampleDescManager.h"
#include "Utility/Result.h"

using DX::RootSignature;

void RootSignature::Create(ID3DBlob* errorBlob)
{
	Device* dev = Device::GetInstance();
	RootParameterManager* rootParams = RootParameterManager::GetInstance();
	SampleDescManager* sampleDesc = SampleDescManager::GetInstance();

	// ルートシグネチャの設定
	desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	desc.pParameters = rootParams->rp.data(); // ルートパラメータの先頭アドレス
	desc.NumParameters = (UINT)rootParams->rp.size();// ルートパラメータ数
	desc.pStaticSamplers = sampleDesc->sd.data();
	desc.NumStaticSamplers = (UINT)sampleDesc->sd.size();

	// ルートシグネチャのシリアライズ
	ID3DBlob* rootSigBlob = nullptr; // ルートシグネチャオブジェクト
	Utility::Result::Check(D3D12SerializeRootSignature(&desc, D3D_ROOT_SIGNATURE_VERSION_1_0,
		&rootSigBlob, &errorBlob));
	Utility::Result::Check(dev->Get()->
		CreateRootSignature(0,
			rootSigBlob->GetBufferPointer(),
			rootSigBlob->GetBufferSize(),
			IID_PPV_ARGS(&rootSignature)));
}

ID3D12RootSignature* DX::RootSignature::Get()
{
	return rootSignature.Get();
}
