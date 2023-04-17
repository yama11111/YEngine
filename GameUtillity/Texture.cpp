#include "Texture.h"
#include "FileUtillity.h"
#include "YAssert.h"
#include <DirectXTex.h>

#pragma region 名前空間

using std::unique_ptr;
using YGame::Texture;
using YDX::GPUResource;
using YDX::DescriptorHeap;
using YMath::Vector4;
using YDX::Result;

#pragma endregion

#pragma region Static

std::vector<unique_ptr<Texture>> Texture::texs_{};
Texture::Common Texture::common_{};
ID3D12Device* Texture::Common::pDevice_ = nullptr;
ID3D12GraphicsCommandList* Texture::Common::pCmdList_ = nullptr;
YDX::DescriptorHeap* Texture::Common::pDescHeap_ = nullptr;

#pragma endregion

Texture* Texture::Create(const Vector4& color)
{
	// テクスチャ生成
	unique_ptr<Texture> newTex = std::make_unique<Texture>();

	// 横方向ピクセル数
	static const size_t textureWidth = 1;
	// 縦方向ピクセル数
	static const size_t textureHeight = 1;
	// 配列の要素数
	static const size_t imageDataCount = textureWidth * textureHeight;

	// 画像イメージデータ配列
	Vector4* imageData = new Vector4[imageDataCount]; // ※必ず後で開放する

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
	//texState.heapProp_.Type = D3D12_HEAP_TYPE_DEFAULT;
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
	newTex->buff_.Create(texState);

	// テクスチャバッファにデータ転送
	Result(newTex->buff_.Get()->WriteToSubresource(
		0,
		nullptr, // 全領域へコピー
		imageData, // 元データアドレス
		sizeof(Vector4) * textureWidth, // 1ラインサイズ
		sizeof(Vector4) * imageDataCount // 全サイズ
	));

	// データ開放
	delete[] imageData;

	// シェーダリソースビュー設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = texState.resDesc_.Format;  // RGBA float
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; // 2Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;

	// SRV生成
	DescriptorHeap::Handle handle{};
	handle = common_.pDescHeap_->CreateSRV(newTex->buff_.Get(), srvDesc, false);

	// ハンドル代入
	newTex->srvCpuHandle_ = handle.cpu_;
	newTex->srvGpuHandle_ = handle.gpu_;


	// ポインタを獲得
	Texture* newTexPtr = newTex.get();

	// テクスチャを保存
	texs_.push_back(std::move(newTex));

	// テクスチャポインタを返す
	return newTexPtr;
}

Texture* Texture::Load(const std::string& texFileName, const bool mipMap)
{
	// ディレクトリパスを設定
	const std::string& directoryPath = "Resources/Textures/";
	
	// テクスチャ読み込み
	return Load(directoryPath, texFileName, mipMap);
}

Texture* Texture::Load(const std::string& directoryPath, const std::string texFileName, const bool mipMap)
{
	// 読み込んだことがあるかチェック
	for (size_t i = 0; i < texs_.size(); i++)
	{
		// ファイルパス が同じなら
		if( directoryPath + texFileName == texs_[i]->fileName_)
		{
			// そのテクスチャポインタを返す
			return texs_[i].get();
		}
	}

	// テクスチャ生成
	unique_ptr<Texture> newTex = std::make_unique<Texture>();

	DirectX::TexMetadata metadata{};
	DirectX::ScratchImage scratchImg{};

	// ファイル名
	std::string filePath = directoryPath + texFileName;
	std::wstring wFilePath = std::wstring(filePath.begin(), filePath.end());
	const wchar_t* fileName = wFilePath.c_str();

	// 拡張子取得
	std::string ext = YUtil::FileExtension(texFileName);

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
	//texState.heapProp_.Type = D3D12_HEAP_TYPE_DEFAULT;
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
	newTex->buff_.Create(texState);

	// テクスチャバッファにデータ転送
	//全ミップマップについて
	for (size_t i = 0; i < metadata.mipLevels; i++)
	{
		// ミップマップを指定してイメージ取得
		const DirectX::Image* img = scratchImg.GetImage(i, 0, 0);
		// テクスチャバッファにデータ転送
		Result(newTex->buff_.Get()->WriteToSubresource(
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

	// SRV生成
	DescriptorHeap::Handle handle{};
	handle = common_.pDescHeap_->CreateSRV(newTex->buff_.Get(), srvDesc, false);

	// ハンドル代入
	newTex->srvCpuHandle_ = handle.cpu_;
	newTex->srvGpuHandle_ = handle.gpu_;

	// ディレクトリパス名 + ファイル名代入
	newTex->fileName_ = directoryPath + texFileName;


	// ポインタを獲得
	Texture* newTexPtr = newTex.get();

	// テクスチャを保存
	texs_.push_back(std::move(newTex));

	// テクスチャポインタを返す
	return newTexPtr;
}

void Texture::AllClear()
{
	// テクスチャ全消去
	for (size_t i = 0; i < texs_.size(); i++)
	{
		texs_[i].reset(nullptr);
	}
	texs_.clear();
}

void Texture::SetDrawCommand(const UINT rootParamIndex)
{	
	// シェーダーにテクスチャを設定
	common_.pCmdList_->SetGraphicsRootDescriptorTable(rootParamIndex, srvGpuHandle_);
}

ID3D12Resource* Texture::Buffer()
{
	// テクスチャバッファを返す
	return buff_.Get();
}

void Texture::Common::StaticInitialize(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCmdList, YDX::DescriptorHeap* pDescHeap)
{
	// nullチェック
	assert(pDevice);
	assert(pCmdList);
	assert(pDescHeap);

	// 代入
	pDevice_ = pDevice;
	pCmdList_ = pCmdList;
	pDescHeap_ = pDescHeap;
}