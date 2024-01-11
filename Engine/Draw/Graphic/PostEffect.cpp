#include "PostEffect.h"
#include "GraphicType.h"
#include "MathVector.h"
#include "YAssert.h"
#include "Def.h"
#include <d3dx12.h>
#include <array>

using std::array;
using std::vector;
using std::list;
using std::unique_ptr;
using YGame::PostEffect;
using YGame::PipelineSetting;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Matrix4;

vector<unique_ptr<PostEffect>> PostEffect::sPostEffects_{};
ID3D12Device* PostEffect::spDevice_ = nullptr;
ID3D12GraphicsCommandList* PostEffect::spCmdList_ = nullptr;

PostEffect::PostEffect() : 
	BaseGraphic(GraphicType::kPostEffectTag), 
	vt_() ,pTexs_() ,phase_(Phase::None) ,screenDesc_(), 
	rtvHeap_(nullptr) ,dsvHeap_(nullptr) ,depthBuff_()
{
}

PostEffect* PostEffect::Create(const std::vector<std::string>& rtvTags)
{
	unique_ptr<PostEffect> newPostEffect = std::make_unique<PostEffect>();

	// 頂点バッファ生成
	newPostEffect->vt_.Initialize(
		{
			{ Vector3(0.0f,        +WinSize.y_, 0.0f), Vector2(0.0f, 1.0f) }, // 左下
			{ Vector3(0.0f,               0.0f, 0.0f), Vector2(0.0f, 0.0f) }, // 左上
			{ Vector3(+WinSize.x_, +WinSize.y_, 0.0f), Vector2(1.0f, 1.0f) }, // 右下
			{ Vector3(+WinSize.x_,        0.0f, 0.0f), Vector2(1.0f, 0.0f) }, // 右上
		});

	// レンダーテクスチャ生成
	for (size_t i = 0; i < rtvTags.size(); i++)
	{
		Texture* pTex = Texture::CreateRender();

		newPostEffect->pTexs_.insert({ rtvTags[i], pTex });
	}

	newPostEffect->CreateRTV();

	newPostEffect->CreateDepthBuff(WinSize);

	newPostEffect->CreateDSV();

	newPostEffect->phase_ = Phase::None;

	newPostEffect->screenDesc_.Initialize({ 0,0 }, WinSize, rtvTags.size());

	// ポインタを獲得
	PostEffect* newPostEffectPtr = newPostEffect.get();

	// ポストエフェクトを保存
	sPostEffects_.push_back(std::move(newPostEffect));

	// ポインタを返す
	return newPostEffectPtr;
}

void PostEffect::CreateRTV()
{
	// デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV; // レンダーターゲットビュー
	rtvHeapDesc.NumDescriptors = 2;

	// デスクリプタヒープ生成
	YDX::Result(spDevice_->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap_)));


	// レンダーターゲットビュー設定
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};

	// シェーダーの計算結果をSRGBに変換して書き込む
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

	
	INT count = 0;
	for (auto itr = pTexs_.begin(); itr != pTexs_.end(); ++itr)
	{
		// レンダーターゲットビュー生成
		spDevice_->CreateRenderTargetView(itr->second->Buffer(), &rtvDesc,
			CD3DX12_CPU_DESCRIPTOR_HANDLE(
				rtvHeap_->GetCPUDescriptorHandleForHeapStart(), count,
				spDevice_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV)));

		count++;
	}
}

void PostEffect::CreateDepthBuff(const YMath::Vector2& size)
{
	// リソース設定
	D3D12_RESOURCE_DESC depthResDesc{};
	depthResDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthResDesc.Width = (UINT16)size.x_;
	depthResDesc.Height = (UINT)size.y_;
	depthResDesc.DepthOrArraySize = 1;
	depthResDesc.Format = DXGI_FORMAT_D32_FLOAT; // 深度値フォーマット
	depthResDesc.SampleDesc.Count = 1;
	depthResDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL; // デプスステンシル

	// 深度値用ヒーププロパティ
	D3D12_HEAP_PROPERTIES depthHeapProp = {}; // バッファ設定
	depthHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;

	// 深度値のクリア設定
	D3D12_CLEAR_VALUE clearValue{}; // 深度値のクリア設定
	clearValue.DepthStencil.Depth = 1.0f; // 深度値1.0f(最大値)でクリア
	clearValue.Format = DXGI_FORMAT_D32_FLOAT; // 深度値フォーマット

	// 深度バッファ生成
	depthBuff_.Create(&depthHeapProp, &depthResDesc, D3D12_RESOURCE_STATE_DEPTH_WRITE, &clearValue);
}

void PostEffect::CreateDSV()
{
	// デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	dsvHeapDesc.NumDescriptors = 1; // 深度ビューは1つ
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV; // デプスステンシルビュー

	// 深度ビュー用デスクリプターヒープ作成
	YDX::Result(spDevice_->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap_)));

	// 深度ビュー設定
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT; // 深度値フォーマット
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;

	// 深度ビュー作成
	spDevice_->CreateDepthStencilView(
		depthBuff_.Get(),
		&dsvDesc,
		dsvHeap_->GetCPUDescriptorHandleForHeapStart());
}

void PostEffect::AllClear()
{
	// スプライト2D全消去
	for (size_t i = 0; i < sPostEffects_.size(); i++)
	{
		sPostEffects_[i].reset(nullptr);
	}
	sPostEffects_.clear();
}

void PostEffect::StartRender()
{
	// 順番通りじゃないなら警告
	assert(phase_ == Phase::None);

	for (auto itr = pTexs_.begin(); itr != pTexs_.end(); ++itr)
	{
		// リソースバリア設定
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Transition.pResource = itr->second->Buffer(); // テクスチャを指定
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE; // シェーダーリソース 状態から
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET; // 描画 状態へ

		// リソースバリアを変更
		spCmdList_->ResourceBarrier(1, &barrierDesc);
	}

	// RTVのハンドルを取得
	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> rtvHandles;

	for (size_t i = 0; i < pTexs_.size(); i++)
	{
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle =
			CD3DX12_CPU_DESCRIPTOR_HANDLE(
				rtvHeap_->GetCPUDescriptorHandleForHeapStart(), static_cast<INT>(i),
				spDevice_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));

		rtvHandles.emplace_back(rtvHandle);
	}

	// DSVのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = dsvHeap_->GetCPUDescriptorHandleForHeapStart();

	// レンダーターゲットをセット
	spCmdList_->OMSetRenderTargets(static_cast<UINT>(rtvHandles.size()), rtvHandles.data(), true, &dsvHandle);

	// スクリーン設定の描画コマンド
	screenDesc_.SetDrawCommand();

	for (size_t i = 0; i < rtvHandles.size(); i++)
	{
		// 画面クリア
		//FLOAT clear[4] = { ClearColor.r_,ClearColor.g_,ClearColor.b_,0.0f };
		FLOAT clear[] = { 0.25f, 0.5f ,0.1f, 0.0f };
		spCmdList_->ClearRenderTargetView(rtvHandles[i], clear, 0, nullptr); // 青っぽい色
	}

	// 深度バッファクリア
	spCmdList_->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	// 段階を進める
	phase_ = Phase::Rendering;
}

void PostEffect::EndRender()
{
	// 順番通りじゃないなら警告
	assert(phase_ == Phase::Rendering);

	for (auto itr = pTexs_.begin(); itr != pTexs_.end(); ++itr)
	{
		// リソースバリア設定
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Transition.pResource = itr->second->Buffer(); // テクスチャを指定
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET; // 描画 状態から
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE; // シェーダーリソース 状態へ

		// リソースバリアを変更
		spCmdList_->ResourceBarrier(1, &barrierDesc);
	}

	// 段階を進める
	phase_ = Phase::End;
}

void PostEffect::SetDrawCommand(std::unordered_map<std::string, uint32_t>& rpIndices)
{
	// 順番通りじゃないなら警告
	assert(phase_ == Phase::End);

	if (isVisible_ == false) { return; }

	// テクスチャ
	for (auto itr = rpIndices.begin(); itr != rpIndices.end(); ++itr)
	{
		// 同一キーがない場合警告
		assert(pTexs_.contains(itr->first));

		pTexs_[itr->first]->SetDrawCommand(itr->second);
	}

	// 頂点バッファを送る + 描画コマンド
	vt_.Draw();

	// 段階を最初に戻す
	phase_ = Phase::None;
}

void PostEffect::StaticInitialize(
	ID3D12Device* pDevice,
	ID3D12GraphicsCommandList* pCmdList)
{
	// nullチェック
	assert(pDevice);
	assert(pCmdList);

	// 代入
	spDevice_ = pDevice;
	spCmdList_ = pCmdList;
}

PipelineSetting PostEffect::GetPipelineSetting()
{
	PipelineSetting result;

	// 頂点レイアウト
	std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout =
	{
		// 頂点座標	 (x, y, z)
		{
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		// UV座標	 (x, y)
		{
			"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		}
	};

	result.inputLayout = inputLayout;

	// テクスチャサンプラーの設定
	D3D12_STATIC_SAMPLER_DESC samplerDesc{};
	samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 横折り返し   (タイリング)
	samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 縦折り返し   (タイリング)
	samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 奥行折り返し (タイリング)
	samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK; // ボーダーの時は黒
	samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;   // 全てリニア補間
	samplerDesc.MaxLOD = D3D12_FLOAT32_MAX; // ミニマップ最大値
	samplerDesc.MinLOD = 0.0f;              // ミニマップ最小値
	samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // ピクセルシェーダーからのみ使用可能

	// テクスチャサンプラー配列に挿入
	result.samplerDescs.emplace_back(samplerDesc);

	result.fillMode = D3D12_FILL_MODE_SOLID; // ポリゴン内塗りつぶし

	result.cullMode = D3D12_CULL_MODE_NONE; // 背面をカリングしない

	result.depthEnable = false; // 深度テストしない

	result.primitiveType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE; // 三角形

	result.primitive = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP; // 三角形ストリップ

	return result;
}