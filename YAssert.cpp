#include "YAssert.h"
#include <cassert>

bool Result(const HRESULT& result)
{
	assert(SUCCEEDED(result));
	if (FAILED(result)) return false;
	return true;
}

void Assert(const bool test)
{
	assert(test);
}

bool IsFailed(const HRESULT& result)
{
	if (FAILED(result)) return true;
	return false;
}
