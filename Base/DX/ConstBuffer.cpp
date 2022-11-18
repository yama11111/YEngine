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
}

template<typename T>
void ConstBuffer<T>::SetDrawCommand()
{
	// 定数バッファビュー(3D変換行列)の設定コマンド
	pCmdList_->SetGraphicsRootConstantBufferView(rpIndex_, rsc_.Get()->GetGPUVirtualAddress());
}

template class ConstBuffer<DX::TransformCBData>;
template class ConstBuffer<DX::ColorCBData>;
template class ConstBuffer<DX::MaterialCBData>;