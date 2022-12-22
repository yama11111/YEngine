#pragma once
#include "PipelineSet.h"
#include "TextureManager.h"
#include "Vec3.h"

namespace YGame
{
	class BillboardCommon
	{
	public:
		// ���_�f�[�^
		struct VData
		{
			YMath::Vec3 pos_; // xyz���W
		};
	protected:
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

