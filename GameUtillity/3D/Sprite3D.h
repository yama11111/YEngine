#pragma once
#include "Sprite3DCommon.h"
#include "Vertices.h"
#include "Object.h"
#include "ViewProjection.h"
#include "Color.h"

namespace YGame
{
	// ���f���p�I�u�W�F�N�g
	using ObjectSprite3D = Object<Sprite3DCommon::CBData>;

	class Sprite3D : private Sprite3DCommon
	{
	private:
		// ���_�f�[�^
		YDX::Vertices<VData> vt_;
		// �F
		std::unique_ptr<Color> defColor_;

		// X���r���{�[�h
		bool isXAxisBillboard_ = false;
		// Y���r���{�[�h
		bool isYAxisBillboard_ = false;
		
		// �e�N�X�`��
		UINT tex_ = UINT32_MAX;

		// ��\��
		bool isInvisible_ = false;
	public:
		struct Status 
		{
			bool isXAxisBillboard_ = false;
			bool isYAxisBillboard_ = false;
		};
	public:
		// ����
		static Sprite3D* Create(const Status& state, const UINT texIndex = UINT32_MAX);
	public:
		// �`��
		void Draw(ObjectSprite3D* obj, const ViewProjection& vp, Color* color, const UINT tex);
		// �`��
		void Draw(ObjectSprite3D* obj, const ViewProjection& vp, const UINT tex);
		// �`��
		void Draw(ObjectSprite3D* obj, const ViewProjection& vp, Color* color);
		// �`��
		void Draw(ObjectSprite3D* obj, const ViewProjection& vp);
	private:
		YMath::Mat4 BillboardMatrix(const ViewProjection& vp);
	private:
		Sprite3D() = default;
	public:
		~Sprite3D() = default;
	};
}
