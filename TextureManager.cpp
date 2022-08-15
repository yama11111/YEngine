#include "TextureManager.h"
#include "DXRootParameterManager.h"
#include "DXResource.h"
#include "Result.h"
#include <DirectXTex.h>

TextureManager::TextureManager() 
{
	srvH = DXSRVHeap::GetInstance();
}

UINT TextureManager::Create(const Vec4& color)
{
	// 横方向ピクセル数
	const size_t textureWidth = 256;
	// 縦方向ピクセル数
	const size_t textureHeight = 256;
	// 配列の要素数
	const size_t imageDataCount = textureWidth * textureHeight;
	// 画像イメージデータ配列
	Vec4* imageData = new Vec4[imageDataCount]; // ※必ず後で開放する

	// 全ピクセルの色を初期化
	for (size_t i = 0; i < imageDataCount; i++)
	{
		imageData[i].r = color.r; // R
		imageData[i].g = color.g; // G
		imageData[i].b = color.b; // B
		imageData[i].a = color.a; // A
	}

	DXResourceInfo texInfo;
	DXResource texBuff;

	// ヒープ設定
	texInfo.heapProp;
	texInfo.heapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	texInfo.heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	texInfo.heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	// リソース設定
	texInfo.resDesc;
	texInfo.resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	texInfo.resDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	texInfo.resDesc.Width = textureWidth;   // 幅
	texInfo.resDesc.Height = textureHeight; // 高さ
	texInfo.resDesc.DepthOrArraySize = 1;
	texInfo.resDesc.MipLevels = 1;
	texInfo.resDesc.SampleDesc.Count = 1;

	texBuff.Create(texInfo);

	// テクスチャバッファにデータ転送
	Result::Check(texBuff.buff->WriteToSubresource(
		0,
		nullptr, // 全領域へコピー
		imageData, // 元データアドレス
		sizeof(Vec4) * textureWidth, // 1ラインサイズ
		sizeof(Vec4) * imageDataCount // 全サイズ
	));

	// データ開放
	delete[] imageData;

	// シェーダリソースビュー設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;  // RGBA float
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; // 2Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;

	return srvH->SetSRV(texBuff.buff, srvDesc);
}

UINT TextureManager::Load(const wchar_t* fileName)
{
	DirectX::TexMetadata metadata{};
	DirectX::ScratchImage scratchImg{};
	// WICテクスチャのロード
	Result::Check(LoadFromWICFile(fileName,
		DirectX::WIC_FLAGS_NONE, &metadata, scratchImg));

	DirectX::ScratchImage mipChain{};
	// ミップマップ生成
	if (Result::Check(GenerateMipMaps(scratchImg.GetImages(),
		scratchImg.GetImageCount(), scratchImg.GetMetadata(),
		DirectX::TEX_FILTER_DEFAULT, 0, mipChain)))
	{
		scratchImg = std::move(mipChain);
		metadata = scratchImg.GetMetadata();
	}

	//読み込んだディフューズテクスチャを SRGB として扱う
	metadata.format = DirectX::MakeSRGB(metadata.format);

	DXResourceInfo texInfo;
	DXResource texBuff;

	// ヒープ設定
	texInfo.heapProp;
	texInfo.heapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	texInfo.heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	texInfo.heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	// リソース設定
	texInfo.resDesc;
	texInfo.resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	texInfo.resDesc.Format = metadata.format;
	texInfo.resDesc.Width = metadata.width;   // 幅
	texInfo.resDesc.Height = (UINT)metadata.height; // 高さ
	texInfo.resDesc.DepthOrArraySize = (UINT16)metadata.arraySize;
	texInfo.resDesc.MipLevels = (UINT16)metadata.mipLevels;
	texInfo.resDesc.SampleDesc.Count = 1;

	texBuff.Create(texInfo);

	// テクスチャバッファにデータ転送
	//全ミップマップについて
	for (size_t i = 0; i < metadata.mipLevels; i++)
	{
		// ミップマップを指定してイメージ取得
		const DirectX::Image* img = scratchImg.GetImage(i, 0, 0);
		// テクスチャバッファにデータ転送
		Result::Check(texBuff.buff->WriteToSubresource(
			(UINT)i,
			nullptr, // 全領域へコピー
			img->pixels, // 元データアドレス
			(UINT)img->rowPitch, // 1ラインサイズ
			(UINT)img->slicePitch // 1枚サイズ
		));
	}

	// シェーダリソースビュー設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = texInfo.resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; // 2Dテクスチャ
	srvDesc.Texture2D.MipLevels = texInfo.resDesc.MipLevels;

	return srvH->SetSRV(texBuff.buff, srvDesc);
}

void TextureManager::SetRootParameter()
{
	// デスクリプタレンジの設定
	descriptorRange.NumDescriptors = 1; // 1度の描画に使うテクスチャが1枚なので1
	descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange.BaseShaderRegister = 0; // テクスチャレジスタ0番
	descriptorRange.OffsetInDescriptorsFromTableStart =
		D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	DXRootParameterManager* rpM = DXRootParameterManager::GetInstance();
	srvH->rpIndex = rpM->PushBackDescriptorTable(descriptorRange);
}

void TextureManager::SetCommand(UINT& index)
{
	srvH->SetRootParameter(index);
}

TextureManager* TextureManager::GetInstance()
{
	static TextureManager instance;
	return &instance;
}
