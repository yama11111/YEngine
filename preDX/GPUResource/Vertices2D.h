#pragma once
#include "Vertices.h"
#include <vector>

namespace DX
{
	namespace GPUResource
	{
		// 頂点データ構造体
		struct VertexData2D
		{
			Math::Vec3 pos;	 // xyz座標
			Math::Vec2 uv;	 // uv座標
		};

		class Vertices2D : public Vertices
		{
		public:
			std::vector<VertexData2D> v; // 頂点データ
		public:
			Vertices2D();
			Vertices2D(const std::vector<VertexData2D> v);
			void Initialize() override;
			void Draw() override;
		};
	}
}

