#pragma once
#include "Utility/Resource.h"
#include "Vec4.h"
#include "Mat4.h"

namespace DX
{
	namespace GPUResource
	{
		// �萔�o�b�t�@�p�f�[�^�\���� (�}�e���A��)
		struct ConstBufferDataMaterial
		{
			Math::Vec4 color; // �F (RGBA)
		};
		// �萔�o�b�t�@�p�f�[�^�\���� (3D�ϊ��s��)
		struct ConstBufferDataTransform
		{
			Math::Mat4 mat; // 3D�ϊ��s��
		};

		class ConstBuffer
		{
		public:
			Utility::Resource mate;
		};

		class ConstBufferMaterial : public ConstBuffer
		{
		public:
			ConstBufferDataMaterial* mapMate = nullptr;
		public:
			void Color(const Math::Vec4& color);
		};

		class ConstBufferTransform : public ConstBuffer
		{
		public:
			ConstBufferDataTransform* mapTrfm = nullptr;
		public:
			void Mat(const Math::Mat4& mat);
		};
	}
}