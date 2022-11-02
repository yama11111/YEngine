#pragma once
#include "RootSignature.h"
#include "PipelineState.h"
#include <d3d12.h>

#pragma comment(lib, "d3d12.lib")

namespace DX
{
	class PipelineSet
	{
	public:
		ShaderSet shdrs;
		RootSignature rootSig;
		PipelineState pplnState;
		int d = 0;
		static ID3D12GraphicsCommandList* pCmdList;
	public:
		void Create(const int dimension);
		void SetCommand();
	public:
		static void StaticInit(ID3D12GraphicsCommandList* pCommandList);
	};
}
