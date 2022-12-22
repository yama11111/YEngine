#pragma once
#include "Vec2.h"
#include "Vec3.h"
#include "Mat4.h"
#include "PipelineSet.h"
#include "TextureManager.h"

namespace YGame
{
	class SpriteCommon
	{
	public:
		// ���_�f�[�^�\����
		struct VData
		{
			YMath::Vec3 pos_; // xyz���W
			YMath::Vec2 uv_;  // uv���W
		};
	protected:
		// �ÓI�ˉe�ϊ��s��(���s���e)
		static YMath::Mat4 projection_;
		// �p�C�v���C���ݒ�
		static YDX::PipelineSet pplnSet_;
		// �ÓI�e�N�X�`���}�l�[�W���[�|�C���^
		static TextureManager* pTexManager_;
	public:
		// �ÓI�������X�e�[�^�X
		struct StaticInitStatus
		{
			// �e�N�X�`���}�l�[�W���[�|�C���^
			TextureManager* pTexManager_;
			// ���[�g�p�����[�^�|�C���^
			std::vector<D3D12_ROOT_PARAMETER>* rootParams_;
		};
	public:
		// �ÓI������
		static void StaticInitialize(const StaticInitStatus& state);
		// �ÓI�`��R�}���h
		static void StaticSetDrawCommand();
	};
}
