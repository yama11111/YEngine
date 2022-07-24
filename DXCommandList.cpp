#include "DXCommandList.h"
#include "DXDevice.h"
#include "Result.h"
#include "Def.h"

void DXCommandList::Create()
{
	DXDevice* dev = DXDevice::GetInstance();

	// �R�}���h�A���P�[�^�𐶐�
	Result::Check(dev->Device()->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(&commandAllocator)));
	// �R�}���h���X�g�𐶐�
	Result::Check(dev->Device()->CreateCommandList(0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		commandAllocator, nullptr,
		IID_PPV_ARGS(&commandList)));
}

void DXCommandList::ClearAndPrepare()
{
	// �L���[���N���A
	Result::Check(commandAllocator->Reset());
	// �ĂуR�}���h���X�g�𒙂߂鏀��
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
