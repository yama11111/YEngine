#include "DepthStencilView.h"
#include "Device.h"
#include "Utility/Result.h"
#include "Def.h"

using DX::DepthStencilView;

void DepthStencilView::Create()
{
	Utility::ResourceInfo2 depthInfo{};
	depthInfo.resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthInfo.resDesc.Width = (UINT16)WIN_SIZE.x; // �����_�[�^�[�Q�b�g�ɍ��킹��
	depthInfo.resDesc.Height = (UINT)WIN_SIZE.y; // �����_�[�^�[�Q�b�g�ɍ��킹��
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
	buff.Create(depthInfo);

	// �[�x�r���[�p�f�X�N���v�^�[�q�[�v�쐬
	dsv.desc.NumDescriptors = 1; // �[�x�r���[��1��
	dsv.desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV; // �f�v�X�X�e���V���r���[
	dsv.Create();

	// �[�x�r���[�쐬
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT; // �[�x�l�t�H�[�}�b�g
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;

	Device* dev = Device::GetInstance();
	dev->Get()->CreateDepthStencilView(
		buff.Get(),
		&dsvDesc,
		dsv.Get()->GetCPUDescriptorHandleForHeapStart());
}

DX::Utility::DescriptorHeap DepthStencilView::Get()
{
	return dsv;
}
