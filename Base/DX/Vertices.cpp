#include "Vertices.h"
#include "YAssert.h"

using DX::Vertices;
using DX::VertexIndex3D;
using Math::Vec3;

template <typename T>
ID3D12GraphicsCommandList* Vertices<T>::pCmdList_ = nullptr;

template <typename T>
void Vertices<T>::StaticInitialize(ID3D12GraphicsCommandList* pCommandList)
{
	assert(pCommandList);
	pCmdList_ = pCommandList;
}

template <typename T>
void Vertices<T>::Initialize(const std::vector<T> v)
{
	// 頂点情報をコピー
	v_ = v;

	// バッファとビュー作成
	Create();
}

template<typename T>
void Vertices<T>::TransferMap(const std::vector<T> v)
{
	// 頂点情報をクリア
	v_.clear();
	// 頂点情報をコピー
	v_ = v;
	// 全頂点に対して座標をコピー
	for (int i = 0; i < v_.size(); i++) { vertMap_[i] = v_[i]; }
}

template<typename T>
void Vertices<T>::Create()
{
	// 頂点サイズ
	UINT dataSize = static_cast <UINT> (sizeof(v_[0]) * v_.size());

	// 生成用設定
	GPUResource::CreateStatus state{};

	// 頂点バッファ設定
	state.heapProp_.Type = D3D12_HEAP_TYPE_UPLOAD; // GPUへの転送用
	// リソース設定
	state.resDesc_.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	state.resDesc_.Width = dataSize; // 頂点データ全体のサイズ
	state.resDesc_.Height = 1;
	state.resDesc_.DepthOrArraySize = 1;
	state.resDesc_.MipLevels = 1;
	state.resDesc_.SampleDesc.Count = 1;
	state.resDesc_.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// 頂点バッファの生成
	buffer_.Create(state);

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

template <typename T>
void Vertices<T>::Draw()
{
	// 頂点バッファビューの設定コマンド
	pCmdList_->IASetVertexBuffers(0, 1, &view_);
	// 描画コマンド
	pCmdList_->DrawInstanced((UINT)v_.size(), 1, 0, 0); // 全ての頂点を使って描画
}

template class Vertices<DX::SpriteVData>;
template class Vertices<DX::ModelVData>;

void VertexIndex3D::Initialize(const std::vector<ModelVData> v, const std::vector<uint16_t> idx, const bool normalized)
{
	// 頂点情報をコピー
	v_ = v;
	// インデックス情報をコピー
	idx_ = idx;

	// 法線計算
	if (normalized) { Normalized(); }

	// ----- vertices ----- //

	Create();

	// ----- index ----- //

	// インデックスサイズ
	UINT dataSize = static_cast <UINT> (sizeof(uint16_t) * idx.size());

	// 生成用設定
	GPUResource::CreateStatus state{};

	// 頂点バッファ設定
	state.heapProp_.Type = D3D12_HEAP_TYPE_UPLOAD; // GPUへの転送用
	// リソース設定
	state.resDesc_.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	state.resDesc_.Width = dataSize; // 頂点データ全体のサイズ
	state.resDesc_.Height = 1;
	state.resDesc_.DepthOrArraySize = 1;
	state.resDesc_.MipLevels = 1;
	state.resDesc_.SampleDesc.Count = 1;
	state.resDesc_.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// インデックスバッファの生成
	idxBuffer_.Create(state);
	// GPU上のバッファに対応した仮想メモリ(メインメモリ上)を取得
	uint16_t* idxMap = nullptr; // 仮想メモリ
	Result(idxBuffer_.Get()->Map(0, nullptr, (void**)&idxMap));
	// 全インデックスに対してインデックスをコピー
	for (int i = 0; i < idx_.size(); i++) { idxMap[i] = idx_[i]; }
	// 繋がりを解除
	idxBuffer_.Get()->Unmap(0, nullptr);

	// インデックスバッファビューの作成
	// GPU仮想アドレス
	idxView_.BufferLocation = idxBuffer_.Get()->GetGPUVirtualAddress();
	idxView_.Format = DXGI_FORMAT_R16_UINT;
	// インデックスバッファのサイズ
	idxView_.SizeInBytes = dataSize;
}

void VertexIndex3D::Normalized() 
{
	for (size_t i = 0; i < idx_.size() / 3; i++)
	{
		// 三角形1つごとに計算していく
		// 三角形のインデックスを取り出して、一般的な変数に入れる
		unsigned short index0 = idx_[i * 3 + 0];
		unsigned short index1 = idx_[i * 3 + 1];
		unsigned short index2 = idx_[i * 3 + 2];
		// 三角形を構成する頂点座標ベクトルに代入
		Vec3 p0 = v_[index0].pos_;
		Vec3 p1 = v_[index1].pos_;
		Vec3 p2 = v_[index2].pos_;
		// p0->p1ベクトル、p0->p2ベクトルを計算 (ベクトルの減算)
		Vec3 v1 = p1 - p0;
		Vec3 v2 = p2 - p0;
		// 外積は両方から垂直なベクトル
		Vec3 normal = v1.Cross(v2);
		// 正規化 (長さを1にする)
		normal = normal.Normalized();
		// 求めた法線を頂点データに代入
		v_[index0].normal_ = normal;
		v_[index1].normal_ = normal;
		v_[index2].normal_ = normal;
	}
}

void VertexIndex3D::Draw()
{
	// 頂点バッファビューの設定コマンド
	pCmdList_->IASetVertexBuffers(0, 1, &view_);
	// インデックスバッファビューの設定コマンド
	pCmdList_->IASetIndexBuffer(&idxView_);
	// 描画コマンド
	pCmdList_->DrawIndexedInstanced((UINT)idx_.size(), 1, 0, 0, 0); // 全ての頂点を使って描画
}