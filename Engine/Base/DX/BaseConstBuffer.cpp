#include "BaseConstBuffer.h"
#include "YAssert.h"

using YGame::ConstBufferCommon;
using YGame::BaseConstBuffer;

ID3D12GraphicsCommandList* ConstBufferCommon::spCmdList_ = nullptr;
YDX::DescriptorHeap* ConstBufferCommon::spDescHeap_ = nullptr;

void ConstBufferCommon::StaticInitialize(ID3D12GraphicsCommandList* pCmdList, YDX::DescriptorHeap* pDescHeap)
{
	assert(pCmdList);
	assert(pDescHeap);

	spCmdList_ = pCmdList;
	spDescHeap_ = pDescHeap;
}

void BaseConstBuffer::CreateBuffer(const size_t dataSize, void** map, const bool isClearWhenTransition)
{
	// �q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;

	// ���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Height = 1;
	resDesc.Width = (dataSize * 0xff) & ~0xff;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// �萔�o�b�t�@�̐���
	buff_.Create(&heapProp, &resDesc);

	// �萔�o�b�t�@�̃}�b�s���O
	YDX::Result(buff_.Get()->Map(0, nullptr, map));

	// CBV����
	viewDesc_.BufferLocation = buff_.Get()->GetGPUVirtualAddress();
	viewDesc_.SizeInBytes = static_cast<UINT>(resDesc.Width);
	spDescHeap_->CreateCBV(viewDesc_, isClearWhenTransition);
}

void BaseConstBuffer::SetDrawCommand(const uint32_t rootParamIndex)
{
	// �萔�o�b�t�@�r���[�ݒ�R�}���h
	spCmdList_->SetGraphicsRootConstantBufferView(static_cast<UINT>(rootParamIndex), viewDesc_.BufferLocation);
}
