#include "Pipeline.h"
#include "YAssert.h"

using YGame::Pipeline;
using YGame::BaseConstBuffer;
using YDX::Result;

ID3D12Device* Pipeline::spDevice_ = nullptr;
ID3D12GraphicsCommandList* Pipeline::spCmdList_ = nullptr;

void Pipeline::EnqueueDrawSet(const size_t priority, const DrawSet& drawSet)
{
	assert(priority < drawQueue_.size());
	drawQueue_[priority].push(drawSet);
}

void Pipeline::Draw()
{
	// �p�C�v���C���ݒ�
	spCmdList_->SetPipelineState(pipelineState_.Get());

	spCmdList_->SetGraphicsRootSignature(rootSignature_.Get());

	spCmdList_->IASetPrimitiveTopology(primitive_);

	for (size_t i = 0; i < drawQueue_.size(); i++)
	{
		// �t������
		size_t irev = (drawQueue_.size() - 1) - i;
		
		if (drawQueue_[irev].empty()) { continue; }
		
		// �ォ�珇�ɕ`��
		while (true)
		{
			if (drawQueue_[irev].empty()) { break; }

			// �萔�o�b�t�@
			ConstBufferPtrSet* pCBPtrSet = drawQueue_[irev].front().pCBPtrSet;

			for (auto itr = cbRPIndices_.begin(); itr != cbRPIndices_.end(); ++itr)
			{
				pCBPtrSet->SetDrawCommand(itr->first, itr->second);
			}

			// �O���t�B�b�N
			BaseGraphic* pGraphic = drawQueue_[irev].front().pGraphic;

			assert(pGraphic);

			pGraphic->SetDrawCommand(graphicRPIndices_);

			drawQueue_[irev].pop();
		}
	}
}

Pipeline* Pipeline::Create(
	ShaderSet& shaderSet,
	const std::vector<std::string>& constBufferKeys,
	const std::vector<std::string>& graphicRPKeys,
	const uint32_t textureNum,
	const PipelineSetting& pipelineSetting,
	const BlendState& blendState,
	const UINT renderTargetNum)
{
	// �V�K�p�C�v���C��
	Pipeline* newPipeline = new Pipeline();
	
	// �萔�o�b�t�@���[�g�p�����[�^�ԍ�
	for (size_t i = 0; i < constBufferKeys.size(); i++)
	{
		std::string key = constBufferKeys[i];

		uint32_t index = static_cast<uint32_t>(i);

		newPipeline->cbRPIndices_.insert({ key, index });
	}
	
	const size_t cbRPIdxSize = constBufferKeys.size();

	// �O���t�B�b�N�p���[�g�p�����[�^�ԍ�
	for (size_t i = 0; i < graphicRPKeys.size(); i++)
	{
		std::string key = graphicRPKeys[i];

		uint32_t index = static_cast<uint32_t>(i + cbRPIdxSize);

		newPipeline->graphicRPIndices_.insert({ key, index });
	}

#pragma region ���[�g�p�����[�^�̐ݒ�

	// ���[�g�p�����[�^
	std::vector<D3D12_ROOT_PARAMETER> rootParams;

	// �K�p���̃������̈���m��
	size_t rpNum = constBufferKeys.size() + graphicRPKeys.size();
	rootParams.reserve(rpNum);


	// �萔�o�b�t�@�� = �S�� - �e�N�X�`������
	size_t cbNum = static_cast<size_t>(rpNum - textureNum);
	
	// �萔�o�b�t�@
	for (size_t i = 0; i < cbNum; i++)
	{
		D3D12_ROOT_PARAMETER rootParam{};
		rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;  // �萔�o�b�t�@�r���[
		rootParam.Descriptor.ShaderRegister = static_cast<UINT>(i); // �萔�o�b�t�@�ԍ�
		rootParam.Descriptor.RegisterSpace = 0;					  // �f�t�H���g�l
		rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // �S�ẴV�F�[�_���猩����

		rootParams.push_back(rootParam);
	}


	// �f�X�N���v�^�����W
	std::vector<D3D12_DESCRIPTOR_RANGE> descriptorRanges{};

	descriptorRanges.reserve(textureNum);
	
	// �e�N�X�`�����W�X�^
	for (size_t i = 0; i < textureNum; i++)
	{
		D3D12_DESCRIPTOR_RANGE descriptorRange{};

		// �f�X�N���v�^�����W�̐ݒ�
		descriptorRange.NumDescriptors = 1; // 1�x�̕`��Ɏg���e�N�X�`����1���Ȃ̂�1
		descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		descriptorRange.BaseShaderRegister = static_cast<UINT>(i); // �e�N�X�`�����W�X�^�ԍ�
		descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

		descriptorRanges.push_back(descriptorRange);

		D3D12_ROOT_PARAMETER rootParam{};
		rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		rootParam.DescriptorTable.pDescriptorRanges = &descriptorRanges[i];
		rootParam.DescriptorTable.NumDescriptorRanges = 1;
		rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // �S�ẴV�F�[�_���猩����

		rootParams.push_back(rootParam);
	}

#pragma endregion


#pragma region �p�C�v���C���ݒ�

	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};

	if (ID3DBlob* shader = shaderSet.ShaderPtr(ShaderSet::ShaderType::eVertex))
	{
		pipelineDesc.VS.pShaderBytecode	 = shader->GetBufferPointer();
		pipelineDesc.VS.BytecodeLength	 = shader->GetBufferSize();
	}
	if (ID3DBlob* shader = shaderSet.ShaderPtr(ShaderSet::ShaderType::eGeometry))
	{
		pipelineDesc.GS.pShaderBytecode	 = shader->GetBufferPointer();
		pipelineDesc.GS.BytecodeLength	 = shader->GetBufferSize();
	}
	if (ID3DBlob* shader = shaderSet.ShaderPtr(ShaderSet::ShaderType::ePixel))
	{
		pipelineDesc.PS.pShaderBytecode	 = shader->GetBufferPointer();
		pipelineDesc.PS.BytecodeLength	 = shader->GetBufferSize();
	}

	// �T���v���}�X�N�̐ݒ�
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // �W���ݒ�

	// ���X�^���C�U�̐ݒ�
	pipelineDesc.RasterizerState.FillMode = pipelineSetting.fillMode;
	pipelineDesc.RasterizerState.DepthClipEnable = true; // �[�x�N���b�s���O��L����
	pipelineDesc.RasterizerState.CullMode = pipelineSetting.cullMode;

	// �f�v�X�X�e���V���X�e�[�g�̐ݒ�
	if (pipelineSetting.depthEnable)
	{
		pipelineDesc.DepthStencilState.DepthEnable = true; // �[�x�e�X�g����
		pipelineDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL; // �������݋���
		pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS; // ��������΍��i
		pipelineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT; // �[�x�t�H�[�}�b�g
	}
	else
	{
		pipelineDesc.DepthStencilState.DepthEnable = false; // �[�x�e�X�g���Ȃ�
		pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS; // ��ɏ㏑��
	}

	for (size_t i = 0; i < renderTargetNum; i++)
	{
		// �u�����h�X�e�[�g
		D3D12_RENDER_TARGET_BLEND_DESC& blendDesc = pipelineDesc.BlendState.RenderTarget[i];
		
		blendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // RBGA�S�Ẵ`�����l����`��

		blendDesc.BlendEnable = true;                // �u�����h��L���ɂ���
		blendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD; // ���Z
		blendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;   // �\�[�X�̒l��100%�g��
		blendDesc.DestBlendAlpha = D3D12_BLEND_ZERO; // �f�X�g�̒l��  0%�g��

		// ����������
		blendDesc.BlendOp = D3D12_BLEND_OP_ADD;			 // ���Z
		blendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;      // �\�[�X�̃A���t�@�l
		blendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA; // 1.0f - �\�[�X�̃A���t�@�l
	}

	// �}�`�̌`��ݒ�
	pipelineDesc.PrimitiveTopologyType = pipelineSetting.primitiveType;

	// ���_���C�A�E�g�̐ݒ�
	pipelineDesc.InputLayout.pInputElementDescs = pipelineSetting.inputLayout.data(); // ���_���C�A�E�g�̐擪�A�h���X
	pipelineDesc.InputLayout.NumElements = static_cast<UINT>(pipelineSetting.inputLayout.size()); // ���_���C�A�E�g��

	// ���̑��̐ݒ�
	pipelineDesc.NumRenderTargets = static_cast<UINT>(renderTargetNum); // �`��Ώ�
	for (size_t i = 0; i < renderTargetNum; i++)
	{
		pipelineDesc.RTVFormats[i] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0~255�w���RGBA
	}
	pipelineDesc.SampleDesc.Count = 1; // 1�s�N�Z���ɂ�1��T���v�����O

	// �v���~�e�B�u�`��
	D3D_PRIMITIVE_TOPOLOGY primitive = pipelineSetting.primitive;

#pragma endregion

	newPipeline->CreateRootSignature(rootParams, pipelineSetting.samplerDescs);

	newPipeline->CreatePipelineState(pipelineDesc);

	newPipeline->SetPrimitiveTopology(primitive);

	return newPipeline;
}

void Pipeline::StaticInitialize(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCommandList)
{
	assert(pDevice);
	assert(pCommandList);

	spDevice_ = pDevice;
	spCmdList_ = pCommandList;
}

void Pipeline::CreateRootSignature(
	const std::vector<D3D12_ROOT_PARAMETER>& rootParams, 
	const std::vector<D3D12_STATIC_SAMPLER_DESC>& samplerDescs)
{
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

	// ���[�g�V�O�l�`���̐ݒ�
	D3D12_ROOT_SIGNATURE_DESC rsDesc{};
	rsDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rsDesc.pParameters		 = rootParams.data();
	rsDesc.NumParameters	 = static_cast<UINT>(rootParams.size());
	rsDesc.pStaticSamplers	 = samplerDescs.data();
	rsDesc.NumStaticSamplers = static_cast<UINT>(samplerDescs.size());

	Microsoft::WRL::ComPtr<ID3DBlob> rootSigBlob = nullptr; // ���[�g�V�O�l�`���I�u�W�F�N�g
	Result(D3D12SerializeRootSignature(&rsDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, errorBlob.GetAddressOf()));

	Result(spDevice_->CreateRootSignature(
		0,
		rootSigBlob->GetBufferPointer(),
		rootSigBlob->GetBufferSize(),
		IID_PPV_ARGS(&rootSignature_)));
}

void Pipeline::CreatePipelineState(D3D12_GRAPHICS_PIPELINE_STATE_DESC& pipelineDesc)
{
	// �p�C�v���C���Ƀ��[�g�V�O�l�`�����Z�b�g
	pipelineDesc.pRootSignature = rootSignature_.Get();

	Result(spDevice_->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState_)));
}


void Pipeline::SetPrimitiveTopology(const D3D_PRIMITIVE_TOPOLOGY& primitive)
{
	// ����`�Ȃ�e��
	assert(primitive != D3D_PRIMITIVE_TOPOLOGY_UNDEFINED);

	primitive_ = primitive;
}