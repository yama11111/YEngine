#pragma once
#include <d3d12.h>
#pragma comment(lib, "d3d12.lib")

namespace DX
{
	// 成功チェック
	bool Result(const HRESULT& result);
	// false -> 警告
	void Assert(const bool test);
	// failed -> true
	bool IsFailed(const HRESULT& result);
}
