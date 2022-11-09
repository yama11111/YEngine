#pragma once
#include "Transform.h"
#include "ViewProjection.h"
#include "Vertices.h"
#include "PipelineSet.h"
#include "TextureManager.h"

namespace Object
{
	class Model
	{
	private:
		// ���_�C���f�b�N�X
		DX::VertexIndex3D vtIdx;
	public:
		// �R���X�g���N�^
		Model();
		// �`��
		void Draw(Transform& trfm, ViewProjection& vp, const UINT tex);
	private:
		// �p�C�v���C���ݒ�
		static DX::PipelineSet pplnSet_;
		// �ÓI�e�N�X�`���}�l�[�W���[�|�C���^
		static TextureManager* pTexManager_;
	public:
		// �ÓI������
		static void StaticInitialize(TextureManager* pTexManager, std::vector<D3D12_ROOT_PARAMETER>* rootParams);
		// �ÓI�`��R�}���h
		static void StaticSetDrawCommand();
	};
}
