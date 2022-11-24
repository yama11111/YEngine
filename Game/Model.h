#pragma once
#include "Vertices.h"
#include "Material.h"
#include "PipelineSet.h"
#include "Object.h"
#include "ViewProjection.h"

namespace Game
{
	class Model
	{
	private:
		// ���_�C���f�b�N�X
		DX::VertexIndex3D vtIdx_;
		// �}�e���A��
		Material mtrl_;
	public:
		// ���I�|�C���^(������)
		static Model* Create();
		// ���f���ǂݍ���
		static Model* Load(const std::string& modelName);
	public:
		// �`��
		void Draw(Object& obj, ViewProjection& vp, const UINT tex);
		void Draw(Object& obj, ViewProjection& vp);
	private:
		// �R���X�g���N�^
		Model() = default;
	private:
		// �p�C�v���C���ݒ�
		static DX::PipelineSet pplnSet_;
	public:
		// �ÓI������
		static void StaticInitialize(std::vector<D3D12_ROOT_PARAMETER>* rootParams);
		// �ÓI�`��R�}���h
		static void StaticSetDrawCommand();
	};
}
