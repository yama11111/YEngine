#include "Mesh.h"
#include "FileUtillity.h"
#include <cassert>
#include <fstream>
#include <sstream>

#pragma region ���O���

using YGame::Mesh;
using YGame::Texture;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;
using YMath::Matrix4;

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
	instance->pTex_ = Texture::Load("white1x1.png", false);

	// �C���X�^���X��Ԃ�
	return instance;
}

Mesh* Mesh::CreateCube(const std::string& texFileName)
{
	// ����
	Mesh* instance = CreateCube();

	// �}�e���A��������
	instance->pTex_ = Texture::Load(texFileName, true);

	// �C���X�^���X��Ԃ�
	return instance;
}

Mesh* Mesh::LoadObj(const std::string& directoryPath, const std::string& objFileName, const bool isSmoothing)
{
	// �C���X�^���X���� (���I)
	Mesh* instance = new Mesh();


	// ���_
	std::vector<VData> v;
	
	// �C���f�b�N�X
	std::vector<uint16_t> i;
	
	// ���_�@���X���[�V���O�p�f�[�^
	std::unordered_map<unsigned short, std::vector<unsigned short>> sd;
	
	// �e�N�X�`��
	Texture* pTex = nullptr;


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
			pTex = LoadMaterial(directoryPath, mtlFileName);
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
	
	// �e�N�X�`�����
	instance->pTex_ = pTex;


	// �C���X�^���X��Ԃ�
	return instance;
}

Mesh* Mesh::LoadFbx(const std::string& folderPath, FbxNode* fbxNode, const bool isSmoothing)
{
	// �C���X�^���X���� (���I)
	Mesh* instance = new Mesh();


	// ���_
	std::vector<VData> v;
	
	// �C���f�b�N�X
	std::vector<uint16_t> i;
	
	// ���_�@���X���[�V���O�p�f�[�^
	std::unordered_map<unsigned short, std::vector<unsigned short>> sd;
	
	// �e�N�X�`��
	Texture* pTex = nullptr;


	// �m�[�h�̃��b�V�����擾
	FbxMesh* fbxMesh = fbxNode->GetMesh();


	// ���_�ǂݎ��
	FbxLoader::ParseMeshVertices(v, fbxMesh);

	// �ʂ��\������f�[�^�̓ǂݎ��
	FbxLoader::ParseMeshFaces(v, i, fbxMesh);

	// �}�e���A���̓ǂݎ��
	FbxLoader::ParseMaterial(folderPath, pTex, fbxNode);


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
	
	// �e�N�X�`�����
	instance->pTex_ = pTex;


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

Texture* Mesh::LoadMaterial(const std::string& directoryPath, const std::string& fileName)
{
	// �߂�l�p
	Texture* pTex = nullptr;

	// �t�@�C���X�g���[��
	std::ifstream file;
	// .mtl�t�@�C�����J��
	file.open(directoryPath + fileName);
	// �t�@�C���I�[�v�����s���`�F�b�N
	assert(file);
	
	// 1�s���ǂݍ���
	std::string line;
	while (std::getline(file, line))
	{
		// 1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		std::istringstream lineStream(line);

		// ���p�X�y�[�X��؂�ōs�̐擪��������擾
		std::string key;
		std::getline(lineStream, key, ' ');

		// �擪�̃^�u�����͖�������
		if (key[0] == '\t') { key.erase(key.begin()); }

		//// �擪������ "newmtl" �Ȃ�}�e���A����
		//if (key == "newmtl")
		//{
		//	// �ǂݍ���
		//	lineStream >> m.name_;
		//}
		//// �擪������ "Ka" �Ȃ�A���r�G���g�F
		//if (key == "Ka")
		//{
		//	// �ǂݍ���
		//	lineStream >> m.ambient_.x_;
		//	lineStream >> m.ambient_.y_;
		//	lineStream >> m.ambient_.z_;
		//}
		//// �擪������ "Kd" �Ȃ�f�B�t���[�Y�F
		//if (key == "Kd")
		//{
		//	// �ǂݍ���
		//	lineStream >> m.diffuse_.x_;
		//	lineStream >> m.diffuse_.y_;
		//	lineStream >> m.diffuse_.z_;
		//}
		//// �擪������ "vn" �Ȃ�X�y�L�����[�F
		//if (key == "Ks")
		//{
		//	// �ǂݍ���
		//	lineStream >> m.specular_.x_;
		//	lineStream >> m.specular_.y_;
		//	lineStream >> m.specular_.z_;
		//}

		// �擪������ "map_Kd" �Ȃ�e�N�X�`���t�@�C����
		if (key == "map_Kd")
		{
			//// �ǂݍ���
			//lineStream >> m.texFileName_;
			
			// �e�N�X�`���t�@�C�����擾
			std::string texFileName;
			lineStream >> texFileName;
			
			// �ǂݍ���
			pTex = Texture::Load(directoryPath, texFileName);
		}
	}

	// �t�@�C�������
	file.close();

	// �e�N�X�`����Ԃ�
	return pTex;
}

void Mesh::Draw(const UINT texRPIndex)
{
	// �e�N�X�`��
	pTex_->SetDrawCommand(texRPIndex);

	// ���_�o�b�t�@�𑗂� + �`��R�}���h
	vtIdx_.Draw();
}


#pragma region FbxLoader

void Mesh::FbxLoader::ParseMeshVertices(std::vector<VData>& vertices, FbxMesh* fbxMesh)
{
	// ���_���W�f�[�^��
	const int controlPointsCount = fbxMesh->GetControlPointsCount();

	// �K�v���������_�f�[�^�z����m��
	VData vData{};
	vertices.resize(controlPointsCount, vData);


	// FBX���b�V���̒��_���W�z����擾
	FbxVector4* pCoord = fbxMesh->GetControlPoints();

	// FBX���b�V���̑S���_���W�𒸓_�z��ɃR�s�[����
	for (int i = 0; i < controlPointsCount; i++)
	{
		// ���_�ǂݍ���
		VData& refVertex = vertices[i];

		// ���W�R�s�[
		refVertex.pos_.x_ = static_cast<float>(pCoord[i][0]);
		refVertex.pos_.y_ = static_cast<float>(pCoord[i][1]);
		refVertex.pos_.z_ = static_cast<float>(pCoord[i][2]);
	}
}

void Mesh::FbxLoader::ParseMeshFaces(std::vector<VData>& vertices, std::vector<uint16_t>& indices, FbxMesh* fbxMesh)
{
	// �������b�V���̃��f���͔�Ή�
	assert(indices.size() == 0);

	// �ʂ̐�
	const int polygonCount = fbxMesh->GetPolygonCount();

	// UV�f�[�^�̐�
	const int textureUVCount = fbxMesh->GetTextureUVCount();

	// UV�����X�g
	FbxStringList uvNames;
	fbxMesh->GetUVSetNames(uvNames);


	// �ʂ��Ƃ̏��ǂݎ��
	for (int i = 0; i < polygonCount; i++)
	{
		// �ʂ��\�����钸�_�̐����擾 (3�Ȃ�O�p�|���S��)
		const int polygonSize = fbxMesh->GetPolygonSize(i);

		// 5�ȏ�͒e��
		assert(polygonSize <= 4);

		// 1���_������
		for (int j = 0; j < polygonSize; j++)
		{
			// FBX���_�z��̃C���f�b�N�X
			int index = fbxMesh->GetPolygonVertex(i, j);

			// 0�ȉ��͒e��
			assert(index >= 0);

			// ���_�ǂݍ���
			VData& refVertex = vertices[index];

			// �@���ǂݍ���
			FbxVector4 normal;
			if (fbxMesh->GetPolygonVertexNormal(i, j, normal))
			{
				// ���
				refVertex.normal_.x_ = static_cast<float>(normal[0]);
				refVertex.normal_.y_ = static_cast<float>(normal[1]);
				refVertex.normal_.z_ = static_cast<float>(normal[2]);
			}

			// �e�N�X�`��UV�ǂݍ���
			if (textureUVCount > 0)
			{
				FbxVector2 uvs;
				bool lUnmapedUV = false;

				// 0�Ԍ��ߑł��œǂݍ���
				if (fbxMesh->GetPolygonVertexUV(i, j, uvNames[0], uvs, lUnmapedUV))
				{
					refVertex.uv_.x_ = static_cast<float>(uvs[0]);
					refVertex.uv_.y_ = static_cast<float>(uvs[1]);
				}

				// �C���f�b�N�X�z��ɒ��_�C���f�b�N�X�ǉ�
				// 3���_�ڂ܂łȂ�
				if (j < 3)
				{
					// 1�_�ǉ����A����2�_�ƎO�p�`���\�z����
					indices.push_back(index);
				}
				// 4���_��
				else
				{
					// 3�_�ǉ����A
					// �l�p�`�� 0,1,2,3 �̓� 2,3,0 �ŎO�p�`���\�z����
					int index2 = indices[indices.size() - 1];
					int index3 = index;
					int index0 = indices[indices.size() - 3];
					indices.push_back(index2);
					indices.push_back(index3);
					indices.push_back(index0);
				}
			}
		}
	}
}

void Mesh::FbxLoader::ParseMaterial(const std::string& folderPath, Texture*& refPtrTex, FbxNode* fbxNode)
{
	// �}�e���A����
	const int materialCount = fbxNode->GetMaterialCount();

	// �}�e���A��������Ȃ�
	if (materialCount > 0)
	{
		// �擪�̃}�e���A�����擾
		FbxSurfaceMaterial* pMaterial = fbxNode->GetMaterial(0);

		// �e�N�X�`����ǂݍ��񂾂�
		bool texLoaded = false;

		// �}�e���A��������Ȃ�
		if (pMaterial)
		{
			// FbxSurfaceLambert�N���X���ǂ������ׂ�
			if (pMaterial->GetClassId().Is(FbxSurfaceLambert::ClassId))
			{
				//// �ϊ�
				//FbxSurfaceLambert* pLambert = static_cast<FbxSurfaceLambert*>(pMaterial);

				//// �����W��
				//FbxPropertyT<FbxDouble3> ambient = pLambert->Ambient;
				//pModel->ambient.x_ = static_cast<float>(ambient.Get()[0]);
				//pModel->ambient.y_ = static_cast<float>(ambient.Get()[1]);
				//pModel->ambient.z_ = static_cast<float>(ambient.Get()[2]);

				//// �g�U���ˌ��W��
				//FbxPropertyT<FbxDouble3> diffuse = pLambert->Diffuse;
				//pModel->diffuse.x_ = static_cast<float>(diffuse.Get()[0]);
				//pModel->diffuse.y_ = static_cast<float>(diffuse.Get()[1]);
				//pModel->diffuse.z_ = static_cast<float>(diffuse.Get()[2]);
			}

			// �f�B�t���[�Y�e�N�X�`�������o��
			const FbxProperty diffuseProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);

			// �f�B�t���[�Y�e�N�X�`�����L���Ȃ�
			if (diffuseProperty.IsValid())
			{
				// �e�N�X�`���擾
				const FbxFileTexture* pTexture = diffuseProperty.GetSrcObject<FbxFileTexture>();

				// �e�N�X�`��������Ȃ�
				if (pTexture)
				{
					// �e�N�X�`���t�@�C���p�X
					const std::string texFilePath = pTexture->GetFileName();

					// �e�N�X�`���t�@�C�����擾
					const std::string texFileName = YUtil::FilePath(texFilePath);

					// �e�N�X�`���ǂݍ���
					refPtrTex = Texture::Load(folderPath, texFileName);

					// ����
					texLoaded = true;
				}
			}
		}

		// �e�N�X�`����ǂݍ���ł��Ȃ��Ȃ�
		if (!texLoaded)
		{
			// �f�t�H���g�e�N�X�`���ǂݍ���
			refPtrTex = Texture::Load("white1x1.png");
		}
	}
}

Matrix4 Mesh::FbxLoader::ConvertFromFbxAMatrixToMatrix4(const FbxAMatrix& fbxMat)
{
	Matrix4 result{};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m_[i][j] = static_cast<float>(fbxMat.Get(i, j));
		}
	}

	return result;
}

#pragma endregion