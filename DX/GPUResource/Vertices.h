#pragma once
#include <d3d12.h>
#include "Vec2.h"
#include "Vec3.h"
#include "Utility/Resource.h"

#pragma comment(lib, "d3d12.lib")

namespace DX
{
	namespace GPUResource
	{
		class Vertices
		{
		public:
			Utility::Resource buffer; // 頂点バッファ
			D3D12_VERTEX_BUFFER_VIEW view{}; // 頂点バッファビュー
			static ID3D12GraphicsCommandList* pCmdList;
		public:
			virtual void Initialize() = 0;
			virtual void SetCommand();
			virtual void Draw() = 0;
		public:
			static void StaticInit(ID3D12GraphicsCommandList* pCommandList);
		};
	}
}