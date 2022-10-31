#pragma once
#include <d3d12.h>
#pragma comment(lib, "d3d12.lib")

bool Result(const HRESULT& result);
// false -> Œx
void Assert(const bool test);
// failed -> true
bool IsFailed(const HRESULT& result);

