#pragma once
#include <d3d12.h>
#include "Vec2.h"
#include "Vec3.h"
#include <vector>
#include "DXResource.h"
#include "DXCommandList.h"

#pragma comment(lib, "d3d12.lib")

// ���_�f�[�^�\����
struct VertexData2D
{
	Vec3 pos;	 // xyz���W
	Vec2 uv;	 // uv���W
};

class Vertices2D
{
public:
	std::vector<VertexData2D> v; // ���_�f�[�^
	DXResource vertBuff; // ���_�o�b�t�@
	D3D12_VERTEX_BUFFER_VIEW vbView{}; // ���_�o�b�t�@�r���[
	DXCommandList* cmdList = nullptr;
public:
	Vertices2D();
	Vertices2D(const std::vector<VertexData2D> v);
	void SetCommand();
	void Draw();
	void Init();
};

// ���_�f�[�^�\����
struct VertexData3D
{
	Vec3 pos;	 // xyz���W
	Vec3 normal; // �@���x�N�g��
	Vec2 uv;	 // uv���W
};

class Vertices3D
{
public:
	std::vector<VertexData3D> v; // ���_�f�[�^
	DXResourceInfo vertInfo; // ���_���
	DXResource vertBuff; // ���_�o�b�t�@
	D3D12_VERTEX_BUFFER_VIEW vbView{}; // ���_�o�b�t�@�r���[
	DXCommandList* cmdList = nullptr;
public:
	Vertices3D();
	Vertices3D(const std::vector<VertexData3D> v);
	void SetCommand();
	void Draw();
	void Init();
};