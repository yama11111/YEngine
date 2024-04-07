/**
 * @file YAssert.h
 * @brief DirectX用警告関数
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

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
