#pragma once
#include "DXVertexLayoutManager.h"
#include "DXRootSignature.h"
#include "DXPipelineState.h"
#include "DXCommandList.h"

class DXPipelineSet
{
public:
	DXShaderManager shdrM;
	DXRootSignature rootSig;
	DXPipelineState pplnState;
	DXCommandList* cmdList = nullptr;
public:
	void Create2D();
	void Create3D();
	void SetCommand2D();
	void SetCommand3D();
};

