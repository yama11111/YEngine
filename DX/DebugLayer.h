#pragma once
#include <d3d12.h>

#pragma comment(lib, "d3d12.lib")

namespace DX 
{
	class DebugLayer
	{
	public:
		void Enable(const bool isValidate);
		void Severity();
	};
}