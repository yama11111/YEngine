#include "RenderTargetView.h"
#include "Device.h"
#include "Utility/Result.h"

using DX::RenderTargetView;

void RenderTargetView::Create(IDXGISwapChain4* swapChain, const DXGI_SWAP_CHAIN_DESC1& swapChainDesc)
{
	Device* dev = Device::GetInstance();
	rtv.desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV; // �����_�[�^�[�Q�b�g�r���[
	rtv.desc.NumDescriptors = swapChainDesc.BufferCount; // ���\��2��
	// �f�X�N���v�^�q�[�v����
	rtv.Create();
	backBuffers.resize(swapChainDesc.BufferCount);

	// �X���b�v�`�F�[���̑S�Ẵo�b�t�@�ɂ��ď�������
	for (size_t i = 0; i < backBuffers.size(); i++)
	{
		// �X���b�v�`�F�[������o�b�t�@�擾
		swapChain->GetBuffer((UINT)i, IID_PPV_ARGS(&backBuffers[i]));
		// �f�X�N���v�^�q�[�v�̃n���h���擾
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtv.Get()->GetCPUDescriptorHandleForHeapStart();
		// �����\���ŃA�h���X�������
		rtvHandle.ptr += i * dev->Get()->GetDescriptorHandleIncrementSize(rtv.desc.Type);
		// �����_�[�^�[�Q�b�g�r���[�ݒ�
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
		// �V�F�[�_�[�̌v�Z���ʂ�SRGB�ɕϊ����ď�������
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		// �����_�[�^�[�Q�b�g�r���[����
		dev->Get()->CreateRenderTargetView(backBuffers[i].Get(), &rtvDesc, rtvHandle);
	}
}

DX::Utility::DescriptorHeap RenderTargetView::Get()
{
	return rtv;
}

std::vector<ID3D12Resource*> RenderTargetView::BackBaffers()
{
	std::vector<ID3D12Resource*> result;
	for (size_t i = 0; i < backBuffers.size(); i++)
	{
		result.push_back(backBuffers[i].Get());
	}
	return result;
}

ID3D12Resource* RenderTargetView::BackBaffer(const int index)
{
	if (backBuffers.size() <= index) return backBuffers[0].Get();
	return backBuffers[index].Get();
}
