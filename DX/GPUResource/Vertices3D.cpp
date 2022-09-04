#include "Vertices3D.h"
#include "Utility/Result.h"

using DX::GPUResource::Vertices3D;

Vertices3D::Vertices3D()
{
	v.push_back({ { 0.0f,0.0f,0.0f },{ 0.0f,0.0f,0.0f },{ 0.0f,0.0f } });
}
Vertices3D::Vertices3D(const std::vector<VertexData3D> v) :
	v(v)
{
}

void Vertices3D::Initialize()
{
	UINT dataSize = static_cast <UINT> (sizeof(v[0]) * v.size());

	// 頂点バッファ設定
	info.heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPUへの転送用
	// リソース設定
	info.resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	info.resDesc.Width = dataSize; // 頂点データ全体のサイズ
	info.resDesc.Height = 1;
	info.resDesc.DepthOrArraySize = 1;
	info.resDesc.MipLevels = 1;
	info.resDesc.SampleDesc.Count = 1;
	info.resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// 頂点バッファの生成
	buffer.Create(info);
	// GPU上のバッファに対応した仮想メモリ(メインメモリ上)を取得
	VertexData3D* vertMap = nullptr; // 仮想メモリ
	Utility::Result::Check(buffer.Get()->Map(0, nullptr, (void**)&vertMap));
	// 全頂点に対して
	for (int i = 0; i < v.size(); i++)
	{
		vertMap[i] = v[i]; // 座標をコピー
	}
	// 繋がりを解除
	buffer.Get()->Unmap(0, nullptr);

	// 頂点バッファビューの作成
	// GPU仮想アドレス
	view.BufferLocation = buffer.Get()->GetGPUVirtualAddress();
	// 頂点バッファのサイズ
	view.SizeInBytes = dataSize;
	// 頂点1つ分のデータサイズ
	view.StrideInBytes = sizeof(v[0]);
}

void Vertices3D::Draw()
{
	// 描画コマンド
	pCmdList->DrawInstanced((UINT)v.size(), 1, 0, 0); // 全ての頂点を使って描画
}
