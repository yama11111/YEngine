#pragma once
#include <d3d12.h>
#pragma comment(lib, "d3d12.lib")

namespace DX
{
	namespace Utility
	{
		class Result
		{
		public:
			static bool Check(const HRESULT& result);
			// false -> Œx
			static void Assert(const bool test);
			// failed -> true
			static bool IsFailed(const HRESULT& result);
		};
	}
}
