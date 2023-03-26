#include "ModelCommon.h"
#include "FileUtillity.h"
#include <memory>
#include <cassert>
#include <fstream>
#include <sstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#pragma region ���O���

using YGame::ModelObjectCommon;
using YGame::ModelCommon;
using YDX::PipelineSet;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;

#pragma endregion


#pragma region ModelCBSetCommon

std::unique_ptr<YGame::ViewProjection> ModelObjectCommon::sDefVP_ = nullptr;
std::unique_ptr<YGame::LightGroup> ModelObjectCommon::sDefLightGroup_ = nullptr;
std::unique_ptr<YGame::Color> ModelObjectCommon::sDefColor_ = nullptr;

void ModelObjectCommon::StaticInitialize()
{
	// ����
	sDefVP_.reset(new YGame::ViewProjection());
	sDefVP_->Initialize({});

	sDefLightGroup_.reset(LightGroup::Create());

	sDefColor_.reset(Color::Create());
}

#pragma endregion


#pragma region ModelCommon

PipelineSet ModelCommon::sPipelineSet_;

void ModelCommon::StaticInitialize()
{
	// �p�C�v���C��������
	std::unique_ptr<PipelineSet::IStatus> pplnState = std::make_unique<PipelineSetStatus>();
	sPipelineSet_.Initialize(pplnState.get());
}

void ModelCommon::ShaderSet::Load(ID3DBlob* errorBlob)
{
	ID3DBlob* vs = nullptr;
	ID3DBlob* ps = nullptr;

	// ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	LoadShader(L"Resources/Shaders/ModelVS.hlsl", "main", "vs_5_0", vs, errorBlob);
	// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	LoadShader(L"Resources/Shaders/ModelPS.hlsl", "main", "ps_5_0", ps, errorBlob);

	vsBlob_ = vs;
	psBlob_ = ps;
}

void ModelCommon::PipelineSetStatus::Initialize(ID3DBlob* errorBlob_)
{
	// �V�F�[�_�[�ǂݍ���
	ShaderSet shdrs;
	shdrs.Load(errorBlob_);

	// ���_���C�A�E�g�̐ݒ�
	inputLayout_ =
	{
		// ���_���W	 (x, y, z)
		{
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		// �@��		 (x, y, z)
		{
			"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		// UV���W	 (x, y)
		{
			"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		// �ڋ�_	 (x, y, z)
		{
			"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		// ���_�F	 (x, y, z, w)
		{
			"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		}
	};

	// �e�N�X�`���T���v���[�̐ݒ�
	{
		D3D12_STATIC_SAMPLER_DESC sampleDesc{};
		sampleDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // ���܂�Ԃ�   (�^�C�����O)
		sampleDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // �c�܂�Ԃ�   (�^�C�����O)
		sampleDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // ���s�܂�Ԃ� (�^�C�����O)
		sampleDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK; // �{�[�_�[�̎��͍�
		sampleDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;   // �S�ă��j�A���
		sampleDesc.MaxLOD = D3D12_FLOAT32_MAX; // �~�j�}�b�v�ő�l
		sampleDesc.MinLOD = 0.0f;              // �~�j�}�b�v�ŏ��l
		sampleDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
		sampleDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // �s�N�Z���V�F�[�_�[����̂ݎg�p�\

		sampleDesc_.push_back(sampleDesc);
	}

	// ���[�g�p�����[�^�̐ݒ�
	{
		size_t rpIdxCBNum = static_cast<size_t> (RootParameterIndex::TexDT);

		for (size_t i = 0; i < rpIdxCBNum; i++)
		{
			// �萔�o�b�t�@
			D3D12_ROOT_PARAMETER rootParam{};
			rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;  // �萔�o�b�t�@�r���[
			rootParam.Descriptor.ShaderRegister = static_cast<UINT>(i); // �萔�o�b�t�@�ԍ�
			rootParam.Descriptor.RegisterSpace = 0;					  // �f�t�H���g�l
			rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // �S�ẴV�F�[�_���猩����

			rootParams_.push_back(rootParam);
		}

		// �f�X�N���v�^�����W�̐ݒ�
		descriptorRange_.NumDescriptors = 1; // 1�x�̕`��Ɏg���e�N�X�`����1���Ȃ̂�1
		descriptorRange_.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		descriptorRange_.BaseShaderRegister = 0; // �e�N�X�`�����W�X�^0��
		descriptorRange_.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

		// �e�N�X�`�����W�X�^
		D3D12_ROOT_PARAMETER rootParam{};
		rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		rootParam.DescriptorTable.pDescriptorRanges = &descriptorRange_;
		rootParam.DescriptorTable.NumDescriptorRanges = 1;
		rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // �S�ẴV�F�[�_���猩����

		rootParams_.push_back(rootParam);
	}

	// �p�C�v���C���ݒ�
	{
		// �V�F�[�_�[�̐ݒ�
		pipelineDesc_.VS.pShaderBytecode = shdrs.vsBlob_.Get()->GetBufferPointer();
		pipelineDesc_.VS.BytecodeLength = shdrs.vsBlob_.Get()->GetBufferSize();
		pipelineDesc_.PS.pShaderBytecode = shdrs.psBlob_.Get()->GetBufferPointer();
		pipelineDesc_.PS.BytecodeLength = shdrs.psBlob_.Get()->GetBufferSize();

		// ���X�^���C�U�̐ݒ�
		pipelineDesc_.RasterizerState.CullMode = D3D12_CULL_MODE_BACK; // �w�ʂ��J�����O

		// �f�v�X�X�e���V���X�e�[�g�̐ݒ�
		pipelineDesc_.DepthStencilState.DepthEnable = true; // �[�x�e�X�g
		pipelineDesc_.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL; // �������݋���
		pipelineDesc_.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS; // ��������΍��i
		pipelineDesc_.DSVFormat = DXGI_FORMAT_D32_FLOAT; // �[�x�t�H�[�}�b�g

		// �}�`�̌`��ݒ�
		pipelineDesc_.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	}

	// �v���~�e�B�u�`��̐ݒ�
	primitive_ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST; // �O�p�`���X�g
}

void ModelCommon::CalculateNormals(std::vector<VData>& v, const std::vector<uint16_t> indices)
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
void ModelCommon::CalculateSmoothedVertexNormals(std::vector<VData>& vertices,
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
YDX::VertexIndex<ModelCommon::VData> ModelCommon::LoadVertices(const aiMesh* src, bool invU, bool invV, bool isNormalized)
{
	// �߂�l�p
	YDX::VertexIndex<VData> vtIdx;

	// �ۑ��p
	aiVector3D zero3D(0.0f, 0.0f, 0.0f);
	aiColor4D zeroColor(0.0f, 0.0f, 0.0f, 0.0f);

	std::vector<VData> vData;
	std::vector<uint16_t> indices;

	// ���T�C�Y(���_�̐�����)
	vData.resize(src->mNumVertices);

	// ���_�̐�
	for (size_t i = 0; i < src->mNumVertices; ++i)
	{
		// �ǂݍ���(���)
		aiVector3D* position = &(src->mVertices[i]);
		aiVector3D* normal = &(src->mNormals[i]);
		aiVector3D* uv = (src->HasTextureCoords(0)) ? &(src->mTextureCoords[0][i]) : &zero3D;
		aiVector3D* tangent = (src->HasTangentsAndBitangents()) ? &(src->mTangents[i]) : &zero3D;
		aiColor4D* color = (src->HasVertexColors(0)) ? &(src->mColors[0][i]) : &zeroColor;

		if (invU) { uv->x = 1.0f - uv->x; }
		if (invV) { uv->y = 1.0f - uv->y; }

		VData vertex = {};
		vertex.pos_ = Vector3(position->x, position->y, position->z);
		vertex.normal_ = Vector3(normal->x, normal->y, normal->z);
		vertex.uv_ = Vector2(uv->x, uv->y);
		vertex.tangent_ = Vector3(tangent->x, tangent->y, tangent->z);
		vertex.color_ = Vector4(color->r, color->g, color->b, color->a);

		vData[i] = vertex;
	}

	// ���T�C�Y(�C���f�b�N�X�̐�����)
	indices.resize(src->mNumFaces * static_cast<size_t>(3));

	// �C���f�b�N�X�̐�
	for (size_t i = 0; i < src->mNumFaces; ++i)
	{
		// �ǂݍ���(���)
		const aiFace& face = src->mFaces[i];

		indices[i * 3 + 0] = face.mIndices[0];
		indices[i * 3 + 1] = face.mIndices[1];
		indices[i * 3 + 2] = face.mIndices[2];
	}

	// �@���v�Z
	if (isNormalized) { CalculateNormals(vData, indices); }

	// ���_�C���f�b�N�X������(���)
	vtIdx.Initialize(vData, indices);

	// ���_�C���f�b�N�X��Ԃ�
	return vtIdx;
}

void ModelCommon::StaticSetDrawCommand()
{
	// �p�C�v���C�����Z�b�g
	sPipelineSet_.SetDrawCommand();
}

#pragma endregion