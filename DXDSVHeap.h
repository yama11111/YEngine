#pragma once
#include "DXResource.h"
#include "DXDescriptorHeap.h"

class DXDSVHeap
{
public:
	DXResource depthBuff;
	DXDescriptorHeap dsvHeap;
public:
	void Create();
};

