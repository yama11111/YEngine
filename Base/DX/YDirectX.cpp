#include "YDirectX.h"
#include "YAssert.h"
#include <wrl/client.h>
#include <thread>

using DX::YDirectX;
using std::chrono::steady_clock;
using std::chrono::microseconds;

microseconds YDirectX::MinTime_ = microseconds(uint64_t(1000000.0f / 60.0f));
microseconds YDirectX::MinCheckTime_ = microseconds(uint64_t(1000000.0f / 65.0f));

void  YDirectX::SetFPS(const float fps)
{
	MinTime_ = microseconds(uint64_t(1000000.0f / fps));
	MinCheckTime_ = microseconds(uint64_t(1000000.0f / (fps + 5.0f)));
}

bool YDirectX::Initialize(const HWND& hwnd, const Math::Vec2& size)
{
	// ----- FPS固定関連 ----- //
	// 現在時間を記録
	timeRef_ = steady_clock::now();

	// ----- デバッグレイヤーを有効に ----- //
#ifdef _DEBUG
	ComPtr<ID3D12Debug1> debugController;
	//デバッグレイヤーをオンに
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
		debugController->SetEnableGPUBasedValidation(true);
	}
#endif

	// ----- DXGIファクトリー生成 ----- //
	Result(CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory_)));

	// ----- デバイス生成 ----- //
	// アダプターの列挙用
	std::vector<ComPtr<IDXGIAdapter4>> adapters;
	// ここに特定の名前を持つアダプターオブジェクトが入る
	ComPtr<IDXGIAdapter4> tmpAdapter = nullptr;

	// パフォーマンスが高いものから順に、全てのアダプターを列挙
	for (UINT i = 0;
		dxgiFactory_->EnumAdapterByGpuPreference(
			i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
			IID_PPV_ARGS(&tmpAdapter)) != DXGI_ERROR_NOT_FOUND;
		i++)
	{
		// 動的配列に追加
		adapters.push_back(tmpAdapter.Get());
	}

	// 妥当なアダプタを選別
	for (size_t i = 0; i < adapters.size(); i++)
	{
		DXGI_ADAPTER_DESC3 adapterDesc;
		// アダプターの情報取得
		adapters[i]->GetDesc3(&adapterDesc);
		// ソフトウェアデバイスを回避
		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE))
		{
			// デバイスを採用してループを抜ける
			tmpAdapter = adapters[i];
			break;
		}
	}

	// アダプターが無いなら終了
	if (tmpAdapter == nullptr)
	{
		assert(false);
		return false;
	}

	// 対応レベルの配列
	D3D_FEATURE_LEVEL levels[4] =
	{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	D3D_FEATURE_LEVEL featureLevel{};

	for (size_t i = 0; i < _countof(levels); i++)
	{
		// 採用したアダプターでデバイス生成
		if (Result(D3D12CreateDevice(tmpAdapter.Get(), levels[i],
			IID_PPV_ARGS(&device_))))
		{
			// デバイスを生成できた時点でループを抜ける
			featureLevel = levels[i];
			break;
		}
	}

	// デバイスが無いなら終了
	if (device_ == nullptr)
	{
		assert(false);
		return false;
	}

	// ----- エラー時止まるように ----- //
#ifdef _DEBUG
	Microsoft::WRL::ComPtr<ID3D12InfoQueue> infoQueue;
	if (SUCCEEDED(device_->QueryInterface(IID_PPV_ARGS(&infoQueue))))
	{
		// 止まる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true); // ヤバいエラー
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true); // エラー
	}
	D3D12_MESSAGE_ID denyIds[] = {
		D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE
	};
	D3D12_MESSAGE_SEVERITY severities[] = { D3D12_MESSAGE_SEVERITY_INFO };
	D3D12_INFO_QUEUE_FILTER filter{};
	filter.DenyList.NumIDs = _countof(denyIds);
	filter.DenyList.pIDList = denyIds;
	filter.DenyList.NumSeverities = _countof(severities);
	filter.DenyList.pSeverityList = severities;
	infoQueue->PushStorageFilter(&filter);
#endif

	// ----- コマンドアロケータ生成 ----- //
	Result(device_->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(&cmdAllocator_)));

	// ----- コマンドリスト生成 ----- //
	Result(device_->CreateCommandList(
		0, D3D12_COMMAND_LIST_TYPE_DIRECT,
		cmdAllocator_.Get(), nullptr,
		IID_PPV_ARGS(&cmdList_)));

	// ----- コマンドキュー生成 ----- //
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{}; // 設定
	Result(device_->CreateCommandQueue(
		&commandQueueDesc, 
		IID_PPV_ARGS(&cmdQueue_)));

	// ----- スワップチェーン生成 ----- //
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{}; // 設定
	swapChainDesc.Width = (UINT)size.x_;
	swapChainDesc.Height = (UINT)size.y_;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;		  // 色情報の書式
	swapChainDesc.SampleDesc.Count = 1;						  // マルチサンプルしない
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;		  // バックバッファ用
	swapChainDesc.BufferCount = 2;							  // バッファ数を2つに設定
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // フリップ後は破棄
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	ComPtr<IDXGISwapChain1> swapChain1;

	Result(dxgiFactory_->CreateSwapChainForHwnd(
		cmdQueue_.Get(),
		hwnd,
		&swapChainDesc,
		nullptr,
		nullptr,
		&swapChain1));

	swapChain1.As(&swapChain_);

	// ----- レンダーターゲットビュー生成 ----- //
	// デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV; // レンダーターゲットビュー
	rtvHeapDesc.NumDescriptors = swapChainDesc.BufferCount; // 裏表の2つ
	// デスクリプタヒープ生成
	Result(device_->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap_)));
	// バックバッファ調整
	backBuffers_.resize(swapChainDesc.BufferCount);

	// スワップチェーンの全てのバッファについて処理する
	for (size_t i = 0; i < backBuffers_.size(); i++)
	{
		// スワップチェーンからバッファ取得
		swapChain_->GetBuffer((UINT)i, IID_PPV_ARGS(&backBuffers_[i]));
		// デスクリプタヒープのハンドル取得
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtvHeap_->GetCPUDescriptorHandleForHeapStart();
		// 裏か表かでアドレスがずれる
		rtvHandle.ptr += i * device_->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);
		// レンダーターゲットビュー設定
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
		// シェーダーの計算結果をSRGBに変換して書き込む
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		// レンダーターゲットビュー生成
		device_->CreateRenderTargetView(backBuffers_[i].Get(), &rtvDesc, rtvHandle);
	}

	// ----- デプスステンシルビュー生成 ----- //
	D3D12_RESOURCE_DESC dsvResDesc{}; // リソース設定
	dsvResDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	dsvResDesc.Width = (UINT16)size.x_; // レンダーターゲットに合わせる
	dsvResDesc.Height = (UINT)size.y_; // レンダーターゲットに合わせる
	dsvResDesc.DepthOrArraySize = 1;
	dsvResDesc.Format = DXGI_FORMAT_D32_FLOAT; // 深度値フォーマット
	dsvResDesc.SampleDesc.Count = 1;
	dsvResDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL; // デプスステンシル

	// 深度値用ヒーププロパティ
	D3D12_HEAP_PROPERTIES dsvHeapProp = {}; // バッファ設定
	dsvHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;

	// 深度値のクリア設定
	D3D12_CLEAR_VALUE clearValue{}; // 深度値のクリア設定
	clearValue.DepthStencil.Depth = 1.0f; // 深度値1.0f(最大値)でクリア
	clearValue.Format = DXGI_FORMAT_D32_FLOAT; // 深度値フォーマット

	// リソース生成
	Result(device_->CreateCommittedResource(
		&dsvHeapProp, // ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&dsvResDesc, // リソース設定
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&clearValue,
		IID_PPV_ARGS(&dsvBuff_)));

	// 深度ビュー用デスクリプターヒープ作成
	// デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	dsvHeapDesc.NumDescriptors = 1; // 深度ビューは1つ
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV; // デプスステンシルビュー
	Result(device_->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap_)));

	// 深度ビュー作成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT; // 深度値フォーマット
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;

	device_->CreateDepthStencilView(
		dsvBuff_.Get(),
		&dsvDesc,
		dsvHeap_->GetCPUDescriptorHandleForHeapStart());

	// ----- フェンス生成 ----- //
	Result(device_->CreateFence(fenceValue_, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence_)));

	return true;
}

void YDirectX::PreDraw(const Math::Vec4& clearColor)
{
	// 1.リソースバリアで書き込み可能に変更
	UINT bbIndex = swapChain_->GetCurrentBackBufferIndex(); // バックバッファの番号を取得(0番か1番)
	D3D12_RESOURCE_BARRIER barrierDesc{};
	barrierDesc.Transition.pResource = backBuffers_[bbIndex].Get(); // バックバッファを指定
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;       // 表示 状態から
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;  // 描画 状態へ
	cmdList_->ResourceBarrier(1, &barrierDesc);

	// 2.描画先の変更
	// レンダーターゲットビューのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtvHeap_->GetCPUDescriptorHandleForHeapStart();
	rtvHandle.ptr += (SIZE_T)bbIndex * device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	// デプスステンシルビューのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = dsvHeap_->GetCPUDescriptorHandleForHeapStart();
	cmdList_->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

	// 3.画面クリア {R, G, B, A}
	FLOAT clear[] = { clearColor.r_,clearColor.g_,clearColor.b_,clearColor.a_ };
	cmdList_->ClearRenderTargetView(rtvHandle, clear, 0, nullptr); // 青っぽい色
	cmdList_->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void YDirectX::PostDraw()
{
	// 5.リソースバリアを戻す
	UINT bbIndex = swapChain_->GetCurrentBackBufferIndex(); // バックバッファの番号を取得(0番か1番)
	D3D12_RESOURCE_BARRIER barrierDesc{};
	barrierDesc.Transition.pResource = backBuffers_[bbIndex].Get(); // バックバッファを指定
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET; // 描画 状態から
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;        // 表示 状態へ
	cmdList_->ResourceBarrier(1, &barrierDesc);

	// 命令のクローズ
	Result(cmdList_->Close());

	// コマンドリスト実行
	ID3D12CommandList* commandLists[] = { cmdList_.Get() };
	cmdQueue_->ExecuteCommandLists(1, commandLists);

	// 画面に表示するバッファをフリップ(裏表の入替え)
	Result(swapChain_->Present(1, 0));

	// コマンドの実行完了を待つ
	cmdQueue_->Signal(fence_.Get(), ++fenceValue_);
	if (fence_->GetCompletedValue() != fenceValue_)
	{
		HANDLE event = CreateEvent(nullptr, false, false, nullptr);
		fence_->SetEventOnCompletion(fenceValue_, event);
		if (event == 0) 
		{
			assert(false);
			return;
		}
		WaitForSingleObject(event, INFINITE);
		CloseHandle(event);
	}

	// 現在時間を取得
	steady_clock::time_point now = steady_clock::now();
	// 前回からの経過時間を取得
	microseconds elpsed = std::chrono::duration_cast<microseconds>(now - timeRef_);

	// 調整用fps分経っていない場合
	if (elpsed < MinCheckTime_)
	{
		// 固定時fps分経過するまで微小なスリープを繰り返す
		while (steady_clock::now() - timeRef_ < MinTime_)
		{
			// 1マイクロ秒スリープ
			std::this_thread::sleep_for(microseconds(1));
		}
	}

	// 現在時間を記録
	timeRef_ = steady_clock::now();

	// キューをクリア
	Result(cmdAllocator_->Reset());
	// 再びコマンドリストを貯める準備
	Result(cmdList_->Reset(cmdAllocator_.Get(), nullptr));
}
