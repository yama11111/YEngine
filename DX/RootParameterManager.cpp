#include "RootParameterManager.h"

using DX::RootParameterManager;

RootParameterManager* RootParameterManager::GetInstance()
{
	static RootParameterManager instance;
	return &instance;
}

UINT RootParameterManager::PushBackCBV()
{
	// �萔�o�b�t�@
	D3D12_ROOT_PARAMETER rootParam{};
	rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;  // �萔�o�b�t�@�r���[
	rootParam.Descriptor.ShaderRegister = cbvNum;             // �萔�o�b�t�@�ԍ�
	rootParam.Descriptor.RegisterSpace = 0;                   // �f�t�H���g�l
	rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // �S�ẴV�F�[�_���猩����

	UINT result = index;

	rp.push_back(rootParam);
	index++;
	cbvNum++;

	return result;
}

UINT RootParameterManager::PushBackDescriptorTable(const D3D12_DESCRIPTOR_RANGE& descriptorRange)
{
	// �e�N�X�`�����W�X�^
	D3D12_ROOT_PARAMETER rootParam{};
	rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParam.DescriptorTable.pDescriptorRanges = &descriptorRange;
	rootParam.DescriptorTable.NumDescriptorRanges = 1;
	rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // �S�ẴV�F�[�_���猩����

	UINT result = index;

	rp.push_back(rootParam);
	index++;

	return result;
}
