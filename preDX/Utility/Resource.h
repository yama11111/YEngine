#pragma once
#include "ResourceInfo.h"
#include <wrl.h>

namespace DX
{
	namespace Utility
	{
		class Resource
		{
		private:
			Microsoft::WRL::ComPtr<ID3D12Resource> buffer = nullptr; // バッファ
		public:
			void Create(const ResourceInfo& rscInfo);
			void Create(const ResourceInfo2& rscInfo);
			ID3D12Resource* Get();
		};
	}
}
