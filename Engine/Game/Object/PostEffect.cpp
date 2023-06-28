#include "PostEffect.h"
#include "MathVector.h"
#include "YAssert.h"
#include "Def.h"
#include <d3dx12.h>

#pragma region 名前空間

using std::array;
using std::vector;
using std::list;
using std::unique_ptr;
using YGame::PostEffect;
using YDX::PipelineSet;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Matrix4;

#pragma endregion

#pragma region ルートパラメータ番号

static const UINT TraIndex = static_cast<UINT>(PostEffect::Pipeline::RootParameterIndex::eTransformCB); // transform
static const UINT ColIndex = static_cast<UINT>(PostEffect::Pipeline::RootParameterIndex::eColorCB); // color
static const UINT TexConfigIndex = static_cast<UINT>(PostEffect::Pipeline::RootParameterIndex::eTexConfigCB); // texConfig
static const UINT Tex0Index = static_cast<UINT>(PostEffect::Pipeline::RootParameterIndex::eTex0DT); // tex0
static const UINT Tex1Index = static_cast<UINT>(PostEffect::Pipeline::RootParameterIndex::eTex1DT); // tex1

#pragma endregion

#pragma region Static

vector<unique_ptr<PostEffect>> PostEffect::sPostEffects_{};
array<PipelineSet, PostEffect::Pipeline::sShaderNum_> PostEffect::Pipeline::sPipelineSets_{};
list<unique_ptr<PostEffect::Pipeline::DrawSet>> PostEffect::Pipeline::sDrawSets_;
ID3D12Device* PostEffect::spDevice_ = nullptr;
ID3D12GraphicsCommandList* PostEffect::spCmdList_ = nullptr;
YDX::ScreenDesc PostEffect::sScreenDesc_{};

#pragma endregion


#pragma region PostEffect

PostEffect* PostEffect::Create()
{
	// スプライト生成
	unique_ptr<PostEffect> newPostEffect = std::make_unique<PostEffect>();

	// 頂点バッファ生成
	newPostEffect->vt_.Initialize(
		{
			{ Vector3(       0.0f, +WinSize.y_, 0.0f), Vector2(0.0f, 1.0f) }, // 左下
			{ Vector3(       0.0f,        0.0f, 0.0f), Vector2(0.0f, 0.0f) }, // 左上
			{ Vector3(+WinSize.x_, +WinSize.y_, 0.0f), Vector2(1.0f, 1.0f) }, // 右下
			{ Vector3(+WinSize.x_,        0.0f, 0.0f), Vector2(1.0f, 0.0f) }, // 右上
		});

	for (size_t i = 0; i < newPostEffect->pTexs_.size(); i++)
	{
		// レンダーテクスチャ生成
		newPostEffect->pTexs_[i] = Texture::CreateRender();
	}

	// RTV初期化
	newPostEffect->CreateRTV();

	// 深度バッファ生成
	newPostEffect->CreateDepthBuff(WinSize);

	// DSV初期化
	newPostEffect->CreateDSV();

	// ポインタを獲得
	PostEffect* newPostEffectPtr = newPostEffect.get();

	// スプライトを保存
	sPostEffects_.push_back(std::move(newPostEffect));

	// スプライトポインタを返す
	return newPostEffectPtr;
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

void PostEffect::SetDrawCommand(PostEffect::Object* pObj, const ShaderType& shaderType)
{
	// 描画セット挿入
	Pipeline::StaticPushBackDrawSet(this, pObj, shaderType);
}

void PostEffect::StartRender()
{
	for (size_t i = 0; i < pTexs_.size(); i++)
	{
		// リソースバリア設定
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Transition.pResource = pTexs_[i]->Buffer(); // テクスチャを指定
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE; // シェーダーリソース 状態から
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;  // 描画 状態へ

		// リソースバリアを変更
		spCmdList_->ResourceBarrier(1, &barrierDesc);
	}

	// RTVのハンドルを取得
	std::array<D3D12_CPU_DESCRIPTOR_HANDLE, kTextureNum_> rtvHandles{};
	
	for (size_t i = 0; i < rtvHandles.size(); i++)
	{
		rtvHandles[i] = 
			CD3DX12_CPU_DESCRIPTOR_HANDLE(
			rtvHeap_->GetCPUDescriptorHandleForHeapStart(), static_cast<INT>(i),
			spDevice_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
	}
	
	// DSVのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = dsvHeap_->GetCPUDescriptorHandleForHeapStart();
	
	// レンダーターゲットをセット
	spCmdList_->OMSetRenderTargets(2, rtvHandles.data(), true, &dsvHandle);

	// スクリーン設定の描画コマンド
	sScreenDesc_.SetDrawCommand();

	for (size_t i = 0; i < rtvHandles.size(); i++)
	{
		// 画面クリア
		//FLOAT clear[] = { ClearColor.r_,ClearColor.g_,ClearColor.b_,ClearColor.a_ };
		FLOAT clear[] = { 0.25f, 0.5f ,0.1f, 0.0f };
		spCmdList_->ClearRenderTargetView(rtvHandles[i], clear, 0, nullptr); // 青っぽい色
	}
	
	// 深度バッファクリア
	spCmdList_->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void PostEffect::EndRender()
{
	for (size_t i = 0; i < pTexs_.size(); i++)
	{
		// リソースバリア設定
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Transition.pResource = pTexs_[i]->Buffer(); // テクスチャを指定
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET; // 描画 状態から
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE; // シェーダーリソース 状態へ

		// リソースバリアを変更
		spCmdList_->ResourceBarrier(1, &barrierDesc);
	}
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
	
	for (size_t i = 0; i < pTexs_.size(); i++)
	{
		// レンダーターゲットビュー生成
		spDevice_->CreateRenderTargetView(pTexs_[i]->Buffer(), &rtvDesc, 
			CD3DX12_CPU_DESCRIPTOR_HANDLE(
				rtvHeap_->GetCPUDescriptorHandleForHeapStart(), static_cast<INT>(i),
				spDevice_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV)));
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
	
	// スクリーン設定初期化
	sScreenDesc_.Initialize({ 0,0 }, WinSize, kTextureNum_);
}

#pragma endregion


#pragma region Object

PostEffect::Object* PostEffect::Object::Create(
	const Status& status,
	CBColor* pColor,
	CBTexConfig* pTexConfig,
	const bool isMutable)
{
	// インスタンス生成 (動的)
	Object* instance = new Object();

	// 定数バッファ生成
	instance->cBuff_.Create(isMutable);

	// 初期化(デフォルト)
	instance->Initialize(status);
	instance->SetColor(pColor);
	instance->SetTexConfig(pTexConfig);

	// インスタンスを返す
	return instance;
}

void PostEffect::Object::SetDrawCommand(
	const UINT transformRPIndex,
	const UINT colorRPIndex,
	const UINT texConfigRPIndex)
{
	// 行列
	cBuff_.map_->matWorld_ = m_ * Default::sProjection_;
	cBuff_.SetDrawCommand(transformRPIndex);

	// 色
	pColor_->SetDrawCommand(colorRPIndex);

	// テクスチャ設定
	pTexConfig_->SetDrawCommand(texConfigRPIndex);
}

void PostEffect::Object::SetColor(CBColor* pColor)
{
	// nullなら
	if (pColor == nullptr)
	{
		// デフォルト代入
		pColor_ = Default::sColor_.get();
		return;
	}

	// 代入
	pColor_ = pColor;
}

void PostEffect::Object::SetTexConfig(CBTexConfig* pTexConfig)
{
	// nullなら
	if (pTexConfig == nullptr)
	{
		// デフォルト代入
		pTexConfig_ = Default::sTexConfig_.get();
		return;
	}

	// 代入
	pTexConfig_ = pTexConfig;
}

Matrix4 PostEffect::Object::Default::sProjection_ = Matrix4::Identity();
unique_ptr<YGame::CBColor> PostEffect::Object::Default::sColor_ = nullptr;
unique_ptr<YGame::CBTexConfig> PostEffect::Object::Default::sTexConfig_ = nullptr;

void PostEffect::Object::Default::StaticInitialize()
{
	// プロジェクション行列を設定
	sProjection_ = YMath::MatOrthoGraphic();

	// 生成 + 初期化 (色)
	sColor_.reset(CBColor::Create({ 1.0f,1.0f,1.0f,1.0f }, { 1.0f,1.0f,1.0f,1.0f }, false));

	// 生成 + 初期化 (テクスチャ設定)
	sTexConfig_.reset(CBTexConfig::Create({ 1.0f,1.0f }, {}, false));
}

#pragma endregion


#pragma region シェーダー番号

static const UINT DefaultIndex			 = static_cast<UINT>(PostEffect::ShaderType::eDefault);
static const UINT ColorInversionIndex	 = static_cast<UINT>(PostEffect::ShaderType::eColorInversion);
static const UINT UVShiftBlurIndex		 = static_cast<UINT>(PostEffect::ShaderType::eUVShiftBlur);
static const UINT GaussianBlurIndex		 = static_cast<UINT>(PostEffect::ShaderType::eGaussianBlur);
static const UINT BloomIndex			 = static_cast<UINT>(PostEffect::ShaderType::eBloom);

#pragma endregion


#pragma region Pipeline

void PostEffect::Pipeline::ShaderSet::Load()
{
	// エラーオブジェクト
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

	// Default
	{
		ID3DBlob* vs = nullptr;
		ID3DBlob* ps = nullptr;

		// 頂点シェーダの読み込みとコンパイル
		LoadShader(L"Resources/Shaders/PostEffectVS.hlsl", "main", "vs_5_0", vs, errorBlob.Get());
		// ピクセルシェーダの読み込みとコンパイル
		LoadShader(L"Resources/Shaders/PostEffectPS.hlsl", "main", "ps_5_0", ps, errorBlob.Get());

		defaultVSBlob_ = vs;
		defaultPSBlob_ = ps;
	}

	// ColorInversion
	{
		ID3DBlob* ps = nullptr;

		// ピクセルシェーダの読み込みとコンパイル
		LoadShader(L"Resources/Shaders/ColorInversionPS.hlsl", "main", "ps_5_0", ps, errorBlob.Get());

		colorInversionPSBlob_ = ps;
	}

	// UVShiftBlur
	{
		ID3DBlob* ps = nullptr;

		// ピクセルシェーダの読み込みとコンパイル
		LoadShader(L"Resources/Shaders/UVShiftBlurPS.hlsl", "main", "ps_5_0", ps, errorBlob.Get());

		uvShiftBlurPSBlob_ = ps;
	}

	// Gaussian
	{
		ID3DBlob* ps = nullptr;

		// ピクセルシェーダの読み込みとコンパイル
		LoadShader(L"Resources/Shaders/GaussianBlurPS.hlsl", "main", "ps_5_0", ps, errorBlob.Get());

		gaussianBlurPSBlob_ = ps;
	}

	// Bloom
	{
		ID3DBlob* ps = nullptr;

		// ピクセルシェーダの読み込みとコンパイル
		LoadShader(L"Resources/Shaders/BloomPS.hlsl", "main", "ps_5_0", ps, errorBlob.Get());

		bloomPSBlob_ = ps;
	}
}

void PostEffect::Pipeline::StaticInitialize()
{

#pragma region シェーダー読み込み

	// シェーダー
	ShaderSet shdrs;

	// 読み込み
	shdrs.Load();

#pragma endregion


#pragma region 頂点レイアウトの設定

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

#pragma endregion


#pragma region テクスチャサンプラーの設定

	// テクスチャサンプラー配列
	std::vector<D3D12_STATIC_SAMPLER_DESC> samplerDescs;

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
	samplerDescs.push_back(samplerDesc);

#pragma endregion


#pragma region ルートパラメータの設定

	// ルートパラメータ
	std::vector<D3D12_ROOT_PARAMETER> rootParams;

	// メモリ領域を確保
	rootParams.reserve(static_cast<size_t>(RootParameterIndex::eTex1DT) + 1);

	// 定数バッファの数
	size_t rpIdxCBNum = static_cast<size_t>(RootParameterIndex::eTexConfigCB) + 1;

	// 定数バッファの数だけ
	for (size_t i = 0; i < rpIdxCBNum; i++)
	{
		// 定数バッファ
		D3D12_ROOT_PARAMETER rootParam{};
		rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;  // 定数バッファビュー
		rootParam.Descriptor.ShaderRegister = static_cast<UINT>(i); // 定数バッファ番号
		rootParam.Descriptor.RegisterSpace = 0;					  // デフォルト値
		rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // 全てのシェーダから見える

		// 配列に挿入
		rootParams.push_back(rootParam);
	}

	// デスクリプタテーブルの数
	size_t rpIdxDTNum = static_cast<size_t>(RootParameterIndex::eTex1DT) - static_cast<size_t>(RootParameterIndex::eTexConfigCB);

	// デスクリプタレンジ
	std::array<D3D12_DESCRIPTOR_RANGE, kTextureNum_> descriptorRanges{};

	// デスクリプタテーブルの数だけ
	for (size_t i = 0; i < rpIdxDTNum; i++)
	{
		// デスクリプタレンジの設定
		descriptorRanges[i].NumDescriptors = 1; // 1度の描画に使うテクスチャが1枚なので1
		descriptorRanges[i].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		descriptorRanges[i].BaseShaderRegister = static_cast<UINT>(i); // テクスチャレジスタ番号
		descriptorRanges[i].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

		// テクスチャレジスタ
		D3D12_ROOT_PARAMETER rootParam{};
		rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		rootParam.DescriptorTable.pDescriptorRanges = &descriptorRanges[i];
		rootParam.DescriptorTable.NumDescriptorRanges = 1;
		rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // 全てのシェーダから見える

		// 配列に挿入
		rootParams.push_back(rootParam);
	}

#pragma endregion


#pragma region パイプライン設定

	// パイプライン設定
	std::array<D3D12_GRAPHICS_PIPELINE_STATE_DESC, sPipelineSets_.size()> pipelineDescs{};

	// シェーダーの設定	
	pipelineDescs[DefaultIndex].VS.pShaderBytecode			 = shdrs.defaultVSBlob_.Get()->GetBufferPointer();
	pipelineDescs[DefaultIndex].VS.BytecodeLength			 = shdrs.defaultVSBlob_.Get()->GetBufferSize();
	pipelineDescs[DefaultIndex].PS.pShaderBytecode			 = shdrs.defaultPSBlob_.Get()->GetBufferPointer();
	pipelineDescs[DefaultIndex].PS.BytecodeLength			 = shdrs.defaultPSBlob_.Get()->GetBufferSize();

	pipelineDescs[ColorInversionIndex].VS.pShaderBytecode	 = shdrs.defaultVSBlob_.Get()->GetBufferPointer();
	pipelineDescs[ColorInversionIndex].VS.BytecodeLength	 = shdrs.defaultVSBlob_.Get()->GetBufferSize();
	pipelineDescs[ColorInversionIndex].PS.pShaderBytecode	 = shdrs.colorInversionPSBlob_.Get()->GetBufferPointer();
	pipelineDescs[ColorInversionIndex].PS.BytecodeLength	 = shdrs.colorInversionPSBlob_.Get()->GetBufferSize();

	pipelineDescs[UVShiftBlurIndex].VS.pShaderBytecode		 = shdrs.defaultVSBlob_.Get()->GetBufferPointer();
	pipelineDescs[UVShiftBlurIndex].VS.BytecodeLength		 = shdrs.defaultVSBlob_.Get()->GetBufferSize();
	pipelineDescs[UVShiftBlurIndex].PS.pShaderBytecode		 = shdrs.uvShiftBlurPSBlob_.Get()->GetBufferPointer();
	pipelineDescs[UVShiftBlurIndex].PS.BytecodeLength		 = shdrs.uvShiftBlurPSBlob_.Get()->GetBufferSize();

	pipelineDescs[GaussianBlurIndex].VS.pShaderBytecode		 = shdrs.defaultVSBlob_.Get()->GetBufferPointer();
	pipelineDescs[GaussianBlurIndex].VS.BytecodeLength		 = shdrs.defaultVSBlob_.Get()->GetBufferSize();
	pipelineDescs[GaussianBlurIndex].PS.pShaderBytecode		 = shdrs.gaussianBlurPSBlob_.Get()->GetBufferPointer();
	pipelineDescs[GaussianBlurIndex].PS.BytecodeLength		 = shdrs.gaussianBlurPSBlob_.Get()->GetBufferSize();

	pipelineDescs[BloomIndex].VS.pShaderBytecode			 = shdrs.defaultVSBlob_.Get()->GetBufferPointer();
	pipelineDescs[BloomIndex].VS.BytecodeLength				 = shdrs.defaultVSBlob_.Get()->GetBufferSize();
	pipelineDescs[BloomIndex].PS.pShaderBytecode			 = shdrs.bloomPSBlob_.Get()->GetBufferPointer();
	pipelineDescs[BloomIndex].PS.BytecodeLength				 = shdrs.bloomPSBlob_.Get()->GetBufferSize();

	// パイプラインの数だけ
	for (size_t i = 0; i < sPipelineSets_.size(); i++)
	{
		// サンプルマスクの設定
		pipelineDescs[i].SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定

		// ラスタライザの設定
		pipelineDescs[i].RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // ポリゴン内塗りつぶし
		pipelineDescs[i].RasterizerState.DepthClipEnable = true; // 深度クリッピングを有効に
		pipelineDescs[i].RasterizerState.CullMode = D3D12_CULL_MODE_BACK; // 背面をカリング

		// デプスステンシルステートの設定
		pipelineDescs[i].DepthStencilState.DepthEnable = false; // 深度テストしない
		pipelineDescs[i].DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS; // 常に上書き

		// ブレンドステート
		D3D12_RENDER_TARGET_BLEND_DESC& blendDesc = pipelineDescs[i].BlendState.RenderTarget[0];
		blendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // RBGA全てのチャンネルを描画

		blendDesc.BlendEnable = true;                // ブレンドを有効にする
		blendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD; // 加算
		blendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;   // ソースの値を100%使う
		blendDesc.DestBlendAlpha = D3D12_BLEND_ZERO; // デストの値を  0%使う

		if (i == BloomIndex)
		{
			// 加算合成
			blendDesc.BlendOp = D3D12_BLEND_OP_ADD; // 加算
			blendDesc.SrcBlend = D3D12_BLEND_ONE; // ソースの値を100%使う
			blendDesc.DestBlend = D3D12_BLEND_ONE; // デストの値を100%使う
		}
		else
		{
			// 半透明合成
			blendDesc.BlendOp = D3D12_BLEND_OP_ADD; // 加算
			blendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA; // ソースのアルファ値
			blendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA; // 1.0f - ソースのアルファ値
		}

		// 図形の形状設定
		pipelineDescs[i].PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

		// 頂点レイアウトの設定
		pipelineDescs[i].InputLayout.pInputElementDescs = inputLayout.data(); // 頂点レイアウトの先頭アドレス
		pipelineDescs[i].InputLayout.NumElements = (UINT)inputLayout.size(); // 頂点レイアウト数

		// その他の設定
		pipelineDescs[i].NumRenderTargets = 1; // 描画対象は1つ
		pipelineDescs[i].RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0~255指定のRGBA
		pipelineDescs[i].SampleDesc.Count = 1; // 1ピクセルにつき1回サンプリング
	}

#pragma endregion


#pragma region プリミティブ形状の設定

	// プリミティブ形状
	D3D_PRIMITIVE_TOPOLOGY primitive = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP; // 三角形ストリップ

#pragma endregion

	// パイプラインの数だけ
	for (size_t i = 0; i < sPipelineSets_.size(); i++)
	{
		// パイプライン初期化
		sPipelineSets_[i].Initialize(samplerDescs, rootParams, pipelineDescs[i], primitive);
	}

	// クリア
	StaticClearDrawSet();
}

void PostEffect::Pipeline::StaticClearDrawSet()
{
	// あるなら
	if (sDrawSets_.empty())
	{
		// クリア
		sDrawSets_.clear();
	}
}

void PostEffect::Pipeline::StaticPushBackDrawSet(
	PostEffect* pPostEffect, PostEffect::Object* pObj, 
	const ShaderType& shaderType)
{
	// 描画セット生成
	unique_ptr<Pipeline::DrawSet> newDrawSet = std::make_unique<Pipeline::DrawSet>();

	// 初期化
	newDrawSet->pPostEffect_ = pPostEffect;
	newDrawSet->pObj_ = pObj;
	newDrawSet->pipelineIndex_ = static_cast<size_t>(shaderType);

	// 挿入
	sDrawSets_.push_back(std::move(newDrawSet));
}

void PostEffect::Pipeline::StaticDraw()
{
	// ポストエフェクト描画
	for (std::unique_ptr<DrawSet>& drawSet : sDrawSets_)
	{
		// パイプラインをセット
		sPipelineSets_[drawSet->pipelineIndex_].SetDrawCommand();

		// 描画
		drawSet->Draw();
	}
}

void PostEffect::Pipeline::DrawSet::Draw()
{
	// 描画しないなら弾く
	if (pPostEffect_->isVisible_ == false) { return; }

	// 定数バッファをシェーダーに送る
	pObj_->SetDrawCommand(TraIndex, ColIndex, TexConfigIndex);

	// テクスチャ0
	pPostEffect_->pTexs_[0]->SetDrawCommand(Tex0Index);
	
	// テクスチャ1
	pPostEffect_->pTexs_[1]->SetDrawCommand(Tex1Index);

	// 頂点バッファを送る + 描画コマンド
	pPostEffect_->vt_.Draw();
}

#pragma endregion
