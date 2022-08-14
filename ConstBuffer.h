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
	UINT index = 0;
private:
	DXResourceInfo cbInfo;
	DXResource cbMate;
	DXCommandList* cmdList = nullptr;
public:
	ConstBuffer();
	void Create(const Vec4& color);
	void SetCommand();
};
