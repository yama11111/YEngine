#include "ConstBufferManager.h"
#include "../RootParameterManager.h"
#include "../Utility/Result.h"

using DX::GPUResource::ConstBufferManager;
using DX::Utility::ResourceInfo;
using DX::Utility::Result;

ID3D12GraphicsCommandList* ConstBufferManager::pCmdList = nullptr;

ConstBufferManager* ConstBufferManager::GetInstance()
{
	static ConstBufferManager instance;
	return &instance;
}

void ConstBufferManager::StaticInit(ID3D12GraphicsCommandList* pCommandList)
{
	Result::Assert(pCommandList != nullptr);
	pCmdList = pCommandList;
}

ConstBufferManager::ConstBufferManager()
{
	RootParameterManager* rpM = RootParameterManager::GetInstance();
	indexM = rpM->PushBackCBV();
	indexT = rpM->PushBackCBV();
}

ResourceInfo ConstBufferManager::CBInfo()
{
	ResourceInfo cbInfo{};
	cbInfo.heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
	cbInfo.resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbInfo.resDesc.Height = 1;
	cbInfo.resDesc.DepthOrArraySize = 1;
	cbInfo.resDesc.MipLevels = 1;
	cbInfo.resDesc.SampleDesc.Count = 1;
	cbInfo.resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	return cbInfo;
}

void ConstBufferManager::CreateCB(ConstBufferMaterial& cb, const Vec4& color)
{
	ResourceInfo cbInfo = CBInfo();
	cbInfo.resDesc.Width = (sizeof(ConstBufferDataMaterial) * 0xff) & ~0xff;

	// �萔�o�b�t�@�̐���
	cb.cbMate.Create(cbInfo);

	// �萔�o�b�t�@�̃}�b�s���O
	Result::Check(cb.cbMate.Get()->Map(0, nullptr, (void**)&cb.cMapMate));
	// �l���������ނƎ����I�ɓ]�������
	cb.cMapMate->color = color;
}

void ConstBufferManager::CreateCB(ConstBufferTransform& cb)
{
	ResourceInfo cbInfo = CBInfo();
	cbInfo.resDesc.Width = (sizeof(ConstBufferDataTransform) * 0xff) & ~0xff;

	// �萔�o�b�t�@�̐���
	cb.cbMate.Create(cbInfo);

	// �萔�o�b�t�@�̃}�b�s���O
	Result::Check(cb.cbMate.Get()->Map(0, nullptr, (void**)&cb.cMapTrfm));
	// �l���������ނƎ����I�ɓ]�������
	cb.cMapTrfm->mat = Mat4::Identity();
}

void ConstBufferManager::SetCommand(ConstBufferMaterial& cb)
{
	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	pCmdList->SetGraphicsRootConstantBufferView(indexM, cb.cbMate.Get()->GetGPUVirtualAddress());
}

void ConstBufferManager::SetCommand(ConstBufferTransform& cb)
{
	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	pCmdList->SetGraphicsRootConstantBufferView(indexT, cb.cbMate.Get()->GetGPUVirtualAddress());
}
