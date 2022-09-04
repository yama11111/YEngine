#pragma once
#include "ShaderManager.h"
#include "Device.h"
#include <vector>

namespace DX
{
	class PipelineState
	{
	public:
		// �p�C�v�����X�e�[�g
		ID3D12PipelineState* pplnState = nullptr;
		// �O���t�B�b�N�X�p�C�v���C���ݒ�
		D3D12_GRAPHICS_PIPELINE_STATE_DESC desc{};
		// �u�����h�X�e�[�g
		D3D12_RENDER_TARGET_BLEND_DESC& blendDesc;
		static Device* dev;
	public:
		PipelineState();
		void Create2D(ID3D12RootSignature* rootSignature, ShaderManager& shaderM,
			std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout);
		void Create3D(ID3D12RootSignature* rootSignature, ShaderManager& shaderM,
			std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout);
		void ChangeSolid();
		void ChangeWire();
		void SetBlendAdd();
		void SetBlendSub();
		void SetBlendInversion();
		void SetBlendAlpha();
	private:
		void InitDesc(ID3D12RootSignature* rootSignature, ShaderManager& shaderM, 
			std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout);
		void CreateState();
	public:
		static void StaticInit();
	};
}
