#include "YDirectX.h"
#include "Adapter.h"
#include "Utility/Result.h"
#include "Def.h"

using DX::YDirectX;
using DX::Utility::Result;

YDirectX* YDirectX::GetInstance()
{
	static YDirectX instance;
	return &instance;
}

bool YDirectX::Initialize(const HWND& hwnd)
{
	// デバッグレイヤーを有効に
	debugLayer.Enable(true);

	// DXGIファクトリー生成
	Result::Check(CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory)));

	Adapter* adpt = Adapter::GetInstance();
	adpt->Selection(dxgiFactory.Get());

	// デバイス生成
	dev = Device::GetInstance();
	if (!dev->Create())
	{
		Result::Assert(false);
		return false;
	}

	// エラー時止まるように
	debugLayer.Severity();

	// コマンドリスト生成
	cmdList.Create();

	// コマンドキュー生成
	cmdQue.Create();

	// スワップチェーン生成
	swpChain.Initialize();
	swpChain.Create(dxgiFactory.Get(), cmdQue.Get(), hwnd);

	// レンダーターゲットビュー生成
	rtv.Create(swpChain.Get(), swpChain.Desc());

	dsv.Create();

	// フェンス生成
	fence.Create();

	rscBarrier.Initialize(cmdList.Get());

	return true;
}

void YDirectX::PreDraw()
{
	// バックバッファの番号を取得(2つなので0番か1番)
	UINT bbIndex = swpChain.Get()->GetCurrentBackBufferIndex();
	// 1.リソースバリアで書き込み可能に変更
	rscBarrier.SetCurrentBackBuffer(rtv.BackBaffer(bbIndex)); // バックバッファを指定
	rscBarrier.ChangeState(rscBarrier.RenderTarget); // 描画状態へ

	// 2.描画先の変更
	// レンダーターゲットビューのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtv.Get().Get()->GetCPUDescriptorHandleForHeapStart();
	rtvHandle.ptr += (SIZE_T)bbIndex * dev->Get()->GetDescriptorHandleIncrementSize(rtv.Get().desc.Type);
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = dsv.Get().Get()->GetCPUDescriptorHandleForHeapStart();
	cmdList.Get()->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

	// 3.画面クリア {R, G, B, A}
	FLOAT clearColor[] = { CLEAR_COLOR.r, CLEAR_COLOR.g, CLEAR_COLOR.b, CLEAR_COLOR.a };
	cmdList.Get()->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr); // 青っぽい色
	cmdList.Get()->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void YDirectX::PostDraw()
{
	// 5.リソースバリアを戻す
	rscBarrier.ChangeState(rscBarrier.Present); // 表示状態へ

	// 命令のクローズ
	Result::Check(cmdList.Get()->Close());

	// コマンドリスト実行
	ID3D12CommandList* commandLists[] = { cmdList.Get() };
	cmdQue.Get()->ExecuteCommandLists(1, commandLists);

	// 画面に表示するバッファをフリップ(裏表の入替え)
	Result::Check(swpChain.Get()->Present(1, 0));

	// コマンドの実行完了を待つ
	fence.ConfirmCommandComplate(cmdQue.Get());

	// キューをクリア + 再びコマンドリストを貯める準備
	cmdList.Reset();
}

ID3D12GraphicsCommandList* YDirectX::GetCommandList()
{
	return cmdList.Get();
}
