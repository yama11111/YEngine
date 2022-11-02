#pragma once
#include "Vertices3D.h"

namespace DX
{
	namespace GPUResource
	{
		class VertexIndex
		{
		public:
			Vertices3D vert; // 頂点
			std::vector<uint16_t> idx; // インデックスデータ
			Utility::Resource buffer; // インデックスバッファ
			D3D12_INDEX_BUFFER_VIEW view{}; // インデックスバッファビュー
		public:
			VertexIndex();
			VertexIndex(const std::vector<VertexData3D> v, const std::vector<uint16_t> i);
			void SetCommand();
			void Draw();
			void Initialize(const bool normalized);
		private:
			void CalcNormal();
		};
	}
}
