#include "DXPipelineSet.h"

void DXPipelineSet::Create2D()
{
	cmdList = DXCommandList::GetInstance();
	DXVertexLayoutManager* layout = DXVertexLayoutManager::GetInstance();

	shdrM.Load2D();
	rootSig.Create(shdrM.errorBlob);
	pplnState.Create2D(rootSig.rootSignature, shdrM, layout->spriteIL);
}

void DXPipelineSet::Create3D()
{
	cmdList = DXCommandList::GetInstance();
	DXVertexLayoutManager* layout = DXVertexLayoutManager::GetInstance();

	shdrM.Load3D();
	rootSig.Create(shdrM.errorBlob);
	pplnState.Create3D(rootSig.rootSignature, shdrM, layout->modelIL);
}

void DXPipelineSet::SetCommand2D()
{
	// パイプラインステートの設定コマンド
	cmdList->List()->SetPipelineState(pplnState.pipelineState);

	// ルートシグネチャの設定コマンド
	cmdList->List()->SetGraphicsRootSignature(rootSig.rootSignature);

	// プリミティブ形状の設定コマンド
	cmdList->List()->IASetPrimitiveTopology(
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); // 三角形ストリップ
}

void DXPipelineSet::SetCommand3D()
{
	// パイプラインステートの設定コマンド
	cmdList->List()->SetPipelineState(pplnState.pipelineState);

	// ルートシグネチャの設定コマンド
	cmdList->List()->SetGraphicsRootSignature(rootSig.rootSignature);

	// プリミティブ形状の設定コマンド
	cmdList->List()->IASetPrimitiveTopology(
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト
}
