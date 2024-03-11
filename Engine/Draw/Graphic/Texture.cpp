#include "Texture.h"
#include "FileUtil.h"
#include "YAssert.h"
#include "Def.h"
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

std::vector<unique_ptr<Texture>> Texture::sTexs_{};
ID3D12Device* Texture::Common::spDevice_ = nullptr;
ID3D12GraphicsCommandList* Texture::Common::spCmdList_ = nullptr;
YDX::DescriptorHeap* Texture::Common::spDescHeap_ = nullptr;

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
		imageData[i].x = color.x; // R
		imageData[i].y = color.y; // G
		imageData[i].z = color.z; // B
		imageData[i].w = color.w; // A
	}

	// ヒープ設定
	D3D12_HEAP_PROPERTIES heapProp{};
	//heapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
	heapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	
	// リソース設定
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	resDesc.Width = (UINT16)textureWidth;   // 幅
	resDesc.Height = (UINT)textureHeight; // 高さ
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;

	// テクスチャバッファ生成
	newTex->buff_.Create(&heapProp, &resDesc);

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
	srvDesc.Format = resDesc.Format;  // RGBA float
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; // 2Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;

	// SRV生成
	DescriptorHeap::Handle handle{};
	handle = Common::spDescHeap_->CreateSRV(newTex->buff_.Get(), srvDesc, false);

	// ハンドル代入
	newTex->srvCpuHandle_ = handle.cpu_;
	newTex->srvGpuHandle_ = handle.gpu_;


	// ポインタを獲得
	Texture* newTexPtr = newTex.get();

	// テクスチャを保存
	sTexs_.push_back(std::move(newTex));

	// テクスチャポインタを返す
	return newTexPtr;
}

Texture* Texture::CreateRender(const YMath::Vector2& size, const YMath::Vector4& clearColor)
{
	// テクスチャ生成
	unique_ptr<Texture> newTex = std::make_unique<Texture>();

	// 横方向ピクセル数
	static const size_t textureWidth = static_cast<size_t>(size.x);
	// 縦方向ピクセル数
	static const size_t textureHeight = static_cast<size_t>(size.y);
	// 配列の要素数
	static const size_t imageDataCount = textureWidth * textureHeight;

	// 画像イメージデータ配列
	UINT* imageData = new UINT[imageDataCount]; // ※必ず後で開放する

	// 全ピクセルの色を初期化
	for (size_t i = 0; i < imageDataCount; i++)
	{
		imageData[i] = 0xffffffff;
	}

	// ヒープ設定
	D3D12_HEAP_PROPERTIES heapProp{};
	heapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	
	// リソース設定
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	resDesc.Width = (UINT16)textureWidth;   // 幅
	resDesc.Height = (UINT)textureHeight; // 高さ
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
	
	// リソースステート設定
	D3D12_RESOURCE_STATES resState = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
	
	// クリア設定
	D3D12_CLEAR_VALUE clearValue{};
	clearValue.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	clearValue.Color[0] = clearColor.x;
	clearValue.Color[1] = clearColor.y;
	clearValue.Color[2] = clearColor.z;
	clearValue.Color[3] = clearColor.w;

	// テクスチャバッファ生成
	newTex->buff_.Create(&heapProp, &resDesc, resState, &clearValue);

	// テクスチャバッファにデータ転送
	Result(newTex->buff_.Get()->WriteToSubresource(
		0,
		nullptr, // 全領域へコピー
		imageData, // 元データアドレス
		sizeof(UINT) * (UINT)textureWidth, // 1ラインサイズ
		sizeof(UINT) * (UINT)imageDataCount // 全サイズ
	));

	// データ開放
	delete[] imageData;

	// シェーダリソースビュー設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = resDesc.Format;  // RGBA float
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; // 2Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;

	// SRV生成
	DescriptorHeap::Handle handle{};
	handle = Common::spDescHeap_->CreateSRV(newTex->buff_.Get(), srvDesc, false);

	// ハンドル代入
	newTex->srvCpuHandle_ = handle.cpu_;
	newTex->srvGpuHandle_ = handle.gpu_;


	// ポインタを獲得
	Texture* newTexPtr = newTex.get();

	// テクスチャを保存
	sTexs_.push_back(std::move(newTex));

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
	for (size_t i = 0; i < sTexs_.size(); i++)
	{
		// ファイルパス が同じなら
		if(directoryPath + texFileName == sTexs_[i]->fileName_)
		{
			// そのテクスチャポインタを返す
			return sTexs_[i].get();
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
	std::string ext = YFile::FileExtension(texFileName);

	if (ext == "png" || ext == "jpg") // png || jpg → WIC
	{
		// WICテクスチャのロード
		Result(LoadFromWICFile(fileName, DirectX::WIC_FLAGS_NONE, &metadata, scratchImg));
	}
	else if (ext == "dds") // dds → DDS
	{
		// DDSテクスチャのロード
		Result(LoadFromDDSFile(fileName, DirectX::DDS_FLAGS_NONE, &metadata, scratchImg));
	}
	else if (ext == "tga") // tga → TGA
	{
		// TGAテクスチャのロード
		Result(LoadFromTGAFile(fileName, &metadata, scratchImg));
	}

	DirectX::ScratchImage mipChain{};
	// ミップマップ生成
	if (ext != "dds" && mipMap && (metadata.width > 1 && metadata.height > 1))
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

	// ヒープ設定
	D3D12_HEAP_PROPERTIES heapProp{};
	//texState.heapProp_.Type = D3D12_HEAP_TYPE_DEFAULT;
	heapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	
	// リソース設定
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resDesc.Format = metadata.format;
	resDesc.Width = metadata.width;   // 幅
	resDesc.Height = (UINT)metadata.height; // 高さ
	resDesc.DepthOrArraySize = (UINT16)metadata.arraySize;
	resDesc.MipLevels = (UINT16)metadata.mipLevels;
	resDesc.SampleDesc.Count = 1;

	// テクスチャバッファ生成
	newTex->buff_.Create(&heapProp, &resDesc);

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
	srvDesc.Format = resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; // 2Dテクスチャ
	srvDesc.Texture2D.MipLevels = resDesc.MipLevels;

	// SRV生成
	DescriptorHeap::Handle handle{};
	handle = Common::spDescHeap_->CreateSRV(newTex->buff_.Get(), srvDesc, false);

	// ハンドル代入
	newTex->srvCpuHandle_ = handle.cpu_;
	newTex->srvGpuHandle_ = handle.gpu_;

	// ディレクトリパス名 + ファイル名代入
	newTex->fileName_ = directoryPath + texFileName;


	// ポインタを獲得
	Texture* newTexPtr = newTex.get();

	// テクスチャを保存
	sTexs_.push_back(std::move(newTex));

	// テクスチャポインタを返す
	return newTexPtr;
}

void Texture::AllClear()
{
	// テクスチャ全消去
	for (size_t i = 0; i < sTexs_.size(); i++)
	{
		sTexs_[i].reset(nullptr);
	}
	sTexs_.clear();
}

void Texture::SetDrawCommand(const UINT rootParamIndex)
{	
	// シェーダーにテクスチャを設定
	Common::spCmdList_->SetGraphicsRootDescriptorTable(rootParamIndex, srvGpuHandle_);
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
	spDevice_ = pDevice;
	spCmdList_ = pCmdList;
	spDescHeap_ = pDescHeap;
}