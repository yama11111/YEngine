#pragma once
#include "DXViewport.h"
#include "DXScissorRect.h"

class DXDrawDesc
{
public:
	DXViewport viewport;
	DXScissorRect scissorRect;
public:
	void Set();
	void SetCommand();
};

