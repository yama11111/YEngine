#include "CommandList.h"
#include "Device.h"
#include "Utility/Result.h"

using DX::CommandList;
using DX::Utility::Result;

void CommandList::Create()
{
	Device* dev = Device::GetInstance();
	
	// コマンドアロケータを生成
	Result::Check(dev->Get()->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(&allocator)));
	// コマンドリストを生成
	Result::Check(dev->Get()->CreateCommandList(0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		allocator.Get(), nullptr,
		IID_PPV_ARGS(&list)));
}

void CommandList::Reset()
{
	// キューをクリア
	Result::Check(allocator->Reset());
	// 再びコマンドリストを貯める準備
	Result::Check(list->Reset(allocator.Get(), nullptr));
}

ID3D12GraphicsCommandList* CommandList::Get()
{
	return list.Get();
}

ID3D12CommandAllocator* CommandList::GetAllocator()
{
	return allocator.Get();
}