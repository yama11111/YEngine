#include "YAssert.h"
#include <cassert>

bool DX::Result(const HRESULT& result)
{
	assert(SUCCEEDED(result));
	if (FAILED(result)) return false;
	return true;
}

void DX::Assert(const bool test)
{
	assert(test);
}

bool DX::IsFailed(const HRESULT& result)
{
	if (FAILED(result)) return true;
	return false;
}
