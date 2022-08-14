#include "Texture.h"
#include "DXSRVHeap.h"
#include "Result.h"
#include <DirectXTex.h>

void Texture::Create(const Vec4& color)
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

	srvH = DXSRVHeap::GetInstance();
	index = srvH->SetSRV(texBuff.buff, srvDesc);
}

void Texture::Load(const wchar_t* imageName)
{
	TexMetadata metadata{};
	ScratchImage scratchImg{};
	// WICテクスチャのロード
	Result::Check(LoadFromWICFile(L"Resources/mario.jpg",
		WIC_FLAGS_NONE, &metadata, scratchImg));

	ScratchImage mipChain{};
	// ミップマップ生成
	if (Result::Check(GenerateMipMaps(scratchImg.GetImages(),
		scratchImg.GetImageCount(), scratchImg.GetMetadata(),
		TEX_FILTER_DEFAULT, 0, mipChain)))
	{
		scratchImg = std::move(mipChain);
		metadata = scratchImg.GetMetadata();
	}

	//読み込んだディフューズテクスチャを SRGB として扱う
	metadata.format = MakeSRGB(metadata.format);

	TexMetadata metadata2{};
	ScratchImage scratchImg2{};
	// WICテクスチャのロード
	Result::Check(LoadFromWICFile(L"Resources/reimu.png",
		WIC_FLAGS_NONE, &metadata2, scratchImg2));
}

void Texture::SetCommand()
{
	srvH->SetRootParameter(index);
}
