#include "Vertices.h"
#include "YAssert.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Mesh.h"
#include "PostEffect.h"

using YDX::VertexCommon;
using YDX::Vertices;
using YDX::VertexIndex;

ID3D12GraphicsCommandList* VertexCommon::spCmdList_ = nullptr;

void VertexCommon::StaticInitialize(ID3D12GraphicsCommandList* pCommandList)
{
	assert(pCommandList);
	spCmdList_ = pCommandList;
}

template <typename VData>
void Vertices<VData>::Initialize(const std::vector<VData>& v)
{
	// 頂点情報をコピー
	v_ = v;

	// バッファとビュー作成
	Create();
}

template<typename VData>
void Vertices<VData>::TransferMap(const std::vector<VData>& v)
{
	// 頂点情報をクリア
	v_.clear();
	// 頂点情報をコピー
	v_ = v;
	// 全頂点に対して座標をコピー
	for (int i = 0; i < v_.size(); i++) { vertMap_[i] = v_[i]; }
}

template<typename VData>
void Vertices<VData>::Create()
{
	// 頂点サイズ
	UINT dataSize = static_cast <UINT> (sizeof(v_[0]) * v_.size());

	// 頂点バッファ設定
	D3D12_HEAP_PROPERTIES heapProp{};
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPUへの転送用

	// リソース設定
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = dataSize; // 頂点データ全体のサイズ
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// 頂点バッファの生成
	buffer_.Create(&heapProp, &resDesc);


	// GPU上のバッファに対応した仮想メモリ(メインメモリ上)を取得
	Result(buffer_.Get()->Map(0, nullptr, (void**)&vertMap_));
	
	// 全頂点に対して座標をコピー
	for (int i = 0; i < v_.size(); i++) { vertMap_[i] = v_[i]; }
	
	// 繋がりを解除
	buffer_.Get()->Unmap(0, nullptr);


	// 頂点バッファビューの作成
	
	// GPU仮想アドレス
	view_.BufferLocation = buffer_.Get()->GetGPUVirtualAddress();
	
	// 頂点バッファのサイズ
	view_.SizeInBytes = dataSize;
	
	// 頂点1つ分のデータサイズ
	view_.StrideInBytes = sizeof(v_[0]);
}

template <typename VData>
void Vertices<VData>::Draw() const
{
	// 頂点バッファビューの設定コマンド
	spCmdList_->IASetVertexBuffers(0, 1, &view_);
	
	// 描画コマンド
	spCmdList_->DrawInstanced(static_cast<UINT>(v_.size()), 1, 0, 0); // 全ての頂点を使って描画
}

template <typename VData>
void VertexIndex<VData>::Initialize(const std::vector<VData>& v, const std::vector<uint16_t>& idx)
{
	// 頂点情報をコピー
	this->v_ = v;
	
	// インデックス情報をコピー
	this->idx_ = idx;

	// ----- vertices ----- //

	this->Create();

	// ----- index ----- //

	// インデックスサイズ
	UINT dataSize = static_cast <UINT> (sizeof(uint16_t) * idx.size());

	// 頂点バッファ設定
	D3D12_HEAP_PROPERTIES heapProp{};
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPUへの転送用

	// リソース設定
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = dataSize; // 頂点データ全体のサイズ
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// インデックスバッファの生成
	idxBuffer_.Create(&heapProp, &resDesc);


	// GPU上のバッファに対応した仮想メモリ(メインメモリ上)を取得
	
	uint16_t* idxMap = nullptr; // 仮想メモリ
	
	Result(idxBuffer_.Get()->Map(0, nullptr, (void**)&idxMap));
	
	// 全インデックスに対してインデックスをコピー
	for (int i = 0; i < this->idx_.size(); i++) { idxMap[i] = this->idx_[i]; }
	
	// 繋がりを解除
	idxBuffer_.Get()->Unmap(0, nullptr);


	// インデックスバッファビューの作成
	
	// GPU仮想アドレス
	idxView_.BufferLocation = idxBuffer_.Get()->GetGPUVirtualAddress();
	idxView_.Format = DXGI_FORMAT_R16_UINT;
	
	// インデックスバッファのサイズ
	idxView_.SizeInBytes = dataSize;
}

template <typename VData>
void VertexIndex<VData>::Draw() const
{
	// 頂点バッファビューの設定コマンド
	this->spCmdList_->IASetVertexBuffers(0, 1, &this->view_);
	
	// インデックスバッファビューの設定コマンド
	this->spCmdList_->IASetIndexBuffer(&idxView_);
	
	// 描画コマンド
	this->spCmdList_->DrawIndexedInstanced(static_cast<UINT>(idx_.size()), 1, 0, 0, 0); // 全ての頂点を使って描画
}

template class YDX::Vertices<YGame::Sprite2D::VData>;
template class YDX::Vertices<YGame::Sprite3D::VData>;
template class YDX::Vertices<YGame::Mesh::VData>;
template class YDX::Vertices<YGame::PostEffect::VData>;
template class YDX::VertexIndex<YGame::Sprite2D::VData>;
template class YDX::VertexIndex<YGame::Sprite3D::VData>;
template class YDX::VertexIndex<YGame::Mesh::VData>;
template class YDX::VertexIndex<YGame::PostEffect::VData>;