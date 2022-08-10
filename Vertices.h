#pragma once
#include <d3d12.h>
#include "Vec2.h"
#include "Vec3.h"
#include <vector>
#include "DXResource.h"
#include "DXCommandList.h"

#pragma comment(lib, "d3d12.lib")

// ���_�f�[�^�\����
struct VertexData
{
	Vec3 pos;	 // xyz���W
	//Vec3 normal; // �@���x�N�g��
	Vec2 uv;	 // uv���W
};

class Vertices
{
public:
	std::vector<VertexData> v; // ���_�f�[�^
	DXResourceInfo vertInfo; // ���_���
	DXResource vertBuff; // ���_�o�b�t�@
	D3D12_VERTEX_BUFFER_VIEW vbView{}; // ���_�o�b�t�@�r���[
	DXCommandList* cmdList = nullptr;
public:
	Vertices();
	Vertices(const std::vector<VertexData> v);
	void SetCommand();
	void Draw();
	void Init();
};
