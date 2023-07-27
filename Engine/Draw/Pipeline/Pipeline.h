#pragma once
#include "ConstBufferPtrSet.h"
#include "BaseGraphic.h"
#include "ShaderSet.h"
#include "PipelineSetting.h"
#include <queue>

namespace YGame
{
	class Pipeline final
	{

	public:

		// �u�����h���
		enum class BlendState
		{
			// �u�����h���Ȃ�
			None,

			// �A���t�@�u�����h
			Alpha,

			// ���Z����
			Add, 
			
			// ���Z����
			Sub,
			
			// �F���]
			Inverse,
		};
	
	public:

		// �`��p�\����
		struct DrawSet
		{
			// �D��x
			uint16_t priority = 0;

			// �萔�o�b�t�@�|�C���^�Z�b�g�|�C���^
			ConstBufferPtrSet* pCBPtrSet = nullptr;
				
			// �O���t�B�b�N�|�C���^
			BaseGraphic* pGraphic = nullptr;
		};

	public:
		
		/// <summary>
		/// ����
		/// </summary>
		/// <param name="shaderSet"> : �V�F�[�_�[</param>
		/// <param name="constBufferKeys"> : �萔�o�b�t�@�L�[�z��</param>
		/// <param name="graphicRPKeys"> : �O���t�B�b�N�p���[�g�p�����[�^�L�[�z��</param>
		/// <param name="textureNum"> : �e�N�X�`������</param>
		/// <param name="pipelineSetting"> : �p�C�v���C���ݒ�</param>
		/// <param name="blendState"> : �u�����h�ݒ�</param>
		/// <param name="renderTargetNum"> : �����_�[�^�[�Q�b�g����</param>
		/// <returns></returns>
		static Pipeline* Create(
			ShaderSet& shaderSet,
			const std::vector<std::string>& constBufferKeys, 
			const std::vector<std::string>& graphicRPKeys,
			const uint32_t textureNum,
			const PipelineSetting& pipelineSetting,
			const BlendState& blendState, 
			const UINT renderTargetNum);

		/// <summary>
		/// �`������L���[�ɐς�
		/// </summary>
		/// <param name="drawSet"> : �`��Z�b�g</param>
		/// <param name="-----------------------------------------"></param>
		/// <param name="(uint16_t) priority"> : �D��x</param>
		/// <param name="(ConstBufferPtrSet*) pCBPtrSet"> : �萔�o�b�t�@�|�C���^�Z�b�g�|�C���^</param>
		/// <param name="(BaseGraphic*) pGraphic"> : �O���t�B�b�N�|�C���^</param>
		void EnqueueDrawSet(const DrawSet& drawSet);

		/// <summary>
		/// �`��
		/// </summary>
		void Draw();

		/// <summary>
		/// �ÓI������
		/// </summary>
		/// <param name="pDevice"> : �f�o�C�X�|�C���^</param>
		/// <param name="pCommandList"> : �R�}���h���X�g�|�C���^</param>
		static void StaticInitialize(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCommandList);

	private:

		// ���[�g�V�O�l�`��
		Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature_ = nullptr;

		// �p�C�v�����X�e�[�g
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState_ = nullptr;

		// �v���~�e�B�u�`��
		D3D_PRIMITIVE_TOPOLOGY primitive_ = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;

		// �萔�o�b�t�@���[�g�p�����[�^�ԍ��i�[�z��
		std::unordered_map<std::string, uint32_t> cbRPIndices_;
		
		// �O���t�B�b�N�p���[�g�p�����[�^�ԍ��i�[�z��
		std::unordered_map<std::string, uint32_t> graphicRPIndices_;

		// �`��p�\���̃L���[
		std::priority_queue<DrawSet> drawSets_;

		// �ÓI�f�o�C�X�|�C���^
		static ID3D12Device* spDevice_;

		// �ÓI�R�}���h���X�g�|�C���^
		static ID3D12GraphicsCommandList* spCmdList_;

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

	};

	// �D�揇�ʕt���p�I�[�o�[���[�h
	bool operator<(const Pipeline::DrawSet& drawSet1, const Pipeline::DrawSet& drawSet2);
	bool operator>(const Pipeline::DrawSet& drawSet1, const Pipeline::DrawSet& drawSet2);
}
