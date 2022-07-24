#include "DXResult.h"
#include <cassert>

bool Result::Check(const HRESULT& result)
{
	assert(SUCCEEDED(result));
	if (FAILED(result)) return false;
	return true;
}

void Result::Assert(const bool test)
{
	assert(test);
}

bool Result::IsFailed(const HRESULT& result)
{
	if (FAILED(result)) return true;
	return false;
}
