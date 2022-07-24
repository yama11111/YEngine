#include "DXCommandList.h"
#include "DXDevice.h"
#include "Result.h"
#include "Def.h"

void DXCommandList::Create()
{
	DXDevice* dev = DXDevice::GetInstance();

	// コマンドアロケータを生成
	Result::Check(dev->Device()->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(&commandAllocator)));
	// コマンドリストを生成
	Result::Check(dev->Device()->CreateCommandList(0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		commandAllocator, nullptr,
		IID_PPV_ARGS(&commandList)));
}

void DXCommandList::ClearAndPrepare()
{
	// キューをクリア
	Result::Check(commandAllocator->Reset());
	// 再びコマンドリストを貯める準備
	Result::Check(commandList->Reset(commandAllocator, nullptr));
}

void DXCommandList::CrearRTV(D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle)
{
	FLOAT clearColor[] = { CLEAR_COLOR.r, CLEAR_COLOR.g, CLEAR_COLOR.b, CLEAR_COLOR.a };
	commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
}

ID3D12GraphicsCommandList* DXCommandList::List()
{
	return commandList;
}

ID3D12CommandAllocator* DXCommandList::Allocator()
{
	return commandAllocator;
}

DXCommandList* DXCommandList::GetInstance()
{
	static DXCommandList instance;
	return &instance;
}
