#include "ConstBufferManager.h"
#include "YAssert.h"

using DX::ConstBufferManager;

ID3D12GraphicsCommandList* ConstBufferManager::pCmdList_ = nullptr;

void ConstBufferManager::StaticInitialize(ID3D12GraphicsCommandList* pCommandList)
{
	Assert(pCommandList != nullptr);
	pCmdList_ = pCommandList;
}

void ConstBufferManager::CreateCB(ConstBuffer<MaterialData>& cb, const Math::Vec4& color)
{
	// �����p���
	GPUResource::CreateStatus state;
	// �q�[�v�ݒ�
	state.heapProp_.Type = D3D12_HEAP_TYPE_UPLOAD;
	// ���\�[�X�ݒ�
	state.resDesc_.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	state.resDesc_.Height = 1;
	state.resDesc_.Width = (sizeof(MaterialData) * 0xff) & ~0xff;
	state.resDesc_.DepthOrArraySize = 1;
	state.resDesc_.MipLevels = 1;
	state.resDesc_.SampleDesc.Count = 1;
	state.resDesc_.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// �萔�o�b�t�@�̐���
	cb.rsc_.Create(state);

	// �萔�o�b�t�@�̃}�b�s���O
	Result(cb.rsc_.Get()->Map(0, nullptr, (void**)&cb.map_));
	// �l���������ނƎ����I�ɓ]�������
	cb.map_->color_ = color;
}

void ConstBufferManager::CreateCB(ConstBuffer<TransformData>& cb)
{
	GPUResource::CreateStatus state;
	// �q�[�v�ݒ�
	state.heapProp_.Type = D3D12_HEAP_TYPE_UPLOAD;
	// ���\�[�X�ݒ�
	state.resDesc_.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	state.resDesc_.Height = 1;
	state.resDesc_.Width = (sizeof(TransformData) * 0xff) & ~0xff;
	state.resDesc_.DepthOrArraySize = 1;
	state.resDesc_.MipLevels = 1;
	state.resDesc_.SampleDesc.Count = 1;
	state.resDesc_.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// �萔�o�b�t�@�̐���
	cb.rsc_.Create(state);

	// �萔�o�b�t�@�̃}�b�s���O
	Result(cb.rsc_.Get()->Map(0, nullptr, (void**)&cb.map_));
	// �l���������ނƎ����I�ɓ]�������
	cb.map_->mat_ = Math::Mat4::Identity();
}

void ConstBufferManager::SetDrawCommand(ConstBuffer<MaterialData>& cb)
{
	// �萔�o�b�t�@�r���[(�}�e���A��)�̐ݒ�R�}���h
	pCmdList_->SetGraphicsRootConstantBufferView(rpIndexM_, cb.rsc_.Get()->GetGPUVirtualAddress());
}

void ConstBufferManager::SetDrawCommand(ConstBuffer<TransformData>& cb)
{
	// �萔�o�b�t�@�r���[(3D�ϊ��s��)�̐ݒ�R�}���h
	pCmdList_->SetGraphicsRootConstantBufferView(rpIndexT_, cb.rsc_.Get()->GetGPUVirtualAddress());
}