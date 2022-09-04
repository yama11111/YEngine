#include "ConstBufferManager.h"
#include "RootParameterManager.h"
#include "Utility/Result.h"

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

void ConstBufferManager::CreateCB(ConstBufferMaterial& cb, const Math::Vec4& color)
{
	ResourceInfo cbInfo = CBInfo();
	cbInfo.resDesc.Width = (sizeof(ConstBufferDataMaterial) * 0xff) & ~0xff;

	// 定数バッファの生成
	cb.mate.Create(cbInfo);

	// 定数バッファのマッピング
	Result::Check(cb.mate.Get()->Map(0, nullptr, (void**)&cb.mapMate));
	// 値を書きこむと自動的に転送される
	cb.mapMate->color = color;
}

void ConstBufferManager::CreateCB(ConstBufferTransform& cb)
{
	ResourceInfo cbInfo = CBInfo();
	cbInfo.resDesc.Width = (sizeof(ConstBufferDataTransform) * 0xff) & ~0xff;

	// 定数バッファの生成
	cb.mate.Create(cbInfo);

	// 定数バッファのマッピング
	Result::Check(cb.mate.Get()->Map(0, nullptr, (void**)&cb.mapTrfm));
	// 値を書きこむと自動的に転送される
	cb.mapTrfm->mat = Math::Mat4::Identity();
}

void ConstBufferManager::SetCommand(ConstBufferMaterial& cb)
{
	// 定数バッファビュー(CBV)の設定コマンド
	pCmdList->SetGraphicsRootConstantBufferView(indexM, cb.mate.Get()->GetGPUVirtualAddress());
}

void ConstBufferManager::SetCommand(ConstBufferTransform& cb)
{
	// 定数バッファビュー(CBV)の設定コマンド
	pCmdList->SetGraphicsRootConstantBufferView(indexT, cb.mate.Get()->GetGPUVirtualAddress());
}
