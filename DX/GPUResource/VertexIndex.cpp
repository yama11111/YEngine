#include "VertexIndex.h"
#include "Utility/Result.h"

using DX::GPUResource::VertexIndex;
using Math::Vec3;

VertexIndex::VertexIndex() :
	vert()
{
	idx.push_back(0);
}

VertexIndex::VertexIndex(const std::vector<VertexData3D> v, const std::vector<uint16_t> i) :
	vert(v), idx(i)
{
}

void VertexIndex::SetCommand()
{
	vert.SetCommand();
	vert.pCmdList->IASetIndexBuffer(&view);
}

void VertexIndex::Draw()
{
	// 描画コマンド
	vert.pCmdList->DrawIndexedInstanced((UINT)idx.size(), 1, 0, 0, 0); // 全ての頂点を使って描画
}

void VertexIndex::Initialize(const bool normalized)
{
	if (normalized) CalcNormal();
	vert.Initialize();
	UINT dataSize = static_cast <UINT> (sizeof(uint16_t) * idx.size());

	vert.info.resDesc.Width = dataSize; // インデックス情報が入る分のサイズ

	// 頂点バッファの生成
	buffer.Create(vert.info);
	// GPU上のバッファに対応した仮想メモリ(メインメモリ上)を取得
	uint16_t* idxMap = nullptr; // 仮想メモリ
	Utility::Result::Check(buffer.Get()->Map(0, nullptr, (void**)&idxMap));
	// 全頂点に対して
	for (int i = 0; i < idx.size(); i++)
	{
		idxMap[i] = idx[i];
	}
	// 繋がりを解除
	buffer.Get()->Unmap(0, nullptr);

	// 頂点バッファビューの作成
	// GPU仮想アドレス
	view.BufferLocation = buffer.Get()->GetGPUVirtualAddress();
	view.Format = DXGI_FORMAT_R16_UINT;
	// 頂点バッファのサイズ
	view.SizeInBytes = dataSize;
}

void VertexIndex::CalcNormal()
{
	for (size_t i = 0; i < idx.size() / 3; i++)
	{// 三角形1つごとに計算していく
		// 三角形のインデックスを取り出して、一般的な変数に入れる
		unsigned short index0 = idx[i * 3 + 0];
		unsigned short index1 = idx[i * 3 + 1];
		unsigned short index2 = idx[i * 3 + 2];
		// 三角形を構成する頂点座標ベクトルに代入
		Vec3 p0 = vert.v[index0].pos;
		Vec3 p1 = vert.v[index1].pos;
		Vec3 p2 = vert.v[index2].pos;
		// p0->p1ベクトル、p0->p2ベクトルを計算 (ベクトルの減算)
		Vec3 v1 = p1 - p0;
		Vec3 v2 = p2 - p0;
		// 外積は両方から垂直なベクトル
		Vec3 normal = v1.Cross(v2);
		// 正規化 (長さを1にする)
		normal = normal.Normalized();
		// 求めた法線を頂点データに代入
		vert.v[index0].normal = normal;
		vert.v[index1].normal = normal;
		vert.v[index2].normal = normal;
	}
}
