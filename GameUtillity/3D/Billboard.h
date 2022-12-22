#pragma once
#include "Vertices.h"
#include "PipelineSet.h"
#include "Object.h"
#include "ViewProjection.h"
#include "TextureManager.h"

namespace YGame
{
	class Billboard
	{
	public:
		// ���_�f�[�^
		struct VData
		{
			YMath::Vec3 pos_; // xyz���W
		};
	private:
		// ���_�f�[�^
		YDX::Vertices<VData> vt_;
		// Y���r���{�[�h
		bool isAxisY_ = false;
		
		// ��\��
		bool isInvisible_ = false;

		// �萔�o�b�t�@(�r���{�[�h)
		YDX::ConstBuffer<YDX::BillboardCBData> cbBlbd_;
	public:
		// ����
		static Billboard* Create(const bool isYAxisBillboard);
	public:
		// �`��
		void Draw(Object& obj, const ViewProjection& vp, const UINT tex);
	private:
		// �R���X�g���N�^
		Billboard() = default;
	private:
		// �p�C�v���C���ݒ�
		static YDX::PipelineSet pplnSet_;
		// �ÓI�e�N�X�`���}�l�[�W���[�|�C���^
		static TextureManager* pTexManager_;
	public:
		// �ÓI������
		static void StaticInitialize(TextureManager* pTexManager, std::vector<D3D12_ROOT_PARAMETER>* rootParams);
		// �ÓI�`��R�}���h
		static void StaticSetDrawCommand();
	};
}
