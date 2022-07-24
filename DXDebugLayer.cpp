#include "DXDebugLayer.h"
#include <wrl/client.h>
#include "DXDevice.h"

void DXDebugLayer::Enable(const bool isValidate)
{
#ifdef _DEBUG
	//�f�o�b�O���C���[���I����
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
		if (isValidate) debugController->SetEnableGPUBasedValidation(true);
	}
#endif
}

void DXDebugLayer::Severity()
{
	DXDevice* dev = DXDevice::GetInstance();
#ifdef _DEBUG
	Microsoft::WRL::ComPtr<ID3D12InfoQueue> infoQueue;
	if (SUCCEEDED(dev->Device()->QueryInterface(IID_PPV_ARGS(&infoQueue))))
	{
		// �~�܂�
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true); // ���o���G���[
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true); // �G���[
	}
#endif
}
