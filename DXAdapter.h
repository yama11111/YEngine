#pragma once
#include <dxgi1_6.h>

#pragma comment(lib, "dxgi.lib")

class DXAdapter
{
private:
	// ここに特定の名前を持つアダプターオブジェクトが入る
	IDXGIAdapter4* tmpAdapter = nullptr;
public:
	void Selection(IDXGIFactory7* dxgiFactory);
	IDXGIAdapter4* Template();
public:
	static DXAdapter* GetInstance();
private:
	DXAdapter() = default;
	~DXAdapter() = default;
	DXAdapter(const DXAdapter&) = delete;
	const DXAdapter& operator=(const DXAdapter&) = delete;
};

