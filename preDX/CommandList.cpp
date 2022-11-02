#include "CommandList.h"
#include "Device.h"
#include "Utility/Result.h"

using DX::CommandList;
using DX::Utility::Result;

void CommandList::Create()
{
	Device* dev = Device::GetInstance();
	
	// �R�}���h�A���P�[�^�𐶐�
	Result::Check(dev->Get()->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(&allocator)));
	// �R�}���h���X�g�𐶐�
	Result::Check(dev->Get()->CreateCommandList(0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		allocator.Get(), nullptr,
		IID_PPV_ARGS(&list)));
}

void CommandList::Reset()
{
	// �L���[���N���A
	Result::Check(allocator->Reset());
	// �ĂуR�}���h���X�g�𒙂߂鏀��
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