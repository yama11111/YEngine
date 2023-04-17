#include "ConstBuffer.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Model.h"
#include "Material.h"
#include "LightGroup.h"
#include "Color.h"
#include "YAssert.h"

using YDX::ConstBufferCommon;

ID3D12GraphicsCommandList* ConstBufferCommon::pCmdList_ = nullptr;
YDX::DescriptorHeap* ConstBufferCommon::pDescHeap_ = nullptr;

void ConstBufferCommon::StaticInitialize(ID3D12GraphicsCommandList* pCmdList, DescriptorHeap* pDescHeap)
{
	assert(pCmdList);
	assert(pDescHeap);

	pCmdList_ = pCmdList;
	pDescHeap_ = pDescHeap;
}

using YDX::ConstBuffer;

template<typename T>
void ConstBuffer<T>::Create(const bool isMutable)
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

	// CBV����
	viewDesc_.BufferLocation = rsc_.Get()->GetGPUVirtualAddress();
	viewDesc_.SizeInBytes = static_cast<UINT>(state.resDesc_.Width);
	pDescHeap_->CreateCBV(viewDesc_, isMutable);
}

template<typename T>
void ConstBuffer<T>::SetDrawCommand(const UINT rootParamIndex)
{
	// �萔�o�b�t�@�r���[(3D�ϊ��s��)�̐ݒ�R�}���h
	pCmdList_->SetGraphicsRootConstantBufferView(rootParamIndex, viewDesc_.BufferLocation);
}

template class ConstBuffer<YGame::Sprite2DObject::CBData>;
template class ConstBuffer<YGame::Sprite3DObject::CBData>;
template class ConstBuffer<YGame::ModelObject::CBData>;
template class ConstBuffer<YGame::Material::CBData>;
template class ConstBuffer<YGame::Color::CBData>;
template class ConstBuffer<YGame::LightGroup::CBData>;
