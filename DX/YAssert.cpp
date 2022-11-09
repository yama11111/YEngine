#include "YAssert.h"

bool DX::Result(const HRESULT& result)
{
	assert(SUCCEEDED(result));
	if (FAILED(result)) return false;
	return true;
}

bool DX::IsFailed(const HRESULT& result)
{
	if (FAILED(result)) return true;
	return false;
}
