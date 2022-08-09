#pragma once
#include "DXVertexLayoutManager.h"
#include "DXRootSignature.h"
#include "DXPipelineState.h"
#include "DXViewport.h"
#include "DXScissorRect.h"

class DXDrawDesc
{
public:
	DXShaderManager shdrM;
	DXVertexLayoutManager layout;

	DXRootSignature rootSig;
	DXPipelineState pplnState;

	DXViewport viewport;
	DXScissorRect scissorRect;

	DXCommandList* cmdList = nullptr;
public:
	void Create();
	void SetCommand();
};

