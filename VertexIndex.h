#pragma once
#include "Vertices.h"

class VertexIndex
{
public:
	Vertices3D vert; // 頂点
	std::vector<uint16_t> idx; // インデックスデータ
	DXResource idxBuff; // インデックスバッファ
	D3D12_INDEX_BUFFER_VIEW ibView{}; // インデックスバッファビュー
public:
	VertexIndex();
	VertexIndex(const std::vector<VertexData3D> v, const std::vector<uint16_t> i);
	void SetCommand();
	void Draw();
	void Init(const bool normalized);
private:
	void CalcNormal();
};

