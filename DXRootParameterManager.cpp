#include "DXRootParameterManager.h"

int DXRootParameterManager::PushBackCBV()
{
	// �萔�o�b�t�@
	D3D12_ROOT_PARAMETER rootParam{};
	rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;  // �萔�o�b�t�@�r���[
	rootParam.Descriptor.ShaderRegister = cbvNum;             // �萔�o�b�t�@�ԍ�
	rootParam.Descriptor.RegisterSpace = 0;                   // �f�t�H���g�l
	rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // �S�ẴV�F�[�_���猩����

	int result = cbvNum;

	rp.push_back(rootParam);
	cbvNum++;

	return result;
}

void DXRootParameterManager::PushBackDescTable(
	const D3D12_DESCRIPTOR_RANGE& descriptorRange)
{
	// �e�N�X�`�����W�X�^
	D3D12_ROOT_PARAMETER rootParam{};
	rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParam.DescriptorTable.pDescriptorRanges = &descriptorRange;
	rootParam.DescriptorTable.NumDescriptorRanges = 1;              // �f�t�H���g�l
	rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;		// �S�ẴV�F�[�_���猩����

	rp.push_back(rootParam);
}

DXRootParameterManager* DXRootParameterManager::GetInstance()
{
	static DXRootParameterManager instance;
	return &instance;
}
