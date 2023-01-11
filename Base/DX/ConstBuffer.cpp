#include "ConstBuffer.h"
#include "YAssert.h"

using YDX::ConstBufferCommon;

ID3D12GraphicsCommandList* ConstBufferCommon::pCmdList_ = nullptr;
YDX::DescriptorHeap* ConstBufferCommon::pDescHeap_ = nullptr;

void ConstBufferCommon::StaticInitialize(const StaticInitStatus& state)
{
	assert(state.pCmdList_);
	assert(state.pDescHeap_);

	pCmdList_ = state.pCmdList_;
	pDescHeap_ = state.pDescHeap_;
}

using YDX::ConstBuffer;

template<typename T>
UINT ConstBuffer<T>::rpIndex_ = UINT32_MAX;

template<typename T>
void ConstBuffer<T>::StaticSetRootParamIndex(const UINT rpIndex)
{
	rpIndex_ = rpIndex;
}

template<typename T>
void ConstBuffer<T>::Create()
{
	GPUResource::CreateStatus state;
	// ヒープ設定
	state.heapProp_.Type = D3D12_HEAP_TYPE_UPLOAD;
	// リソース設定
	state.resDesc_.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	state.resDesc_.Height = 1;
	state.resDesc_.Width = (sizeof(T) * 0xff) & ~0xff;
	state.resDesc_.DepthOrArraySize = 1;
	state.resDesc_.MipLevels = 1;
	state.resDesc_.SampleDesc.Count = 1;
	state.resDesc_.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// 定数バッファの生成
	rsc_.Create(state);

	// 定数バッファのマッピング
	Result(rsc_.Get()->Map(0, nullptr, (void**)&map_));

	// CBV生成
	viewDesc_.BufferLocation = rsc_.Get()->GetGPUVirtualAddress();
	viewDesc_.SizeInBytes = static_cast<UINT>(state.resDesc_.Width);
	pDescHeap_->CreateCBV(viewDesc_);
}

template<typename T>
void ConstBuffer<T>::SetDrawCommand()
{
	// 定数バッファビュー(3D変換行列)の設定コマンド
	pCmdList_->SetGraphicsRootConstantBufferView(rpIndex_, viewDesc_.BufferLocation);
}

template class ConstBuffer<YDX::TransformCBData>;
template class ConstBuffer<YDX::ColorCBData>;
template class ConstBuffer<YDX::MaterialCBData>;
template class ConstBuffer<YDX::BillboardCBData>;
