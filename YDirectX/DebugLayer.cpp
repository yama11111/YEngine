#include "DebugLayer.h"
#include "Device.h"
#include <wrl/client.h>

using DX::DebugLayer;

void DebugLayer::Enable(const bool isValidate)
{
#ifdef _DEBUG
	Microsoft::WRL::ComPtr<ID3D12Debug1> debugController;
	//デバッグレイヤーをオンに
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
		if (isValidate) debugController->SetEnableGPUBasedValidation(true);
	}
#endif
}

void DebugLayer::Severity()
{
#ifdef _DEBUG
	Device* dev = Device::GetInstance();
	Microsoft::WRL::ComPtr<ID3D12InfoQueue> infoQueue;
	if (SUCCEEDED(dev->Get()->QueryInterface(IID_PPV_ARGS(&infoQueue))))
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
