#include "Mesh.h"
#include "FileUtillity.h"
#include <cassert>
#include <fstream>
#include <sstream>

#pragma region ���O���

using YGame::Mesh;
using YGame::Material;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;

#pragma endregion

Mesh* Mesh::CreateCube()
{
	// �C���X�^���X���� (���I)
	Mesh* instance = new Mesh();

	// ���_
	std::vector<VData> v =
	{
		// �O
		{{ -1.0f, -1.0f, -1.0f }, {}, {0.0f, 1.0f}}, // ����
		{{ -1.0f,  1.0f, -1.0f }, {}, {0.0f, 0.0f}}, // ����
		{{  1.0f, -1.0f, -1.0f }, {}, {1.0f, 1.0f}}, // �E��
		{{  1.0f,  1.0f, -1.0f }, {}, {1.0f, 0.0f}}, // �E��

		// ��
		{{ -1.0f, -1.0f,  1.0f }, {}, {1.0f, 1.0f}}, // ����
		{{ -1.0f,  1.0f,  1.0f }, {}, {1.0f, 0.0f}}, // ����
		{{  1.0f, -1.0f,  1.0f }, {}, {0.0f, 1.0f}}, // �E��
		{{  1.0f,  1.0f,  1.0f }, {}, {0.0f, 0.0f}}, // �E��

		// ��
		{{ -1.0f, -1.0f, -1.0f }, {}, {1.0f, 1.0f}}, // ����
		{{ -1.0f, -1.0f,  1.0f }, {}, {0.0f, 1.0f}}, // ����
		{{ -1.0f,  1.0f, -1.0f }, {}, {1.0f, 0.0f}}, // �E��
		{{ -1.0f,  1.0f,  1.0f }, {}, {0.0f, 0.0f}}, // �E��

		// �E
		{{  1.0f, -1.0f, -1.0f }, {}, {0.0f, 1.0f}}, // ����
		{{  1.0f, -1.0f,  1.0f }, {}, {1.0f, 1.0f}}, // ����
		{{  1.0f,  1.0f, -1.0f }, {}, {0.0f, 0.0f}}, // �E��
		{{  1.0f,  1.0f,  1.0f }, {}, {1.0f, 0.0f}}, // �E��

		// ��
		{{ -1.0f, -1.0f,  1.0f }, {}, {0.0f, 0.0f}}, // ����
		{{ -1.0f, -1.0f, -1.0f }, {}, {0.0f, 1.0f}}, // ����
		{{  1.0f, -1.0f,  1.0f }, {}, {1.0f, 0.0f}}, // �E��
		{{  1.0f, -1.0f, -1.0f }, {}, {1.0f, 1.0f}}, // �E��

		// ��
		{{ -1.0f,  1.0f,  1.0f }, {}, {0.0f, 0.0f}}, // ����
		{{ -1.0f,  1.0f, -1.0f }, {}, {0.0f, 1.0f}}, // ����
		{{  1.0f,  1.0f,  1.0f }, {}, {1.0f, 0.0f}}, // �E��
		{{  1.0f,  1.0f, -1.0f }, {}, {1.0f, 1.0f}}, // �E��
	};
	// �C���f�b�N�X
	std::vector<uint16_t> i =
	{
		// �O
		0, 1, 2, // �O�p�`1��
		2, 1, 3, // �O�p�`2��

		// ��
		6, 7, 4, // �O�p�`1��
		4, 7, 5, // �O�p�`2��

		// ��
		8, 9, 10, // �O�p�`1��
		10, 9, 11, // �O�p�`2��

		// �E
		14, 15, 12, // �O�p�`1��
		12, 15, 13, // �O�p�`2��

		// ��
		16, 17, 18, // �O�p�`1��
		18, 17, 19, // �O�p�`2��

		//// ��
		22, 23, 20, // �O�p�`1��
		20, 23, 21, // �O�p�`2��
	};

	// �@�����v�Z
	CalculateNormals(v, i);

	// ���_�C���f�b�N�X������(���)
	instance->vtIdx_.Initialize(v, i);
	// �}�e���A��������
	instance->mtrl_ = Material();

	// �C���X�^���X��Ԃ�
	return instance;
}

Mesh* Mesh::CreateCube(const std::string& texFileName)
{
	// ����
	Mesh* instance = CreateCube();

	// �摜�ǂݍ���
	instance->mtrl_.LoadTexture(texFileName);

	// �C���X�^���X��Ԃ�
	return instance;
}

Mesh* Mesh::Load(const std::string& directoryPath, const std::string& objFileName, const bool isSmoothing)
{
	// �C���X�^���X���� (���I)
	Mesh* instance = new Mesh();

	// ���_
	std::vector<VData> v;
	// �C���f�b�N�X
	std::vector<uint16_t> i;
	// ���_�@���X���[�V���O�p�f�[�^
	std::unordered_map<unsigned short, std::vector<unsigned short>> sd;
	// �}�e���A��
	Material m;

	// �t�@�C���X�g���[��
	std::ifstream file;

	// .obj�t�@�C�����J��
	file.open(directoryPath + objFileName);
	// �t�@�C���I�[�v�����s���`�F�b�N
	assert(file);

	// ���_���W
	std::vector<Vector3> positions;
	// �@��
	std::vector<Vector3> normals;
	// UV���W
	std::vector<Vector2> uvs;

	// 1�s���ǂݍ���
	std::string line;
	while (std::getline(file, line))
	{
		// 1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		std::istringstream lineStream(line);

		// ���p�X�y�[�X��؂�ōs�̐擪��������擾
		std::string key;
		std::getline(lineStream, key, ' ');

#pragma region �}�e���A��

		// �擪������ "mtllib" �Ȃ�}�e���A��
		if (key == "mtllib")
		{
			// �}�e���A���t�@�C�����擾
			std::string mtlFileName;
			lineStream >> mtlFileName;
			// �}�e���A���ǂݍ���
			m = Material::Load(directoryPath, mtlFileName);
		}

#pragma endregion

#pragma region ���_�f�[�^

		// �擪������ "v" �Ȃ璸�_���W
		if (key == "v")
		{
			// ���_���W
			Vector3 pos;
			// �ǂݍ���
			lineStream >> pos.x_;
			lineStream >> pos.y_;
			lineStream >> pos.z_;
			// �ǉ�
			positions.push_back(pos);
		}
		// �擪������ "vt" �Ȃ�e�N�X�`��
		if (key == "vt")
		{
			// UV���W
			Vector2 uv;
			// �ǂݍ���
			lineStream >> uv.x_;
			lineStream >> uv.y_;
			// v���]
			uv.y_ = 1.0f - uv.y_;
			// �ǉ�
			uvs.push_back(uv);
		}
		// �擪������ "vn" �Ȃ�@���x�N�g��
		if (key == "vn")
		{
			// �@��
			Vector3 normal;
			// �ǂݍ���
			lineStream >> normal.x_;
			lineStream >> normal.y_;
			lineStream >> normal.z_;
			// �ǉ�
			normals.push_back(normal);
		}

#pragma endregion

#pragma region �C���f�b�N�X�f�[�^

		// �擪������ "f" �Ȃ�|���S��(�O�p�`)
		if (key == "f")
		{
			// ���p�X�y�[�X��؂�ōs�̑����ǂݍ���
			std::string indexString;
			while (std::getline(lineStream, indexString, ' '))
			{
				// ���_�C���f�b�N�X1���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
				std::istringstream indexStream(indexString);

				// �C���f�b�N�X�f�[�^
				uint16_t idPositon, idNormal, idTexcoord;

				// �ǂݍ���
				indexStream >> idPositon;
				// '/' ��΂�
				indexStream.seekg(1, std::ios_base::cur);
				// �ǂݍ���
				indexStream >> idTexcoord;
				// '/' ��΂�
				indexStream.seekg(1, std::ios_base::cur);
				// �ǂݍ���
				indexStream >> idNormal;

				// ���_�f�[�^
				VData vData;
				vData.pos_ = positions[static_cast<size_t>(idPositon - 1)];
				vData.normal_ = normals[static_cast<size_t>(idNormal - 1)];
				vData.uv_ = uvs[static_cast<size_t>(idTexcoord - 1)];

				// �ǉ�
				v.push_back(vData);
				// �ǉ�
				i.push_back(static_cast<uint16_t>(i.size()));
				// �ǉ�
				if (isSmoothing)
				{
					sd[idPositon].emplace_back(static_cast<unsigned short>(v.size() - 1));
				}
			}
		}

#pragma endregion

	}

	// �t�@�C�������
	file.close();

	// �X���[�V���O���邩
	if (isSmoothing)
	{
		// �X���[�V���O�v�Z
		CalculateSmoothedVertexNormals(v, sd);
	}


	// ���_�C���f�b�N�X������(���)
	instance->vtIdx_.Initialize(v, i);
	// �X���[�X�f�[�^���
	instance->smoothData_ = sd;
	// �}�e���A�����
	instance->mtrl_ = m;

	// �C���X�^���X��Ԃ�
	return instance;
}

void Mesh::CalculateNormals(std::vector<VData>& v, const std::vector<uint16_t>& indices)
{
	// �O�p�`1���ƂɌv�Z���Ă���
	for (size_t i = 0; i < indices.size() / 3; i++)
	{
		// �O�p�`�̃C���f�b�N�X�����o��
		unsigned short index0 = indices[i * 3 + 0];
		unsigned short index1 = indices[i * 3 + 1];
		unsigned short index2 = indices[i * 3 + 2];

		// �O�p�`���\�����钸�_���W�x�N�g���ɑ��
		Vector3 p0 = v[index0].pos_;
		Vector3 p1 = v[index1].pos_;
		Vector3 p2 = v[index2].pos_;

		// p0->p1�x�N�g���Ap0->p2�x�N�g�����v�Z (�x�N�g���̌��Z)
		Vector3 v1 = p1 - p0;
		Vector3 v2 = p2 - p0;

		// �O�ς͗������琂���ȃx�N�g��
		Vector3 normal = v1.Cross(v2);

		// ���K�� (������1�ɂ���)
		normal = normal.Normalized();

		// ���߂��@���𒸓_�f�[�^�ɑ��
		v[index0].normal_ = normal;
		v[index1].normal_ = normal;
		v[index2].normal_ = normal;
	}
}

void Mesh::CalculateSmoothedVertexNormals(std::vector<VData>& vertices, 
	std::unordered_map<unsigned short, std::vector<unsigned short>>& smoothData)
{
	// �X���[�X�f�[�^�̐�����
	auto itr = smoothData.begin();
	for (; itr != smoothData.end(); ++itr)
	{
		// ���̗v�f����
		std::vector<unsigned short>& v = itr->second;

		// �@��
		Vector3 normal = {};

		// �v�Z
		for (unsigned short index : v)
		{
			normal += vertices[index].normal_;
		}
		normal = (normal / (float)v.size()).Normalized();

		// ���
		for (unsigned short index : v)
		{
			vertices[index].normal_ = normal;
		}
	}
}

void Mesh::Draw(UINT mateRPIndex, UINT texRPIndex)
{
	// �}�e���A��
	mtrl_.SetDrawCommand(mateRPIndex, texRPIndex);

	// ���_�o�b�t�@�𑗂� + �`��R�}���h
	vtIdx_.Draw();
}
