#include "DXRootSignature.h"
#include "DXDevice.h"
#include "DXRootParameterManager.h"
//#include "DXSampleDescManager.h"
#include "Result.h"

void DXRootSignature::Create(ID3DBlob* errorBlob)
{
	DXDevice* dev = DXDevice::GetInstance();
	DXRootParameterManager* rootParams = DXRootParameterManager::GetInstance();
	//DXSampleDescManager* sampleDesc = DXSampleDescManager::GetInstance();

	// ルートシグネチャの設定
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rootSignatureDesc.pParameters = rootParams->rp.data(); // ルートパラメータの先頭アドレス
	rootSignatureDesc.NumParameters = rootParams->rp.size();// ルートパラメータ数
	//rootSignatureDesc.pStaticSamplers = sampleDesc->sd.data();
	//rootSignatureDesc.NumStaticSamplers = sampleDesc->sd.size();

	// ルートシグネチャのシリアライズ
	ID3DBlob* rootSigBlob = nullptr; // ルートシグネチャオブジェクト
	Result::Check(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0,
		&rootSigBlob, &errorBlob));
	Result::Check(dev->Device()->
		CreateRootSignature(0,
			rootSigBlob->GetBufferPointer(),
			rootSigBlob->GetBufferSize(),
			IID_PPV_ARGS(&rootSignature)));
	rootSigBlob->Release();
}
