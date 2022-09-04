#pragma once
#include "ConstBuffer.h"
#include <d3d12.h>

#pragma comment(lib, "d3d12.lib")

namespace DX 
{
	namespace GPUResource
	{
		class ConstBufferManager
		{
		private:
			UINT indexM = 0;
			UINT indexT = 0;
			static ID3D12GraphicsCommandList* pCmdList;
		public:
			void CreateCB(ConstBufferMaterial& cb, const Math::Vec4& color = { 1.0f,1.0f,1.0f,1.0f });
			void CreateCB(ConstBufferTransform& cb);
			void SetCommand(ConstBufferMaterial& cb);
			void SetCommand(ConstBufferTransform& cb);
		private:
			Utility::ResourceInfo CBInfo();
		public:
			static void StaticInit(ID3D12GraphicsCommandList* pCommandList);
			static ConstBufferManager* GetInstance();
		private:
			ConstBufferManager();
			~ConstBufferManager() = default;
			ConstBufferManager(const ConstBufferManager&) = delete;
			const ConstBufferManager& operator=(const ConstBufferManager&) = delete;
		};
	}
}
