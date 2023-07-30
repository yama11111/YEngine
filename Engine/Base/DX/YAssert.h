#pragma once
#include <d3d12.h>
#include <cassert>

namespace YDX
{
	// 成功チェック
	bool Result(const HRESULT& result);
	// failed -> true
	bool IsFailed(const HRESULT& result);
}
