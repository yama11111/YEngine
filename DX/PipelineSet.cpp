#include "PipelineSet.h"
#include "VertexLayoutManager.h"
#include <assert.h>

using DX::PipelineSet;
using DX::PipelineState;

ID3D12GraphicsCommandList* PipelineSet::pCmdList = nullptr;

void PipelineSet::StaticInit(ID3D12GraphicsCommandList* pCommandList)
{
	assert(pCommandList != nullptr);
	pCmdList = pCommandList;
}

void PipelineSet::Create(const int dimension)
{
	VertexLayoutManager* layout = VertexLayoutManager::GetInstance();

	switch (dimension)
	{
	case PipelineState::Dimension::Two:
		shdrs.Load2D();
		rootSig.Create(shdrs.errorBlob);
		pplnState.Create(rootSig.Get(), shdrs, layout->spriteIL, PipelineState::Dimension::Two);
		d = PipelineState::Dimension::Two;
		break;
	case PipelineState::Dimension::Three:
		shdrs.Load3D();
		rootSig.Create(shdrs.errorBlob);
		pplnState.Create(rootSig.Get(), shdrs, layout->modelIL, PipelineState::Dimension::Three);
		d = PipelineState::Dimension::Three;
		break;
	default:
		assert(false);
		break;
	}
}

void PipelineSet::SetCommand()
{
	// パイプラインステートの設定コマンド
	pCmdList->SetPipelineState(pplnState.Get());

	// ルートシグネチャの設定コマンド
	pCmdList->SetGraphicsRootSignature(rootSig.Get());
	switch (d)
	{
	case PipelineState::Dimension::Two:
		// プリミティブ形状の設定コマンド
		pCmdList->IASetPrimitiveTopology(
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); // 三角形ストリップ
		break;
	case PipelineState::Dimension::Three:
		// プリミティブ形状の設定コマンド
		pCmdList->IASetPrimitiveTopology(
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト
		break;
	}
}
