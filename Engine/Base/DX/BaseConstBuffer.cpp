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
	// ヒープ設定
	D3D12_HEAP_PROPERTIES heapProp{};
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;

	// リソース設定
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Height = 1;
	resDesc.Width = (dataSize * 0xff) & ~0xff;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// 定数バッファの生成
	buff_.Create(&heapProp, &resDesc);

	// 定数バッファのマッピング
	YDX::Result(buff_.Get()->Map(0, nullptr, map));

	// CBV生成
	viewDesc_.BufferLocation = buff_.Get()->GetGPUVirtualAddress();
	viewDesc_.SizeInBytes = static_cast<UINT>(resDesc.Width);
	spDescHeap_->CreateCBV(viewDesc_, isClearWhenTransition);
}

void BaseConstBuffer::SetDrawCommand(const uint32_t rootParamIndex)
{
	// 定数バッファビュー設定コマンド
	spCmdList_->SetGraphicsRootConstantBufferView(static_cast<UINT>(rootParamIndex), viewDesc_.BufferLocation);
}
