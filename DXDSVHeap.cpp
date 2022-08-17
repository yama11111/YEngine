#include "DXDSVHeap.h"
#include "DXDevice.h"
#include "Result.h"
#include "Def.h"

void DXDSVHeap::Create()
{
	DXResourceInfo2 depthInfo{};
	depthInfo.resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthInfo.resDesc.Width = WIN_SIZE.x; // �����_�[�^�[�Q�b�g�ɍ��킹��
	depthInfo.resDesc.Height = WIN_SIZE.y; // �����_�[�^�[�Q�b�g�ɍ��킹��
	depthInfo.resDesc.DepthOrArraySize = 1;
	depthInfo.resDesc.Format = DXGI_FORMAT_D32_FLOAT; // �[�x�l�t�H�[�}�b�g
	depthInfo.resDesc.SampleDesc.Count = 1;
	depthInfo.resDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL; // �f�v�X�X�e���V��

	// �[�x�l�p�q�[�v�v���p�e�B
	depthInfo.heapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
	// �[�x�l�̃N���A�ݒ�
	depthInfo.clearValue.DepthStencil.Depth = 1.0f; // �[�x�l1.0f(�ő�l)�ŃN���A
	depthInfo.clearValue.Format = DXGI_FORMAT_D32_FLOAT; // �[�x�l�t�H�[�}�b�g

	// ���\�[�X����
	depthBuff.Create(depthInfo);

	// �[�x�r���[�p�f�X�N���v�^�[�q�[�v�쐬
	dsvHeap.hDesc.NumDescriptors = 1; // �[�x�r���[��1��
	dsvHeap.hDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV; // �f�v�X�X�e���V���r���[
	dsvHeap.Create();

	// �[�x�r���[�쐬
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT; // �[�x�l�t�H�[�}�b�g
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;

	DXDevice* dev = DXDevice::GetInstance();
	dev->Device()->CreateDepthStencilView(
		depthBuff.buff,
		&dsvDesc,
		dsvHeap.heap->GetCPUDescriptorHandleForHeapStart());
}
