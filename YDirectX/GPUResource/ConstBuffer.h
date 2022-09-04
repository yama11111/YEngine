#pragma once
#include "../Utility/Resource.h"
#include "../../Math/Vec4.h"
#include "../../Math/Mat4.h"

namespace DX
{
	namespace GPUResource
	{
		// �萔�o�b�t�@�p�f�[�^�\���� (�}�e���A��)
		struct ConstBufferDataMaterial
		{
			Vec4 color; // �F (RGBA)
		};
		// �萔�o�b�t�@�p�f�[�^�\���� (3D�ϊ��s��)
		struct ConstBufferDataTransform
		{
			Mat4 mat; // 3D�ϊ��s��
		};

		class ConstBuffer
		{
		public:
			Utility::Resource cbMate;
		};

		class ConstBufferMaterial : public ConstBuffer
		{
		public:
			ConstBufferDataMaterial* cMapMate = nullptr;
		public:
			void Color(const Vec4& color);
		};

		class ConstBufferTransform : public ConstBuffer
		{
		public:
			ConstBufferDataTransform* cMapTrfm = nullptr;
		public:
			void Mat(const Mat4& mat);
		};
	}
}