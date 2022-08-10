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

	// ���[�g�V�O�l�`���̐ݒ�
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rootSignatureDesc.pParameters = rootParams->rp.data(); // ���[�g�p�����[�^�̐擪�A�h���X
	rootSignatureDesc.NumParameters = rootParams->rp.size();// ���[�g�p�����[�^��
	//rootSignatureDesc.pStaticSamplers = sampleDesc->sd.data();
	//rootSignatureDesc.NumStaticSamplers = sampleDesc->sd.size();

	// ���[�g�V�O�l�`���̃V���A���C�Y
	ID3DBlob* rootSigBlob = nullptr; // ���[�g�V�O�l�`���I�u�W�F�N�g
	Result::Check(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0,
		&rootSigBlob, &errorBlob));
	Result::Check(dev->Device()->
		CreateRootSignature(0,
			rootSigBlob->GetBufferPointer(),
			rootSigBlob->GetBufferSize(),
			IID_PPV_ARGS(&rootSignature)));
	rootSigBlob->Release();
}
