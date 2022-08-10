#pragma once
#include "DXResource.h"
#include "DXCommandList.h"
#include "Vec4.h"

struct ConstBufferDataMaterial
{
	Vec4 color;
};

class ConstBuffer
{
public:
	ConstBufferDataMaterial* cMapMate = nullptr;
private:
	DXResourceInfo cbInfo;
	DXResource cbMate;
	UINT index = 0;
	DXCommandList* cmdList = nullptr;
public:
	ConstBuffer();
	void Init();
	void SetCommand();
};
