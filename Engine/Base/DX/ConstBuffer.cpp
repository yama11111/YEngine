#include "ConstBuffer.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Model.h"
#include "PostEffect.h"
#include "CBColor.h"
#include "CBLightGroup.h"
#include "CBMaterial.h"
#include "CBTexConfig.h"
#include "PostEffect.h"
#include "YAssert.h"

using YDX::ConstBufferCommon;
using YDX::ConstBuffer;

ID3D12GraphicsCommandList* ConstBufferCommon::spCmdList_ = nullptr;
YDX::DescriptorHeap* ConstBufferCommon::spDescHeap_ = nullptr;

void ConstBufferCommon::StaticInitialize(ID3D12GraphicsCommandList* pCmdList, DescriptorHeap* pDescHeap)
{
	assert(pCmdList);
	assert(pDescHeap);

	spCmdList_ = pCmdList;
	spDescHeap_ = pDescHeap;
}

template<typename T>
void ConstBuffer<T>::Create(const bool isMutable)
{
	// �q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;

	// ���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Height = 1;
	resDesc.Width = (sizeof(T) * 0xff) & ~0xff;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// �萔�o�b�t�@�̐���
	buff_.Create(&heapProp, &resDesc);

	// �萔�o�b�t�@�̃}�b�s���O
	Result(buff_.Get()->Map(0, nullptr, (void**)&map_));

	// CBV����
	viewDesc_.BufferLocation = buff_.Get()->GetGPUVirtualAddress();
	viewDesc_.SizeInBytes = static_cast<UINT>(resDesc.Width);
	spDescHeap_->CreateCBV(viewDesc_, isMutable);
}

template<typename T>
void ConstBuffer<T>::SetDrawCommand(const UINT rootParamIndex)
{
	// �萔�o�b�t�@�r���[(3D�ϊ��s��)�̐ݒ�R�}���h
	spCmdList_->SetGraphicsRootConstantBufferView(rootParamIndex, viewDesc_.BufferLocation);
}

template class ConstBuffer<YGame::Sprite2D::Object::CBData>;
template class ConstBuffer<YGame::Sprite3D::Object::CBData>;
template class ConstBuffer<YGame::Model::Object::CBData>;
template class ConstBuffer<YGame::PostEffect::Object::CBData>;
template class ConstBuffer<YGame::CBColor::CBData>;
template class ConstBuffer<YGame::CBMaterial::CBData>;
template class ConstBuffer<YGame::CBLightGroup::CBData>;
template class ConstBuffer<YGame::CBTexConfig::CBData>;
