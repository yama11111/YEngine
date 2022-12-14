#include "TextureManager.h"
#include <DirectXTex.h>
#include "YAssert.h"

using Game::TextureManager;
using DX::GPUResource;
using Math::Vec4;
using DX::Result;

ID3D12Device* TextureManager::pDevice_ = nullptr;
ID3D12GraphicsCommandList*  TextureManager::pCmdList_ = nullptr;
DX::SRVHeap* TextureManager::pSrvHeap_ = nullptr;

void TextureManager::StaticInitialize(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCommandList, DX::SRVHeap* pSrvHeap)
{
	assert(pDevice);
	assert(pCommandList);
	assert(pSrvHeap);

	pDevice_ = pDevice;
	pCmdList_ = pCommandList;
	pSrvHeap_ = pSrvHeap;
}

std::string TextureManager::FileExtension(const std::string path)
{
	size_t idx = path.rfind('.') + 1;
	return path.substr(idx, path.length() - idx);
}

UINT TextureManager::CreateTex(const Math::Vec4& color)
{
	// テクスチャ情報
	Texture tex;

	// 画像イメージデータ配列
	Vec4* imageData = new Vec4[imageDataCount]; // ※必ず後で開放する

	// 全ピクセルの色を初期化
	for (size_t i = 0; i < imageDataCount; i++)
	{
		imageData[i].r_ = color.r_; // R
		imageData[i].g_ = color.g_; // G
		imageData[i].b_ = color.b_; // B
		imageData[i].a_ = color.a_; // A
	}

	// 生成用情報
	GPUResource::CreateStatus texState;
	// ヒープ設定
	texState.heapProp_.Type = D3D12_HEAP_TYPE_CUSTOM;
	texState.heapProp_.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	texState.heapProp_.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	// リソース設定
	texState.resDesc_.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	texState.resDesc_.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	texState.resDesc_.Width = textureWidth;   // 幅
	texState.resDesc_.Height = textureHeight; // 高さ
	texState.resDesc_.DepthOrArraySize = 1;
	texState.resDesc_.MipLevels = 1;
	texState.resDesc_.SampleDesc.Count = 1;

	// テクスチャバッファ生成
	tex.buff_.Create(texState);

	// テクスチャバッファにデータ転送
	Result(tex.buff_.Get()->WriteToSubresource(
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
	srvDesc.Format = texState.resDesc_.Format;  // RGBA float
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; // 2Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;

	// テクスチャ設定
	SetTexture(tex, &srvDesc);

	// テクスチャを保存
	texs_.push_back(tex);

	return static_cast<UINT>(texs_.size() - 1);
}

UINT TextureManager::Load(const std::string& texFileName, const bool mipMap)
{
	const std::string& directoryPath = "Resources/Textures/";
	return Load(directoryPath, texFileName, mipMap);
}

UINT TextureManager::Load(const std::string& directoryPath, const std::string texFileName, const bool mipMap)
{
	// テクスチャ情報
	Texture tex;

	DirectX::TexMetadata metadata{};
	DirectX::ScratchImage scratchImg{};

	// ファイル名
	std::string filePath = directoryPath + texFileName;
	std::wstring wFilePath = std::wstring(filePath.begin(), filePath.end());
	const wchar_t* fileName = wFilePath.c_str();

	// 拡張子取得
	std::string ext = FileExtension(texFileName);

	if (ext == "png") // png → WIC
	{
		// WICテクスチャのロード
		Result(LoadFromWICFile(fileName, DirectX::WIC_FLAGS_NONE, &metadata, scratchImg));
	}
	else if (ext == "tga") // tga → TGA
	{
		// TGAテクスチャのロード
		Result(LoadFromTGAFile(fileName, &metadata, scratchImg));
	}

	DirectX::ScratchImage mipChain{};
	// ミップマップ生成
	if (mipMap && (metadata.width > 1 && metadata.height > 1))
	{
		if (Result(GenerateMipMaps(
			scratchImg.GetImages(),
			scratchImg.GetImageCount(),
			scratchImg.GetMetadata(),
			DirectX::TEX_FILTER_DEFAULT, 0, mipChain)))
		{
			scratchImg = std::move(mipChain);
			metadata = scratchImg.GetMetadata();
		}
	}

	//読み込んだディフューズテクスチャを SRGB として扱う
	metadata.format = DirectX::MakeSRGB(metadata.format);

	// 生成用情報
	GPUResource::CreateStatus texState;
	// ヒープ設定
	texState.heapProp_.Type = D3D12_HEAP_TYPE_CUSTOM;
	texState.heapProp_.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	texState.heapProp_.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	// リソース設定
	texState.resDesc_.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	texState.resDesc_.Format = metadata.format;
	texState.resDesc_.Width = metadata.width;   // 幅
	texState.resDesc_.Height = (UINT)metadata.height; // 高さ
	texState.resDesc_.DepthOrArraySize = (UINT16)metadata.arraySize;
	texState.resDesc_.MipLevels = (UINT16)metadata.mipLevels;
	texState.resDesc_.SampleDesc.Count = 1;

	// テクスチャバッファ生成
	tex.buff_.Create(texState);

	// テクスチャバッファにデータ転送
	//全ミップマップについて
	for (size_t i = 0; i < metadata.mipLevels; i++)
	{
		// ミップマップを指定してイメージ取得
		const DirectX::Image* img = scratchImg.GetImage(i, 0, 0);
		// テクスチャバッファにデータ転送
		Result(tex.buff_.Get()->WriteToSubresource(
			(UINT)i,
			nullptr, // 全領域へコピー
			img->pixels, // 元データアドレス
			(UINT)img->rowPitch, // 1ラインサイズ
			(UINT)img->slicePitch // 1枚サイズ
		));
	}

	// シェーダリソースビュー設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = texState.resDesc_.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; // 2Dテクスチャ
	srvDesc.Texture2D.MipLevels = texState.resDesc_.MipLevels;

	// テクスチャ設定
	SetTexture(tex, &srvDesc);
	tex.fileName_ = texFileName;

	// テクスチャを保存
	texs_.push_back(tex);

	return static_cast<UINT>(texs_.size() - 1);
}

void TextureManager::SetTexture(Texture& tex, D3D12_SHADER_RESOURCE_VIEW_DESC* srvDesc)
{
	// SRVヒープの先頭ハンドル(CPU)を取得
	tex.srvCpuHandle_ = pSrvHeap_->CPUHandleStart();

	// SRVヒープの先頭ハンドル(GPU)を取得
	tex.srvGpuHandle_ = pSrvHeap_->GPUHandleStart();

	// インクリメントサイズ獲得
	UINT incSize = pDevice_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	// テクスチャがある分だけハンドルを進める
	tex.srvCpuHandle_.ptr += (incSize * texs_.size());

	// テクスチャがある分だけハンドルを進める
	tex.srvGpuHandle_.ptr += (incSize * texs_.size());

	// ハンドルの指す位置にシェーダーリソースビュー作成
	pDevice_->CreateShaderResourceView(tex.buff_.Get(), srvDesc, tex.srvCpuHandle_);
}

void TextureManager::SetDrawCommand(const UINT texIndex)
{
	assert((0 <= texIndex && texIndex < texs_.size()));
	pCmdList_->SetGraphicsRootDescriptorTable(rpIndex_, texs_[texIndex].srvGpuHandle_);
}

ID3D12Resource* Game::TextureManager::TextureBuffer(const UINT texIndex)
{
	assert((0 <= texIndex && texIndex < texs_.size()));
	return texs_[texIndex].buff_.Get();
}