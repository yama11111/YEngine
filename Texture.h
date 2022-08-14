#pragma once
#include "Vec4.h"
#include "DXResource.h"
#include "DXSRVHeap.h"

class Texture
{
public:
	DXResourceInfo texInfo;
	DXResource texBuff;
private:
	int index = 0;
	DXSRVHeap* srvH = nullptr;
public:
	void Create(const Vec4& color = { 1.0f,1.0f,1.0f,1.0f });
	void SetCommand();
};

