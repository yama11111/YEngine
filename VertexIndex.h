#pragma once
#include "Vertices.h"

class VertexIndex
{
public:
	Vertices vert; // ���_
	std::vector<uint16_t> idx; // �C���f�b�N�X�f�[�^
	DXResource idxBuff; // �C���f�b�N�X�o�b�t�@
	D3D12_INDEX_BUFFER_VIEW ibView{}; // �C���f�b�N�X�o�b�t�@�r���[
public:
	VertexIndex();
	VertexIndex(const std::vector<VertexData> v, const std::vector<uint16_t> i);
	void SetCommand();
	void Draw();
	void Init(const bool normalized);
private:
	void CalcNormal();
};

