#include "ConstBuffer.h"
#include "Sprite2DCommon.h"
#include "Sprite3DCommon.h"
#include "ModelCommon.h"
#include "LightGroup.h"
#include "Color.h"
#include "YAssert.h"

using YDX::ConstBufferCommon;

ID3D12GraphicsCommandList* ConstBufferCommon::pCommandList_ = nullptr;
YDX::DescriptorHeap* ConstBufferCommon::pDescHeap_ = nullptr;

void ConstBufferCommon::StaticInitialize(const StaticInitStatus& state)
{
	assert(state.pCommandList_);
	assert(state.pDescHeap_);

	pCommandList_ = state.pCommandList_;
	pDescHeap_ = state.pDescHeap_;
}

using YDX::ConstBuffer;

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
void ConstBuffer<T>::SetDrawCommand(const UINT rootParamIndex)
{
	// 定数バッファビュー(3D変換行列)の設定コマンド
	pCommandList_->SetGraphicsRootConstantBufferView(rootParamIndex, viewDesc_.BufferLocation);
}

template class ConstBuffer<YGame::Sprite2DCommon::CBData>;
template class ConstBuffer<YGame::Sprite3DCommon::CBData>;
template class ConstBuffer<YGame::ModelCommon::CBData>;
template class ConstBuffer<YGame::ModelCommon::MaterialCBData>;
template class ConstBuffer<YGame::Color::CBData>;
template class ConstBuffer<YGame::LightGroup::CBData>;
