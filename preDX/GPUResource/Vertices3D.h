#pragma once
#include "Vertices.h"
#include <vector>

namespace DX
{
	namespace GPUResource
	{
		// 頂点データ構造体
		struct VertexData3D
		{
			Math::Vec3 pos;	 // xyz座標
			Math::Vec3 normal; // 法線ベクトル
			Math::Vec2 uv;	 // uv座標
		};

		class Vertices3D : public Vertices
		{
		public:
			std::vector<VertexData3D> v; // 頂点データ
			Utility::ResourceInfo info; // 頂点情報
		public:
			Vertices3D();
			Vertices3D(const std::vector<VertexData3D> v);
			void Initialize() override;
			void Draw() override;
		};
	}
}

