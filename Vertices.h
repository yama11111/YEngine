#pragma once
#include <d3d12.h>
#include "Vec2.h"
#include "Vec3.h"
#include <vector>
#include "DXResource.h"
#include "DXCommandList.h"

#pragma comment(lib, "d3d12.lib")

// 頂点データ構造体
struct VertexData
{
	Vec3 pos;	 // xyz座標
	//Vec3 normal; // 法線ベクトル
	Vec2 uv;	 // uv座標
};

class Vertices
{
public:
	std::vector<VertexData> v; // 頂点データ
	DXResourceInfo vertInfo; // 頂点情報
	DXResource vertBuff; // 頂点バッファ
	D3D12_VERTEX_BUFFER_VIEW vbView{}; // 頂点バッファビュー
	DXCommandList* cmdList = nullptr;
public:
	Vertices();
	Vertices(const std::vector<VertexData> v);
	void SetCommand();
	void Draw();
	void Init();
};
