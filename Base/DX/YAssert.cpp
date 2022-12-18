#include "YAssert.h"

bool YDX::Result(const HRESULT& result)
{
	assert(SUCCEEDED(result));
	if (FAILED(result)) return false;
	return true;
}

bool YDX::IsFailed(const HRESULT& result)
{
	if (FAILED(result)) return true;
	return false;
}
