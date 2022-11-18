#pragma once
#include "Transform.h"
#include "ViewProjection.h"
#include "Vertices.h"
#include "PipelineSet.h"
#include "TextureManager.h"
#include "Material.h"

namespace Game
{
	class Model
	{
	private:
		// ���_�C���f�b�N�X
		DX::VertexIndex3D vtIdx_;
		// �}�e���A��
		Material mtrl_;
		// �萔�o�b�t�@(�}�e���A��2)
		DX::ConstBuffer<DX::MaterialData2> cbMtrl_;
	public:
		// ���I�|�C���^(������)
		static Model* Create();
		// ���f���ǂݍ���
		static Model* Load(const char* fileName);
	public:
		// �`��
		void Draw(Transform& trfm, ViewProjection& vp, const UINT tex);
	private:
		// �R���X�g���N�^
		Model() = default;
	private:
		// �p�C�v���C���ݒ�
		static DX::PipelineSet pplnSet_;
		// �ÓI�萔�o�b�t�@�}�l�[�W���[�|�C���^
		static DX::ConstBufferManager* pCBManager_;
		// �ÓI�e�N�X�`���}�l�[�W���[�|�C���^
		static TextureManager* pTexManager_;
	public:
		// �ÓI�������\����
		struct StaticInitState
		{
			DX::ConstBufferManager* pCBManage;
			TextureManager* pTexManager;
			std::vector<D3D12_ROOT_PARAMETER>* rootParams;
		};
	public:
		// �ÓI������
		static void StaticInitialize(const StaticInitState& state);
		// �ÓI�`��R�}���h
		static void StaticSetDrawCommand();
	};
}
