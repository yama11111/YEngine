#include "DXDebugLayer.h"
#include <wrl/client.h>
#include "DXDevice.h"

void DXDebugLayer::Enable(const bool isValidate)
{
#ifdef _DEBUG
	ID3D12Debug1* debugController = nullptr;
	//デバッグレイヤーをオンに
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
		if (isValidate) debugController->SetEnableGPUBasedValidation(true);
	}
#endif
}

void DXDebugLayer::Severity()
{
#ifdef _DEBUG
	DXDevice* dev = DXDevice::GetInstance();
	Microsoft::WRL::ComPtr<ID3D12InfoQueue> infoQueue;
	if (SUCCEEDED(dev->Device()->QueryInterface(IID_PPV_ARGS(&infoQueue))))
	{
		// 止まる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true); // ヤバいエラー
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true); // エラー
	}
	D3D12_MESSAGE_ID denyIds[] = {
		D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE
	};
	D3D12_MESSAGE_SEVERITY severities[] = { D3D12_MESSAGE_SEVERITY_INFO };
	D3D12_INFO_QUEUE_FILTER filter{};
	filter.DenyList.NumIDs = _countof(denyIds);
	filter.DenyList.pIDList = denyIds;
	filter.DenyList.NumSeverities = _countof(severities);
	filter.DenyList.pSeverityList = severities;
	infoQueue->PushStorageFilter(&filter);
#endif
}
