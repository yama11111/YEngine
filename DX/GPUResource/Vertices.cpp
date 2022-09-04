#include "Vertices.h"
#include <cassert>

using DX::GPUResource::Vertices;

ID3D12GraphicsCommandList* Vertices::pCmdList = nullptr;

void Vertices::StaticInit(ID3D12GraphicsCommandList* pCommandList)
{
	assert(pCommandList != nullptr);
	pCmdList = pCommandList;
}

void Vertices::SetCommand()
{
	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	pCmdList->IASetVertexBuffers(0, 1, &view);
}