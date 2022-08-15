#include "ConstBufferManager.h"
#include "DXRootParameterManager.h"
#include "Result.h"

ConstBufferManager::ConstBufferManager()
{
	DXRootParameterManager* rpM = DXRootParameterManager::GetInstance();
	indexM = rpM->PushBackCBV();
	indexT = rpM->PushBackCBV();
	cmdList = DXCommandList::GetInstance();
}

void ConstBufferManager::CreateCB(ConstBufferMaterial& cb, const Vec4& color)
{
	DXResourceInfo cbInfo{};
	cbInfo.heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
	cbInfo.resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbInfo.resDesc.Width = (sizeof(ConstBufferDataMaterial) * 0xff) & ~0xff;
	cbInfo.resDesc.Height = 1;
	cbInfo.resDesc.DepthOrArraySize = 1;
	cbInfo.resDesc.MipLevels = 1;
	cbInfo.resDesc.SampleDesc.Count = 1;
	cbInfo.resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	// �萔�o�b�t�@�̐���
	cb.cbMate.Create(cbInfo);

	// �萔�o�b�t�@�̃}�b�s���O
	Result::Check(cb.cbMate.buff->Map(0, nullptr, (void**)&cb.cMapMate));
	// �l���������ނƎ����I�ɓ]�������
	cb.cMapMate->color = color;
}

void ConstBufferManager::CreateCB(ConstBufferTransform& cb)
{
	DXResourceInfo cbInfo{};
	cbInfo.heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
	cbInfo.resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbInfo.resDesc.Width = (sizeof(ConstBufferDataTransform) * 0xff) & ~0xff;
	cbInfo.resDesc.Height = 1;
	cbInfo.resDesc.DepthOrArraySize = 1;
	cbInfo.resDesc.MipLevels = 1;
	cbInfo.resDesc.SampleDesc.Count = 1;
	cbInfo.resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	// �萔�o�b�t�@�̐���
	cb.cbMate.Create(cbInfo);

	// �萔�o�b�t�@�̃}�b�s���O
	Result::Check(cb.cbMate.buff->Map(0, nullptr, (void**)&cb.cMapTrfm));
	// �l���������ނƎ����I�ɓ]�������
	cb.cMapTrfm->mat = Mat4::Identity();
}

void ConstBufferManager::SetCommand(ConstBufferMaterial& cb)
{
	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	cmdList->List()->
		SetGraphicsRootConstantBufferView(indexM, cb.cbMate.buff->GetGPUVirtualAddress());
}

void ConstBufferManager::SetCommand(ConstBufferTransform& cb)
{
	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	cmdList->List()->
		SetGraphicsRootConstantBufferView(indexT, cb.cbMate.buff->GetGPUVirtualAddress());
}

ConstBufferManager* ConstBufferManager::GetInstance()
{
	static ConstBufferManager instance;
	return &instance;
}
