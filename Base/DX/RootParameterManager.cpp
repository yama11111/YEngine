#include "RootParameterManager.h"

using DX::RootParameterManager;

UINT RootParameterManager::PushBackCBV()
{
	// �萔�o�b�t�@
	D3D12_ROOT_PARAMETER rootParam{};
	rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;  // �萔�o�b�t�@�r���[
	rootParam.Descriptor.ShaderRegister = cbvIndex_;		  // �萔�o�b�t�@�ԍ�
	rootParam.Descriptor.RegisterSpace = 0;					  // �f�t�H���g�l
	rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // �S�ẴV�F�[�_���猩����

	cbvIndex_++;
	rps_.push_back(rootParam);

	return static_cast<UINT>(rps_.size() - 1);
}

UINT RootParameterManager::PushBackTR()
{
	// �f�X�N���v�^�����W�̐ݒ�
	descriptorRange_.NumDescriptors = 1; // 1�x�̕`��Ɏg���e�N�X�`����1���Ȃ̂�1
	descriptorRange_.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange_.BaseShaderRegister = 0; // �e�N�X�`�����W�X�^0��
	descriptorRange_.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	// �e�N�X�`�����W�X�^
	D3D12_ROOT_PARAMETER rootParam{};
	rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParam.DescriptorTable.pDescriptorRanges = &descriptorRange_;
	rootParam.DescriptorTable.NumDescriptorRanges = 1;
	rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // �S�ẴV�F�[�_���猩����

	rps_.push_back(rootParam);

	return static_cast<UINT>(rps_.size() - 1);
}

UINT RootParameterManager::PushBackDescriptorTable(const D3D12_DESCRIPTOR_RANGE& descriptorRange)
{
	// �e�N�X�`�����W�X�^
	D3D12_ROOT_PARAMETER rootParam{};
	rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParam.DescriptorTable.pDescriptorRanges = &descriptorRange;
	rootParam.DescriptorTable.NumDescriptorRanges = 1;
	rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // �S�ẴV�F�[�_���猩����

	rps_.push_back(rootParam);

	return static_cast<UINT>(rps_.size() - 1);
}