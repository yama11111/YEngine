#include "Vertices2D.h"
#include "Utility/Result.h"

using DX::GPUResource::Vertices2D;

Vertices2D::Vertices2D()
{
	v.push_back({ { 0.0f,0.0f,0.0f },{ 0.0f,0.0f } });
}
Vertices2D::Vertices2D(const std::vector<VertexData2D> v) :
	v(v)
{
}

void Vertices2D::Initialize()
{
	UINT dataSize = static_cast <UINT> (sizeof(v[0]) * v.size());

	// ���_�o�b�t�@�ݒ�
	Utility::ResourceInfo vertInfo; // ���_���
	vertInfo.heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPU�ւ̓]���p
	// ���\�[�X�ݒ�
	vertInfo.resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	vertInfo.resDesc.Width = dataSize; // ���_�f�[�^�S�̂̃T�C�Y
	vertInfo.resDesc.Height = 1;
	vertInfo.resDesc.DepthOrArraySize = 1;
	vertInfo.resDesc.MipLevels = 1;
	vertInfo.resDesc.SampleDesc.Count = 1;
	vertInfo.resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// ���_�o�b�t�@�̐���
	buffer.Create(vertInfo);
	// GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	VertexData2D* vertMap = nullptr; // ���z������
	Utility::Result::Check(buffer.Get()->Map(0, nullptr, (void**)&vertMap));
	// �S���_�ɑ΂���
	for (int i = 0; i < v.size(); i++)
	{
		vertMap[i] = v[i]; // ���W���R�s�[
	}
	// �q���������
	buffer.Get()->Unmap(0, nullptr);

	// ���_�o�b�t�@�r���[�̍쐬
	// GPU���z�A�h���X
	view.BufferLocation = buffer.Get()->GetGPUVirtualAddress();
	// ���_�o�b�t�@�̃T�C�Y
	view.SizeInBytes = dataSize;
	// ���_1���̃f�[�^�T�C�Y
	view.StrideInBytes = sizeof(v[0]);
}

void Vertices2D::Draw()
{
	// �`��R�}���h
	pCmdList->DrawInstanced((UINT)v.size(), 1, 0, 0); // �S�Ă̒��_���g���ĕ`��
}
