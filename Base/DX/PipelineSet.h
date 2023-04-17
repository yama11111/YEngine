#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <vector>

#pragma comment(lib, "d3d12.lib")

namespace YDX
{
	class PipelineSet
	{
	public:
		// �ݒ�\���̃C���^�[�t�F�[�X
		struct IStatus
		{
		public:
			// ���_���C�A�E�g
			std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout_;
			// �e�N�X�`���T���v���[
			std::vector<D3D12_STATIC_SAMPLER_DESC> sampleDesc_;
			// ���[�g�p�����[�^
			std::vector<D3D12_ROOT_PARAMETER> rootParams_;
			// �f�X�N���v�^�����W
			D3D12_DESCRIPTOR_RANGE descriptorRange_{};
			// �p�C�v���C���ݒ�
			D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc_{};
			// �v���~�e�B�u�`��
			D3D_PRIMITIVE_TOPOLOGY primitive_ = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
		public:
			virtual void Initialize(ID3DBlob* errorBlob_) = 0;
		public:
			IStatus() = default;
			virtual ~IStatus() = default;
		};
	private:
		// ���[�g�V�O�l�`��
		Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature_ = nullptr;
		// �p�C�v�����X�e�[�g
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState_ = nullptr;
		// �v���~�e�B�u�`��
		D3D_PRIMITIVE_TOPOLOGY primitive_ = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
	public:
		// ������
		void Initialize(IStatus* state);
		// �`��O�R�}���h
		void SetDrawCommand();
	private:
		// �ÓI�f�o�C�X�|�C���^
		static ID3D12Device* pDevice_;
		// �ÓI�R�}���h���X�g�|�C���^
		static ID3D12GraphicsCommandList* pCmdList_;
	public:
		// �ÓI������
		static void StaticInitialize(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCommandList);
	};
}
