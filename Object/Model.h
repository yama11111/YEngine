#pragma once
#include "Transform.h"
#include "ViewProjection.h"
#include "Vertices.h"
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
		// �ÓI�e�N�X�`���}�l�[�W���[�|�C���^
		static DX::TextureManager* pTexManager_;
	public:
		// �ÓI������
		static void StaticInitialize(DX::TextureManager* pTexManager);
	};
}
