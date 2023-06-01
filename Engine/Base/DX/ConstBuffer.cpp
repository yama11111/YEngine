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
	// ヒープ設定
	D3D12_HEAP_PROPERTIES heapProp{};
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;

	// リソース設定
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Height = 1;
	resDesc.Width = (sizeof(T) * 0xff) & ~0xff;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// 定数バッファの生成
	buff_.Create(&heapProp, &resDesc);

	// 定数バッファのマッピング
	Result(buff_.Get()->Map(0, nullptr, (void**)&map_));

	// CBV生成
	viewDesc_.BufferLocation = buff_.Get()->GetGPUVirtualAddress();
	viewDesc_.SizeInBytes = static_cast<UINT>(resDesc.Width);
	spDescHeap_->CreateCBV(viewDesc_, isMutable);
}

template<typename T>
void ConstBuffer<T>::SetDrawCommand(const UINT rootParamIndex)
{
	// 定数バッファビュー(3D変換行列)の設定コマンド
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
