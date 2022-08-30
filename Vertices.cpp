#include "Vertices.h"
#include "Result.h"

// ----- Vertices2D ----- //
Vertices2D::Vertices2D()
{
	v.push_back({ { 0.0f,0.0f,0.0f },{ 0.0f,0.0f } });
}
Vertices2D::Vertices2D(const std::vector<VertexData2D> v) :
	v(v)
{
}

void Vertices2D::SetCommand()
{
	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	cmdList->List()->IASetVertexBuffers(0, 1, &vbView);
}
void Vertices2D::Draw()
{
	// �`��R�}���h
	cmdList->List()->
		DrawInstanced((UINT)v.size(), 1, 0, 0); // �S�Ă̒��_���g���ĕ`��
}

void Vertices2D::Init()
{
	cmdList = DXCommandList::GetInstance();
	UINT dataSize = static_cast <UINT> (sizeof(v[0]) * v.size());

	// ���_�o�b�t�@�ݒ�
	DXResourceInfo vertInfo; // ���_���
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
	vertBuff.Create(vertInfo);
	// GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	VertexData2D* vertMap = nullptr; // ���z������
	Result::Check(vertBuff.buff->Map(0, nullptr, (void**)&vertMap));
	// �S���_�ɑ΂���
	for (int i = 0; i < v.size(); i++)
	{
		vertMap[i] = v[i]; // ���W���R�s�[
	}
	// �q���������
	vertBuff.buff->Unmap(0, nullptr);

	// ���_�o�b�t�@�r���[�̍쐬
	// GPU���z�A�h���X
	vbView.BufferLocation = vertBuff.buff->GetGPUVirtualAddress();
	// ���_�o�b�t�@�̃T�C�Y
	vbView.SizeInBytes = dataSize;
	// ���_1���̃f�[�^�T�C�Y
	vbView.StrideInBytes = sizeof(v[0]);
}

// ----- Vertices3D ----- //
Vertices3D::Vertices3D()
{
	v.push_back({ { 0.0f,0.0f,0.0f },{ 0.0f,0.0f,0.0f },{ 0.0f,0.0f } });
}
Vertices3D::Vertices3D(const std::vector<VertexData3D> v) :
	v(v)
{
}

void Vertices3D::SetCommand()
{
	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	cmdList->List()->IASetVertexBuffers(0, 1, &vbView);
}
void Vertices3D::Draw()
{
	// �`��R�}���h
	cmdList->List()->
		DrawInstanced((UINT)v.size(), 1, 0, 0); // �S�Ă̒��_���g���ĕ`��
}

void Vertices3D::Init()
{
	cmdList = DXCommandList::GetInstance();
	UINT dataSize = static_cast <UINT> (sizeof(v[0]) * v.size());

	// ���_�o�b�t�@�ݒ�
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
	vertBuff.Create(vertInfo);
	// GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	VertexData3D* vertMap = nullptr; // ���z������
	Result::Check(vertBuff.buff->Map(0, nullptr, (void**)&vertMap));
	// �S���_�ɑ΂���
	for (int i = 0; i < v.size(); i++)
	{
		vertMap[i] = v[i]; // ���W���R�s�[
	}
	// �q���������
	vertBuff.buff->Unmap(0, nullptr);

	// ���_�o�b�t�@�r���[�̍쐬
	// GPU���z�A�h���X
	vbView.BufferLocation = vertBuff.buff->GetGPUVirtualAddress();
	// ���_�o�b�t�@�̃T�C�Y
	vbView.SizeInBytes = dataSize;
	// ���_1���̃f�[�^�T�C�Y
	vbView.StrideInBytes = sizeof(v[0]);
}
