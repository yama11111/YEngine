#pragma once
#include <d3d12.h>
#pragma comment(lib, "d3d12.lib")

namespace DX
{
	// �����`�F�b�N
	bool Result(const HRESULT& result);
	// false -> �x��
	void Assert(const bool test);
	// failed -> true
	bool IsFailed(const HRESULT& result);
}
