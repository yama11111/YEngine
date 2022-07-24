#include "DXRenderTargetView.h"
#include "DXDevice.h"
#include "Result.h"

void DXRenderTargetView::Create(IDXGISwapChain4* swapChain, DXGI_SWAP_CHAIN_DESC1 swapChainDesc)
{
	DXDevice* dev = DXDevice::GetInstance();
	rtv.hDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;		// �����_�[�^�[�Q�b�g�r���[
	rtv.hDesc.NumDescriptors = swapChainDesc.BufferCount; // ���\��2��
	// �f�X�N���v�^�q�[�v����
	rtv.Create();
	backBuffers.resize(swapChainDesc.BufferCount);

	// �X���b�v�`�F�[���̑S�Ẵo�b�t�@�ɂ��ď�������
	for (size_t i = 0; i < backBuffers.size(); i++)
	{
		// �X���b�v�`�F�[������o�b�t�@�擾
		swapChain->GetBuffer((UINT)i, IID_PPV_ARGS(&backBuffers[i]));
		// �f�X�N���v�^�q�[�v�̃n���h���擾
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtv.heap->GetCPUDescriptorHandleForHeapStart();
		// �����\���ŃA�h���X�������
		rtvHandle.ptr += i * dev->Device()->GetDescriptorHandleIncrementSize(rtv.hDesc.Type);
		// �����_�[�^�[�Q�b�g�r���[�ݒ�
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
		// �V�F�[�_�[�̌v�Z���ʂ�SRGB�ɕϊ����ď�������
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		// �����_�[�^�[�Q�b�g�r���[����
		dev->Device()->CreateRenderTargetView(backBuffers[i], &rtvDesc, rtvHandle);
	}
}

DXDescriptorHeap DXRenderTargetView::RenderTargetView()
{
	return rtv;
}

std::vector<ID3D12Resource*> DXRenderTargetView::BackBaffers()
{
	return backBuffers;
}

ID3D12Resource* DXRenderTargetView::BackBaffer(const int index)
{
	if (backBuffers.size() <= index) return backBuffers[0];
	return backBuffers[index];
}
