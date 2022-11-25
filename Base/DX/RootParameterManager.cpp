#include "RootParameterManager.h"

using DX::RootParameterManager;

UINT RootParameterManager::PushBackCBV()
{
	// 定数バッファ
	D3D12_ROOT_PARAMETER rootParam{};
	rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;  // 定数バッファビュー
	rootParam.Descriptor.ShaderRegister = cbvIndex_;		  // 定数バッファ番号
	rootParam.Descriptor.RegisterSpace = 0;					  // デフォルト値
	rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // 全てのシェーダから見える

	cbvIndex_++;
	rps_.push_back(rootParam);

	return static_cast<UINT>(rps_.size() - 1);
}

UINT RootParameterManager::PushBackTR()
{
	// デスクリプタレンジの設定
	descriptorRange_.NumDescriptors = 1; // 1度の描画に使うテクスチャが1枚なので1
	descriptorRange_.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange_.BaseShaderRegister = 0; // テクスチャレジスタ0番
	descriptorRange_.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	// テクスチャレジスタ
	D3D12_ROOT_PARAMETER rootParam{};
	rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParam.DescriptorTable.pDescriptorRanges = &descriptorRange_;
	rootParam.DescriptorTable.NumDescriptorRanges = 1;
	rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // 全てのシェーダから見える

	rps_.push_back(rootParam);

	return static_cast<UINT>(rps_.size() - 1);
}

UINT RootParameterManager::PushBackDescriptorTable(const D3D12_DESCRIPTOR_RANGE& descriptorRange)
{
	// テクスチャレジスタ
	D3D12_ROOT_PARAMETER rootParam{};
	rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParam.DescriptorTable.pDescriptorRanges = &descriptorRange;
	rootParam.DescriptorTable.NumDescriptorRanges = 1;
	rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // 全てのシェーダから見える

	rps_.push_back(rootParam);

	return static_cast<UINT>(rps_.size() - 1);
}