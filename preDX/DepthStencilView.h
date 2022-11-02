#pragma once
#include "Utility/Resource.h"
#include "Utility/DescriptorHeap.h"

namespace DX
{
	class DepthStencilView
	{
	private:
		Utility::Resource buff;
		Utility::DescriptorHeap dsv;
	public:
		void Create();
		Utility::DescriptorHeap Get();
	};
}
