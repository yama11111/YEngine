#include "TextureManager.h"
#include "FileUtillity.h"
#include "YAssert.h"
#include <DirectXTex.h>

#pragma region ���O���

using YGame::Texture;
using YGame::TextureManagerCommon;
using YGame::TextureManager;
using YDX::GPUResource;
using YMath::Vector4;
using YDX::Result;

#pragma endregion

#pragma region Static

ID3D12Device* TextureManagerCommon::pDevice_ = nullptr;
ID3D12GraphicsCommandList* TextureManagerCommon::pCmdList_ = nullptr;
YDX::DescriptorHeap* TextureManagerCommon::pDescHeap_ = nullptr;

#pragma endregion

void TextureManagerCommon::StaticInitialize(const StaticInitStatus& state)
{
	// null�`�F�b�N
	assert(state.pDevice_);
	assert(state.pCmdList_);
	assert(state.pDescHeap_);

	// ���
	pDevice_ = state.pDevice_;
	pCmdList_ = state.pCmdList_;
	pDescHeap_ = state.pDescHeap_;
}

TextureManager* TextureManager::GetInstance()
{
	// �C���X�^���X���� (�ÓI)
	static TextureManager instance;

	// �C���X�^���X��Ԃ�
	return &instance;
}

UINT TextureManager::CreateTex(const Vector4& color)
{
	// �e�N�X�`�����
	Texture tex;

	// �摜�C���[�W�f�[�^�z��
	Vector4* imageData = new Vector4[imageDataCount]; // ���K����ŊJ������

	// �S�s�N�Z���̐F��������
	for (size_t i = 0; i < imageDataCount; i++)
	{
		imageData[i].r_ = color.r_; // R
		imageData[i].g_ = color.g_; // G
		imageData[i].b_ = color.b_; // B
		imageData[i].a_ = color.a_; // A
	}

	// �����p���
	GPUResource::CreateStatus texState;
	// �q�[�v�ݒ�
	//texState.heapProp_.Type = D3D12_HEAP_TYPE_DEFAULT;
	texState.heapProp_.Type = D3D12_HEAP_TYPE_CUSTOM;
	texState.heapProp_.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	texState.heapProp_.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	// ���\�[�X�ݒ�
	texState.resDesc_.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	texState.resDesc_.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	texState.resDesc_.Width = textureWidth;   // ��
	texState.resDesc_.Height = textureHeight; // ����
	texState.resDesc_.DepthOrArraySize = 1;
	texState.resDesc_.MipLevels = 1;
	texState.resDesc_.SampleDesc.Count = 1;

	// �e�N�X�`���o�b�t�@����
	tex.buff_.Create(texState);

	// �e�N�X�`���o�b�t�@�Ƀf�[�^�]��
	Result(tex.buff_.Get()->WriteToSubresource(
		0,
		nullptr, // �S�̈�փR�s�[
		imageData, // ���f�[�^�A�h���X
		sizeof(Vector4) * textureWidth, // 1���C���T�C�Y
		sizeof(Vector4) * imageDataCount // �S�T�C�Y
	));

	// �f�[�^�J��
	delete[] imageData;

	// �V�F�[�_���\�[�X�r���[�ݒ�
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = texState.resDesc_.Format;  // RGBA float
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; // 2D�e�N�X�`��
	srvDesc.Texture2D.MipLevels = 1;

	// �e�N�X�`���ݒ�
	pDescHeap_->CreateSRV(tex.buff_.Get(), srvDesc, tex.srvCpuHandle_, tex.srvGpuHandle_);

	// �e�N�X�`����ۑ�
	texs_.push_back(tex);

	// �e�N�X�`���ԍ���Ԃ�
	return static_cast<UINT>(texs_.size() - 1);
}

UINT TextureManager::Load(const std::string& texFileName, const bool mipMap)
{
	// �f�B���N�g���p�X��ݒ�
	const std::string& directoryPath = "Resources/Textures/";
	
	// �e�N�X�`���ǂݍ���
	return Load(directoryPath, texFileName, mipMap);
}

UINT TextureManager::Load(const std::string& directoryPath, const std::string texFileName, const bool mipMap)
{
	// �e�N�X�`�����
	Texture tex;

	DirectX::TexMetadata metadata{};
	DirectX::ScratchImage scratchImg{};

	// �t�@�C����
	std::string filePath = directoryPath + texFileName;
	std::wstring wFilePath = std::wstring(filePath.begin(), filePath.end());
	const wchar_t* fileName = wFilePath.c_str();

	// �g���q�擾
	std::string ext = YUtil::FileExtension(texFileName);

	if (ext == "png") // png �� WIC
	{
		// WIC�e�N�X�`���̃��[�h
		Result(LoadFromWICFile(fileName, DirectX::WIC_FLAGS_NONE, &metadata, scratchImg));
	}
	else if (ext == "tga") // tga �� TGA
	{
		// TGA�e�N�X�`���̃��[�h
		Result(LoadFromTGAFile(fileName, &metadata, scratchImg));
	}

	DirectX::ScratchImage mipChain{};
	// �~�b�v�}�b�v����
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

	//�ǂݍ��񂾃f�B�t���[�Y�e�N�X�`���� SRGB �Ƃ��Ĉ���
	metadata.format = DirectX::MakeSRGB(metadata.format);

	// �����p���
	GPUResource::CreateStatus texState;
	// �q�[�v�ݒ�
	//texState.heapProp_.Type = D3D12_HEAP_TYPE_DEFAULT;
	texState.heapProp_.Type = D3D12_HEAP_TYPE_CUSTOM;
	texState.heapProp_.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	texState.heapProp_.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	// ���\�[�X�ݒ�
	texState.resDesc_.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	texState.resDesc_.Format = metadata.format;
	texState.resDesc_.Width = metadata.width;   // ��
	texState.resDesc_.Height = (UINT)metadata.height; // ����
	texState.resDesc_.DepthOrArraySize = (UINT16)metadata.arraySize;
	texState.resDesc_.MipLevels = (UINT16)metadata.mipLevels;
	texState.resDesc_.SampleDesc.Count = 1;

	// �e�N�X�`���o�b�t�@����
	tex.buff_.Create(texState);

	// �e�N�X�`���o�b�t�@�Ƀf�[�^�]��
	//�S�~�b�v�}�b�v�ɂ���
	for (size_t i = 0; i < metadata.mipLevels; i++)
	{
		// �~�b�v�}�b�v���w�肵�ăC���[�W�擾
		const DirectX::Image* img = scratchImg.GetImage(i, 0, 0);
		// �e�N�X�`���o�b�t�@�Ƀf�[�^�]��
		Result(tex.buff_.Get()->WriteToSubresource(
			(UINT)i,
			nullptr, // �S�̈�փR�s�[
			img->pixels, // ���f�[�^�A�h���X
			(UINT)img->rowPitch, // 1���C���T�C�Y
			(UINT)img->slicePitch // 1���T�C�Y
		));
	}

	// �V�F�[�_���\�[�X�r���[�ݒ�
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = texState.resDesc_.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; // 2D�e�N�X�`��
	srvDesc.Texture2D.MipLevels = texState.resDesc_.MipLevels;

	// �e�N�X�`���ݒ�
	pDescHeap_->CreateSRV(tex.buff_.Get(), srvDesc, tex.srvCpuHandle_, tex.srvGpuHandle_);
	tex.fileName_ = texFileName;

	// �e�N�X�`����ۑ�
	texs_.push_back(tex);

	// �e�N�X�`���ԍ���Ԃ�
	return static_cast<UINT>(texs_.size() - 1);
}

void TextureManager::SetDrawCommand(const UINT rootParamIndex, const UINT texIndex)
{
	// �e�N�X�`���ԍ��� 0 �ȏ� �ő�l �ȉ��łȂ��Ȃ�x��
	assert((0 <= texIndex && texIndex < texs_.size()));
	
	// �V�F�[�_�[�Ƀe�N�X�`����ݒ�
	pCmdList_->SetGraphicsRootDescriptorTable(rootParamIndex, texs_[texIndex].srvGpuHandle_);
}

ID3D12Resource* TextureManager::TextureBuffer(const UINT texIndex)
{
	// �e�N�X�`���ԍ��� 0 �ȏ� �ő�l �ȉ��łȂ��Ȃ�x��
	assert((0 <= texIndex && texIndex < texs_.size()));
	
	// �e�N�X�`���o�b�t�@��Ԃ�
	return texs_[texIndex].buff_.Get();
}
