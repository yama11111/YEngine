#pragma once
#include "Vertices.h"
#include <vector>

namespace DX
{
	namespace GPUResource
	{
		// ���_�f�[�^�\����
		struct VertexData2D
		{
			Math::Vec3 pos;	 // xyz���W
			Math::Vec2 uv;	 // uv���W
		};

		class Vertices2D : public Vertices
		{
		public:
			std::vector<VertexData2D> v; // ���_�f�[�^
		public:
			Vertices2D();
			Vertices2D(const std::vector<VertexData2D> v);
			void Initialize() override;
			void Draw() override;
		};
	}
}

