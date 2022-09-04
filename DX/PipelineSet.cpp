#include "PipelineSet.h"
#include "VertexLayoutManager.h"
#include <assert.h>

using DX::PipelineSet;

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
	case Two:
		shdrM.Load2D();
		rootSig.Create(shdrM.errorBlob);
		pplnState.Create2D(rootSig.Get(), shdrM, layout->spriteIL);
		d = Two;
		break;
	case Three:
		shdrM.Load3D();
		rootSig.Create(shdrM.errorBlob);
		pplnState.Create3D(rootSig.Get(), shdrM, layout->modelIL);
		d = Three;
		break;
	default:
		assert(false);
		break;
	}
}

void PipelineSet::SetCommand()
{
	// パイプラインステートの設定コマンド
	pCmdList->SetPipelineState(pplnState.pplnState);

	// ルートシグネチャの設定コマンド
	pCmdList->SetGraphicsRootSignature(rootSig.Get());
	switch (d)
	{
	case Two:
		// プリミティブ形状の設定コマンド
		pCmdList->IASetPrimitiveTopology(
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); // 三角形ストリップ
		break;
	case Three:
		// プリミティブ形状の設定コマンド
		pCmdList->IASetPrimitiveTopology(
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト
		break;
	}
}
