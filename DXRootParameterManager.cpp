#include "DXRootParameterManager.h"

int DXRootParameterManager::PushBackCBV()
{
	// 定数バッファ
	D3D12_ROOT_PARAMETER rootParam{};
	rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;  // 定数バッファビュー
	rootParam.Descriptor.ShaderRegister = cbvNum;             // 定数バッファ番号
	rootParam.Descriptor.RegisterSpace = 0;                   // デフォルト値
	rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // 全てのシェーダから見える

	int result = cbvNum;

	rp.push_back(rootParam);
	cbvNum++;

	return result;
}

void DXRootParameterManager::PushBackDescTable(
	const D3D12_DESCRIPTOR_RANGE& descriptorRange)
{
	// テクスチャレジスタ
	D3D12_ROOT_PARAMETER rootParam{};
	rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParam.DescriptorTable.pDescriptorRanges = &descriptorRange;
	rootParam.DescriptorTable.NumDescriptorRanges = 1;              // デフォルト値
	rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;		// 全てのシェーダから見える

	rp.push_back(rootParam);
}

DXRootParameterManager* DXRootParameterManager::GetInstance()
{
	static DXRootParameterManager instance;
	return &instance;
}
