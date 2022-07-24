#pragma once
#include <d3d12.h>

#pragma comment(lib, "d3d12.lib")

class DXDebugLayer
{
private:
	ID3D12Debug1* debugController = nullptr;
public:
	void Enable(const bool isValidate);
	void Severity();
};
