#include "Pipeline.h"
#include "YAssert.h"

using YGame::Pipeline;
using YGame::BaseConstBuffer;
using YDX::Result;

ID3D12Device* Pipeline::spDevice_ = nullptr;
ID3D12GraphicsCommandList* Pipeline::spCmdList_ = nullptr;

void Pipeline::EnqueueDrawSet(const size_t priority, const DrawSet& drawSet)
{
	assert(priority < drawQueue_.size());
	drawQueue_[priority].push(drawSet);
}

void Pipeline::Draw()
{
	// パイプライン設定
	spCmdList_->SetPipelineState(pipelineState_.Get());

	spCmdList_->SetGraphicsRootSignature(rootSignature_.Get());

	spCmdList_->IASetPrimitiveTopology(primitive_);

	for (size_t i = 0; i < drawQueue_.size(); i++)
	{
		// 逆順走査
		size_t irev = (drawQueue_.size() - 1) - i;
		
		if (drawQueue_[irev].empty()) { continue; }
		
		// 上から順に描画
		while (true)
		{
			if (drawQueue_[irev].empty()) { break; }

			// 定数バッファ
			ConstBufferPtrSet* pCBPtrSet = drawQueue_[irev].front().pCBPtrSet;

			for (auto itr = cbRPIndices_.begin(); itr != cbRPIndices_.end(); ++itr)
			{
				pCBPtrSet->SetDrawCommand(itr->first, itr->second);
			}

			// グラフィック
			BaseGraphic* pGraphic = drawQueue_[irev].front().pGraphic;

			assert(pGraphic);

			pGraphic->SetDrawCommand(graphicRPIndices_);

			drawQueue_[irev].pop();
		}
	}
}

Pipeline* Pipeline::Create(
	ShaderSet& shaderSet,
	const std::vector<std::string>& constBufferKeys,
	const std::vector<std::string>& graphicRPKeys,
	const uint32_t textureNum,
	const PipelineSetting& pipelineSetting,
	const BlendState& blendState,
	const UINT renderTargetNum)
{
	// 新規パイプライン
	Pipeline* newPipeline = new Pipeline();
	
	// 定数バッファルートパラメータ番号
	for (size_t i = 0; i < constBufferKeys.size(); i++)
	{
		std::string key = constBufferKeys[i];

		uint32_t index = static_cast<uint32_t>(i);

		newPipeline->cbRPIndices_.insert({ key, index });
	}
	
	const size_t cbRPIdxSize = constBufferKeys.size();

	// グラフィック用ルートパラメータ番号
	for (size_t i = 0; i < graphicRPKeys.size(); i++)
	{
		std::string key = graphicRPKeys[i];

		uint32_t index = static_cast<uint32_t>(i + cbRPIdxSize);

		newPipeline->graphicRPIndices_.insert({ key, index });
	}

#pragma region ルートパラメータの設定

	// ルートパラメータ
	std::vector<D3D12_ROOT_PARAMETER> rootParams;

	// 必用分のメモリ領域を確保
	size_t rpNum = constBufferKeys.size() + graphicRPKeys.size();
	rootParams.reserve(rpNum);


	// 定数バッファ数 = 全体 - テクスチャ枚数
	size_t cbNum = static_cast<size_t>(rpNum - textureNum);
	
	// 定数バッファ
	for (size_t i = 0; i < cbNum; i++)
	{
		D3D12_ROOT_PARAMETER rootParam{};
		rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;  // 定数バッファビュー
		rootParam.Descriptor.ShaderRegister = static_cast<UINT>(i); // 定数バッファ番号
		rootParam.Descriptor.RegisterSpace = 0;					  // デフォルト値
		rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // 全てのシェーダから見える

		rootParams.push_back(rootParam);
	}


	// デスクリプタレンジ
	std::vector<D3D12_DESCRIPTOR_RANGE> descriptorRanges{};

	descriptorRanges.reserve(textureNum);
	
	// テクスチャレジスタ
	for (size_t i = 0; i < textureNum; i++)
	{
		D3D12_DESCRIPTOR_RANGE descriptorRange{};

		// デスクリプタレンジの設定
		descriptorRange.NumDescriptors = 1; // 1度の描画に使うテクスチャが1枚なので1
		descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		descriptorRange.BaseShaderRegister = static_cast<UINT>(i); // テクスチャレジスタ番号
		descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

		descriptorRanges.push_back(descriptorRange);

		D3D12_ROOT_PARAMETER rootParam{};
		rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		rootParam.DescriptorTable.pDescriptorRanges = &descriptorRanges[i];
		rootParam.DescriptorTable.NumDescriptorRanges = 1;
		rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // 全てのシェーダから見える

		rootParams.push_back(rootParam);
	}

#pragma endregion


#pragma region パイプライン設定

	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};

	if (ID3DBlob* shader = shaderSet.ShaderPtr(ShaderSet::ShaderType::eVertex))
	{
		pipelineDesc.VS.pShaderBytecode	 = shader->GetBufferPointer();
		pipelineDesc.VS.BytecodeLength	 = shader->GetBufferSize();
	}
	if (ID3DBlob* shader = shaderSet.ShaderPtr(ShaderSet::ShaderType::eGeometry))
	{
		pipelineDesc.GS.pShaderBytecode	 = shader->GetBufferPointer();
		pipelineDesc.GS.BytecodeLength	 = shader->GetBufferSize();
	}
	if (ID3DBlob* shader = shaderSet.ShaderPtr(ShaderSet::ShaderType::ePixel))
	{
		pipelineDesc.PS.pShaderBytecode	 = shader->GetBufferPointer();
		pipelineDesc.PS.BytecodeLength	 = shader->GetBufferSize();
	}

	// サンプルマスクの設定
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定

	// ラスタライザの設定
	pipelineDesc.RasterizerState.FillMode = pipelineSetting.fillMode;
	pipelineDesc.RasterizerState.DepthClipEnable = true; // 深度クリッピングを有効に
	pipelineDesc.RasterizerState.CullMode = pipelineSetting.cullMode;

	// デプスステンシルステートの設定
	if (pipelineSetting.depthEnable)
	{
		pipelineDesc.DepthStencilState.DepthEnable = true; // 深度テストする
		pipelineDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL; // 書き込み許可
		pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS; // 小さければ合格
		pipelineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT; // 深度フォーマット
	}
	else
	{
		pipelineDesc.DepthStencilState.DepthEnable = false; // 深度テストしない
		pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS; // 常に上書き
	}

	for (size_t i = 0; i < renderTargetNum; i++)
	{
		// ブレンドステート
		D3D12_RENDER_TARGET_BLEND_DESC& blendDesc = pipelineDesc.BlendState.RenderTarget[i];
		
		blendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // RBGA全てのチャンネルを描画

		blendDesc.BlendEnable = true;                // ブレンドを有効にする
		blendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD; // 加算
		blendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;   // ソースの値を100%使う
		blendDesc.DestBlendAlpha = D3D12_BLEND_ZERO; // デストの値を  0%使う

		// 半透明合成
		blendDesc.BlendOp = D3D12_BLEND_OP_ADD;			 // 加算
		blendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;      // ソースのアルファ値
		blendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA; // 1.0f - ソースのアルファ値
	}

	// 図形の形状設定
	pipelineDesc.PrimitiveTopologyType = pipelineSetting.primitiveType;

	// 頂点レイアウトの設定
	pipelineDesc.InputLayout.pInputElementDescs = pipelineSetting.inputLayout.data(); // 頂点レイアウトの先頭アドレス
	pipelineDesc.InputLayout.NumElements = static_cast<UINT>(pipelineSetting.inputLayout.size()); // 頂点レイアウト数

	// その他の設定
	pipelineDesc.NumRenderTargets = static_cast<UINT>(renderTargetNum); // 描画対象
	for (size_t i = 0; i < renderTargetNum; i++)
	{
		pipelineDesc.RTVFormats[i] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0~255指定のRGBA
	}
	pipelineDesc.SampleDesc.Count = 1; // 1ピクセルにつき1回サンプリング

	// プリミティブ形状
	D3D_PRIMITIVE_TOPOLOGY primitive = pipelineSetting.primitive;

#pragma endregion

	newPipeline->CreateRootSignature(rootParams, pipelineSetting.samplerDescs);

	newPipeline->CreatePipelineState(pipelineDesc);

	newPipeline->SetPrimitiveTopology(primitive);

	return newPipeline;
}

void Pipeline::StaticInitialize(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCommandList)
{
	assert(pDevice);
	assert(pCommandList);

	spDevice_ = pDevice;
	spCmdList_ = pCommandList;
}

void Pipeline::CreateRootSignature(
	const std::vector<D3D12_ROOT_PARAMETER>& rootParams, 
	const std::vector<D3D12_STATIC_SAMPLER_DESC>& samplerDescs)
{
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

	// ルートシグネチャの設定
	D3D12_ROOT_SIGNATURE_DESC rsDesc{};
	rsDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rsDesc.pParameters		 = rootParams.data();
	rsDesc.NumParameters	 = static_cast<UINT>(rootParams.size());
	rsDesc.pStaticSamplers	 = samplerDescs.data();
	rsDesc.NumStaticSamplers = static_cast<UINT>(samplerDescs.size());

	Microsoft::WRL::ComPtr<ID3DBlob> rootSigBlob = nullptr; // ルートシグネチャオブジェクト
	Result(D3D12SerializeRootSignature(&rsDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, errorBlob.GetAddressOf()));

	Result(spDevice_->CreateRootSignature(
		0,
		rootSigBlob->GetBufferPointer(),
		rootSigBlob->GetBufferSize(),
		IID_PPV_ARGS(&rootSignature_)));
}

void Pipeline::CreatePipelineState(D3D12_GRAPHICS_PIPELINE_STATE_DESC& pipelineDesc)
{
	// パイプラインにルートシグネチャをセット
	pipelineDesc.pRootSignature = rootSignature_.Get();

	Result(spDevice_->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState_)));
}


void Pipeline::SetPrimitiveTopology(const D3D_PRIMITIVE_TOPOLOGY& primitive)
{
	// 未定義なら弾く
	assert(primitive != D3D_PRIMITIVE_TOPOLOGY_UNDEFINED);

	primitive_ = primitive;
}