#include "ConstBuffer.h"
#include "YAssert.h"

using DX::ConstBuffer;

template<typename T>
ID3D12GraphicsCommandList* ConstBuffer<T>::pCmdList_ = nullptr;
template<typename T>
UINT ConstBuffer<T>::rpIndex_ = 0;

template<typename T>
void ConstBuffer<T>::StaticInitialize(ID3D12GraphicsCommandList* pCommandList)
{
	assert(pCommandList);
	pCmdList_ = pCommandList;
}

template<typename T>
void ConstBuffer<T>::Create()
{
	GPUResource::CreateStatus state;
	// �q�[�v�ݒ�
	state.heapProp_.Type = D3D12_HEAP_TYPE_UPLOAD;
	// ���\�[�X�ݒ�
	state.resDesc_.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	state.resDesc_.Height = 1;
	state.resDesc_.Width = (sizeof(T) * 0xff) & ~0xff;
	state.resDesc_.DepthOrArraySize = 1;
	state.resDesc_.MipLevels = 1;
	state.resDesc_.SampleDesc.Count = 1;
	state.resDesc_.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// �萔�o�b�t�@�̐���
	rsc_.Create(state);

	// �萔�o�b�t�@�̃}�b�s���O
	Result(rsc_.Get()->Map(0, nullptr, (void**)&map_));
}

template<typename T>
void ConstBuffer<T>::SetDrawCommand()
{
	// �萔�o�b�t�@�r���[(3D�ϊ��s��)�̐ݒ�R�}���h
	pCmdList_->SetGraphicsRootConstantBufferView(rpIndex_, rsc_.Get()->GetGPUVirtualAddress());
}

template class ConstBuffer<DX::TransformCBData>;
template class ConstBuffer<DX::ColorCBData>;
template class ConstBuffer<DX::MaterialCBData>;