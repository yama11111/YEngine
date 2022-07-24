#pragma once
#include <dxgi1_6.h>

#pragma comment(lib, "dxgi.lib")

class DXAdapter
{
private:
	// �����ɓ���̖��O�����A�_�v�^�[�I�u�W�F�N�g������
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

