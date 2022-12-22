#pragma once
#include "BillboardCommon.h"
#include "Vertices.h"
#include "Object.h"
#include "ViewProjection.h"

namespace YGame
{
	class Billboard : private BillboardCommon
	{
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
	};
}
