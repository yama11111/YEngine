#include "VertexIndex.h"
#include "Result.h"

VertexIndex::VertexIndex() :
	vert()
{
	idx.push_back(0);
}

VertexIndex::VertexIndex(const std::vector<VertexData> v, const std::vector<uint16_t> i) :
	vert(v), idx(i)
{
}

void VertexIndex::SetCommand()
{
	vert.SetCommand();
	vert.cmdList->List()->IASetIndexBuffer(&ibView);
}

void VertexIndex::Draw()
{
	// �`��R�}���h
	vert.cmdList->List()->
		DrawIndexedInstanced((UINT)idx.size(), 1, 0, 0, 0); // �S�Ă̒��_���g���ĕ`��
}

void VertexIndex::Init()
{
	CalcNormal();
	vert.Init();
	UINT dataSize = static_cast <UINT> (sizeof(uint16_t) * idx.size());

	vert.vertInfo.resDesc.Width = dataSize; // �C���f�b�N�X��񂪓��镪�̃T�C�Y

	// ���_�o�b�t�@�̐���
	idxBuff.Create(vert.vertInfo);
	// GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	uint16_t* idxMap = nullptr; // ���z������
	Result::Check(idxBuff.buff->Map(0, nullptr, (void**)&idxMap));
	// �S���_�ɑ΂���
	for (int i = 0; i < idx.size(); i++)
	{
		idxMap[i] = idx[i];
	}
	// �q���������
	idxBuff.buff->Unmap(0, nullptr);

	// ���_�o�b�t�@�r���[�̍쐬
	// GPU���z�A�h���X
	ibView.BufferLocation = idxBuff.buff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	// ���_�o�b�t�@�̃T�C�Y
	ibView.SizeInBytes = dataSize;
}

void VertexIndex::CalcNormal()
{
	//for (int i = 0; i < idxData.i.size() / 3; i++)
	//{// �O�p�`1���ƂɌv�Z���Ă���
	//	// �O�p�`�̃C���f�b�N�X�����o���āA��ʓI�ȕϐ��ɓ����
	//	unsigned short index0 = idxData.i[i * 3 + 0];
	//	unsigned short index1 = idxData.i[i * 3 + 1];
	//	unsigned short index2 = idxData.i[i * 3 + 2];
	//	// �O�p�`���\�����钸�_���W�x�N�g���ɑ��
	//	Vec3 p0 = vert.v[index0].pos;
	//	Vec3 p1 = vert.v[index1].pos;
	//	Vec3 p2 = vert.v[index2].pos;
	//	// p0->p1�x�N�g���Ap0->p2�x�N�g�����v�Z (�x�N�g���̌��Z)
	//	Vec3 v1 = p1 - p0;
	//	Vec3 v2 = p2 - p0;
	//	// �O�ς͗������琂���ȃx�N�g��
	//	Vec3 normal = v1.Cross(v2);
	//	// ���K�� (������1�ɂ���)
	//	normal = normal.Normalized();
	//	// ���߂��@���𒸓_�f�[�^�ɑ��
	//	vert.v[index0].normal = normal;
	//	vert.v[index1].normal = normal;
	//	vert.v[index2].normal = normal;
	//}
}
