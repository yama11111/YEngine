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

	// ���_�o�b�t�@�ݒ�
	info.heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPU�ւ̓]���p
	// ���\�[�X�ݒ�
	info.resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	info.resDesc.Width = dataSize; // ���_�f�[�^�S�̂̃T�C�Y
	info.resDesc.Height = 1;
	info.resDesc.DepthOrArraySize = 1;
	info.resDesc.MipLevels = 1;
	info.resDesc.SampleDesc.Count = 1;
	info.resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// ���_�o�b�t�@�̐���
	buffer.Create(info);
	// GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	VertexData3D* vertMap = nullptr; // ���z������
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

void Vertices3D::Draw()
{
	// �`��R�}���h
	pCmdList->DrawInstanced((UINT)v.size(), 1, 0, 0); // �S�Ă̒��_���g���ĕ`��
}
