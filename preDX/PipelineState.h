#pragma once
#include "ShaderSet.h"
#include "Device.h"
#include <vector>

namespace DX
{
	class PipelineState
	{
	public:
		enum Dimension
		{
			Two,
			Three,
		};
	public:
		// �p�C�v�����X�e�[�g
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pplnState = nullptr;
		// �O���t�B�b�N�X�p�C�v���C���ݒ�
		D3D12_GRAPHICS_PIPELINE_STATE_DESC desc{};
		// �u�����h�X�e�[�g
		D3D12_RENDER_TARGET_BLEND_DESC& blendDesc;
		static Device* dev;
	public:
		PipelineState();
		void Create(ID3D12RootSignature* rootSignature, ShaderSet& shaders,
			std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout, const int dimension);
		void ChangeSolid();
		void ChangeWire();
		void SetBlendAdd();
		void SetBlendSub();
		void SetBlendInversion();
		void SetBlendAlpha();
		ID3D12PipelineState* Get();
	private:
		void CreateState();
	public:
		static void StaticInit();
	};
}
