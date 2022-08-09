#pragma once
#include "DXShaderManager.h"
#include "DXDevice.h"
#include <vector>

class DXPipelineState
{
public:
	// パイプランステート
	ID3D12PipelineState* pipelineState = nullptr;
	// グラフィックスパイプライン設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};
	// ブレンドステート
	D3D12_RENDER_TARGET_BLEND_DESC& blendDesc;

	DXDevice* dev = nullptr;
public:
	DXPipelineState();
	void Create(ID3D12RootSignature* rootSignature, DXShaderManager& shaderM,
		std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout);
	void ChangeSolid();
	void ChangeWire();
	void SetBlendAdd();
	void SetBlendSub();
	void SetBlendInversion();
	void SetBlendAlpha();
private:
	void CreateState();
};

