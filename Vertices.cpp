#include "Vertices.h"
#include "Result.h"

Vertices::Vertices()
{
	v.push_back({ { 0.0f,0.0f,0.0f },{ 0.0f,0.0f,0.0f },{ 0.0f,0.0f } });
}

Vertices::Vertices(const std::vector<VertexData> v) :
	v(v)
{
}

void Vertices::SetCommand()
{
	// 頂点バッファビューの設定コマンド
	cmdList->List()->IASetVertexBuffers(0, 1, &vbView);
}

void Vertices::Draw()
{
	// 描画コマンド
	cmdList->List()->
		DrawInstanced((UINT)v.size(), 1, 0, 0); // 全ての頂点を使って描画
}

void Vertices::Init()
{
	cmdList = DXCommandList::GetInstance();
	UINT dataSize = static_cast <UINT> (sizeof(v[0]) * v.size());

	// 頂点バッファ設定
	vertInfo.heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPUへの転送用
	// リソース設定
	vertInfo.resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	vertInfo.resDesc.Width = dataSize; // 頂点データ全体のサイズ
	vertInfo.resDesc.Height = 1;
	vertInfo.resDesc.DepthOrArraySize = 1;
	vertInfo.resDesc.MipLevels = 1;
	vertInfo.resDesc.SampleDesc.Count = 1;
	vertInfo.resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// 頂点バッファの生成
	vertBuff.Create(vertInfo);
	// GPU上のバッファに対応した仮想メモリ(メインメモリ上)を取得
	VertexData* vertMap = nullptr; // 仮想メモリ
	Result::Check(vertBuff.buff->Map(0, nullptr, (void**)&vertMap));
	// 全頂点に対して
	for (int i = 0; i < v.size(); i++)
	{
		vertMap[i] = v[i]; // 座標をコピー
	}
	// 繋がりを解除
	vertBuff.buff->Unmap(0, nullptr);

	// 頂点バッファビューの作成
	// GPU仮想アドレス
	vbView.BufferLocation = vertBuff.buff->GetGPUVirtualAddress();
	// 頂点バッファのサイズ
	vbView.SizeInBytes = dataSize;
	// 頂点1つ分のデータサイズ
	vbView.StrideInBytes = sizeof(v[0]);
}
