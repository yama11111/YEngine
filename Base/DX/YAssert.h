#pragma once
#include <d3d12.h>
#include <cassert>

#pragma comment(lib, "d3d12.lib")

namespace DX
{
	// �����`�F�b�N
	bool Result(const HRESULT& result);
	// failed -> true
	bool IsFailed(const HRESULT& result);
}
