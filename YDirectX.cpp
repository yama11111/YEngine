#include "YDirectX.h"
#include "DXAdapter.h"
#include "Result.h"

int YDirectX::Init(const HWND& hwnd)
{
	// デバッグレイヤーを有効に
	debugLayer.Enable(true);

	// DXGIファクトリー生成
	Result::Check(CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory)));

	DXAdapter* adpt = DXAdapter::GetInstance();
	adpt->Selection(dxgiFactory);

	// デバイス生成
	dev = DXDevice::GetInstance();
	if (!dev->Create()) return -1;
	Result::Assert(dev->Device() != nullptr);

	// エラー時止まるように
	debugLayer.Severity();

	// コマンドリスト生成
	cmdList = DXCommandList::GetInstance();
	cmdList->Create();

	// コマンドキュー生成
	cmdQue.Create();

	// スワップチェーン生成
	swpChain.Init();
	swpChain.Create(dxgiFactory, cmdQue.Queue(), hwnd);

	// レンダーターゲットビュー生成
	rtv.Create(swpChain.SwapChain(), swpChain.Desc());

	// フェンス生成
	fence.Create();

	return 0;
}

int YDirectX::PreDraw()
{
	// バックバッファの番号を取得(2つなので0番か1番)
	UINT bbIndex = swpChain.SwapChain()->GetCurrentBackBufferIndex();
	// 1.リソースバリアで書き込み可能に変更
	rscBarrier.SetCurrentBackBuffer(rtv.BackBaffer(bbIndex)); // バックバッファを指定
	rscBarrier.ChangeState(rscBarrier.RenderTarget); // 描画状態へ

	// 2.描画先の変更
	DXDescriptorHeap _rtv = rtv.RenderTargetView();
	// レンダーターゲットビューのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = _rtv.heap->GetCPUDescriptorHandleForHeapStart();
	rtvHandle.ptr += bbIndex * dev->Device()->GetDescriptorHandleIncrementSize(_rtv.hDesc.Type);
	cmdList->List()->OMSetRenderTargets(1, &rtvHandle, false, nullptr);

	// 3.画面クリア {R, G, B, A}
	cmdList->CrearRTV(rtvHandle); // 青っぽい色

	return 0;
}

int YDirectX::PostDraw()
{
	// 5.リソースバリアを戻す
	rscBarrier.ChangeState(rscBarrier.Present); // 表示状態へ

	// 命令のクローズ
	Result::Check(cmdList->List()->Close());

	// コマンドリスト実行
	ID3D12CommandList* commandLists[] = { cmdList->List() };
	cmdQue.Queue()->ExecuteCommandLists(1, commandLists);

	// 画面に表示するバッファをフリップ(裏表の入替え)
	Result::Check(swpChain.SwapChain()->Present(1, 0));

	// コマンドの実行完了を待つ
	fence.ConfirmCommandComplate(cmdQue.Queue());

	// キューをクリア + 再びコマンドリストを貯める準備
	cmdList->ClearAndPrepare();

	return 0;
}

YDirectX* YDirectX::GetInstance()
{
	static YDirectX instance;
	return &instance;
}

