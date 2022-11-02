#pragma once
#include "Vertices.h"
#include <vector>

namespace DX
{
	namespace GPUResource
	{
		// ���_�f�[�^�\����
		struct VertexData3D
		{
			Math::Vec3 pos;	 // xyz���W
			Math::Vec3 normal; // �@���x�N�g��
			Math::Vec2 uv;	 // uv���W
		};

		class Vertices3D : public Vertices
		{
		public:
			std::vector<VertexData3D> v; // ���_�f�[�^
			Utility::ResourceInfo info; // ���_���
		public:
			Vertices3D();
			Vertices3D(const std::vector<VertexData3D> v);
			void Initialize() override;
			void Draw() override;
		};
	}
}

