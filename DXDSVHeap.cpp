#include "DXDSVHeap.h"
#include "DXDevice.h"
#include "Result.h"
#include "Def.h"

void DXDSVHeap::Create()
{
	DXResourceInfo2 depthInfo{};
	depthInfo.resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthInfo.resDesc.Width = WIN_SIZE.x; // レンダーターゲットに合わせる
	depthInfo.resDesc.Height = WIN_SIZE.y; // レンダーターゲットに合わせる
	depthInfo.resDesc.DepthOrArraySize = 1;
	depthInfo.resDesc.Format = DXGI_FORMAT_D32_FLOAT; // 深度値フォーマット
	depthInfo.resDesc.SampleDesc.Count = 1;
	depthInfo.resDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL; // デプスステンシル

	// 深度値用ヒーププロパティ
	depthInfo.heapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
	// 深度値のクリア設定
	depthInfo.clearValue.DepthStencil.Depth = 1.0f; // 深度値1.0f(最大値)でクリア
	depthInfo.clearValue.Format = DXGI_FORMAT_D32_FLOAT; // 深度値フォーマット

	// リソース生成
	depthBuff.Create(depthInfo);

	// 深度ビュー用デスクリプターヒープ作成
	dsvHeap.hDesc.NumDescriptors = 1; // 深度ビューは1つ
	dsvHeap.hDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV; // デプスステンシルビュー
	dsvHeap.Create();

	// 深度ビュー作成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT; // 深度値フォーマット
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;

	DXDevice* dev = DXDevice::GetInstance();
	dev->Device()->CreateDepthStencilView(
		depthBuff.buff,
		&dsvDesc,
		dsvHeap.heap->GetCPUDescriptorHandleForHeapStart());
}
