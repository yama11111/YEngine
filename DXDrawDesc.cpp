#include "DXDrawDesc.h"
#include "Def.h"

void DXDrawDesc::Create()
{
	shdrM.Load();
	rootSig.Create(shdrM.errorBlob);
	pplnState.Create(rootSig.rootSignature, shdrM, layout.inputLayout);
	viewport.Set({ WIN_SIZE });
	scissorRect.Set({ { 0, 0 }, WIN_SIZE });

	cmdList = DXCommandList::GetInstance();
}

void DXDrawDesc::SetCommand()
{
	// ビューポート設定コマンドを、コマンドリストに積む
	viewport.Stack();
	// シザー矩形設定コマンドを、コマンドリストに積む
	scissorRect.Stack();

	// パイプラインステートの設定コマンド
	cmdList->List()->SetPipelineState(pplnState.pipelineState);

	// ルートシグネチャの設定コマンド
	cmdList->List()->SetGraphicsRootSignature(rootSig.rootSignature);

	// プリミティブ形状の設定コマンド
	cmdList->List()->IASetPrimitiveTopology(
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト
}
