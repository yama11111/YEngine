#pragma once
#include "Transform.h"
#include "MatProjection.h"
#include "Vertices.h"
#include "TextureManager.h"

namespace Object
{
	class Sprite
	{
	public:
		// �T�C�Y
		const Math::Vec2 size_;
	private:
		// ���_�f�[�^
		DX::Vertices<DX::SpriteVData> vt_;
	public:
		// �R���X�g���N�^
		Sprite(const Math::Vec2& size);
		// �`��
		void Draw(Transform& trfm, const UINT tex);
	private:
		// �ÓI�ˉe�ϊ��s��(���s���e)
		static Math::MatProjection mp_;
		// �ÓI�e�N�X�`���}�l�[�W���[�|�C���^
		static DX::TextureManager* pTexManager_;
	public:
		// �ÓI������
		static void StaticInitialize(DX::TextureManager* pTexManager);
	};
}
