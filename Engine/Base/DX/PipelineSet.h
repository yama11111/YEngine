#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <vector>

#pragma comment(lib, "d3d12.lib")

namespace YDX
{
	class PipelineSet
	{

	private:

		// ���[�g�V�O�l�`��
		Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature_ = nullptr;

		// �p�C�v�����X�e�[�g
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState_ = nullptr;

		// �v���~�e�B�u�`��
		D3D_PRIMITIVE_TOPOLOGY primitive_ = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="samplerDescs"> : �e�N�X�`���T���v���[</param>
		/// <param name="rootParams"> : ���[�g�p�����[�^</param>
		/// <param name="pipelineDesc"> : �p�C�v���C���ݒ�</param>
		/// <param name="primitive"> : �v���~�e�B�u�`��</param>
		void Initialize(
			const std::vector<D3D12_STATIC_SAMPLER_DESC>& samplerDescs,
			const std::vector<D3D12_ROOT_PARAMETER>& rootParams,
			D3D12_GRAPHICS_PIPELINE_STATE_DESC& pipelineDesc,
			const D3D_PRIMITIVE_TOPOLOGY& primitive);

		/// <summary>
		/// �`��O�R�}���h
		/// </summary>
		void SetDrawCommand();

	private:

		/// <summary>
		/// ���[�g�V�O�l�`������
		/// </summary>
		/// <param name="rootParams"> : ���[�g�p�����[�^</param>
		/// <param name="samplerDescs"> : �e�N�X�`���T���v���[</param>
		void CreateRootSignature(
			const std::vector<D3D12_ROOT_PARAMETER>& rootParams,
			const std::vector<D3D12_STATIC_SAMPLER_DESC>& samplerDescs);

		/// <summary>
		/// �p�C�v���C���X�e�[�g����
		/// </summary>
		/// <param name="pipelineDesc"> : �p�C�v���C���ݒ�</param>
		void CreatePipelineState(D3D12_GRAPHICS_PIPELINE_STATE_DESC& pipelineDesc);

		/// <summary>
		/// �v���~�e�B�u�`��̐ݒ�
		/// </summary>
		/// <param name="primitive"> : �v���~�e�B�u�`��</param>
		void SetPrimitiveTopology(const D3D_PRIMITIVE_TOPOLOGY& primitive);

	private:

		// �ÓI�f�o�C�X�|�C���^
		static ID3D12Device* spDevice_;

		// �ÓI�R�}���h���X�g�|�C���^
		static ID3D12GraphicsCommandList* spCmdList_;

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		/// <param name="pDevice"> : �f�o�C�X�|�C���^</param>
		/// <param name="pCommandList"> : �R�}���h���X�g�|�C���^</param>
		static void StaticInitialize(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCommandList);

	};
}
