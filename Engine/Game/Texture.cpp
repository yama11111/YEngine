#include "Texture.h"
#include "FileUtillity.h"
#include "YAssert.h"
#include "Def.h"
#include <DirectXTex.h>

#pragma region ���O���

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
	// �e�N�X�`������
	unique_ptr<Texture> newTex = std::make_unique<Texture>();

	// �������s�N�Z����
	static const size_t textureWidth = 1;
	// �c�����s�N�Z����
	static const size_t textureHeight = 1;
	// �z��̗v�f��
	static const size_t imageDataCount = textureWidth * textureHeight;

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

	// �q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};
	//heapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
	heapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	
	// ���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	resDesc.Width = (UINT16)textureWidth;   // ��
	resDesc.Height = (UINT)textureHeight; // ����
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;

	// �e�N�X�`���o�b�t�@����
	newTex->buff_.Create(&heapProp, &resDesc);

	// �e�N�X�`���o�b�t�@�Ƀf�[�^�]��
	Result(newTex->buff_.Get()->WriteToSubresource(
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
	srvDesc.Format = resDesc.Format;  // RGBA float
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; // 2D�e�N�X�`��
	srvDesc.Texture2D.MipLevels = 1;

	// SRV����
	DescriptorHeap::Handle handle{};
	handle = Common::spDescHeap_->CreateSRV(newTex->buff_.Get(), srvDesc, false);

	// �n���h�����
	newTex->srvCpuHandle_ = handle.cpu_;
	newTex->srvGpuHandle_ = handle.gpu_;


	// �|�C���^���l��
	Texture* newTexPtr = newTex.get();

	// �e�N�X�`����ۑ�
	sTexs_.push_back(std::move(newTex));

	// �e�N�X�`���|�C���^��Ԃ�
	return newTexPtr;
}

Texture* Texture::CreateRender()
{
	// �e�N�X�`������
	unique_ptr<Texture> newTex = std::make_unique<Texture>();

	// �������s�N�Z����
	static const size_t textureWidth = static_cast<size_t>(WinSize.x_);
	// �c�����s�N�Z����
	static const size_t textureHeight = static_cast<size_t>(WinSize.y_);
	// �z��̗v�f��
	static const size_t imageDataCount = textureWidth * textureHeight;

	// �摜�C���[�W�f�[�^�z��
	UINT* imageData = new UINT[imageDataCount]; // ���K����ŊJ������

	// �S�s�N�Z���̐F��������
	for (size_t i = 0; i < imageDataCount; i++)
	{
		imageData[i] = 0xffffffff;
	}

	// �q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};
	heapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	
	// ���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	resDesc.Width = (UINT16)textureWidth;   // ��
	resDesc.Height = (UINT)textureHeight; // ����
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
	
	// ���\�[�X�X�e�[�g�ݒ�
	D3D12_RESOURCE_STATES resState = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
	
	// �N���A�ݒ�
	D3D12_CLEAR_VALUE clearValue{};
	clearValue.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	//clearValue.Color[0] = ClearColor.r_;
	//clearValue.Color[1] = ClearColor.g_;
	//clearValue.Color[2] = ClearColor.b_;
	//clearValue.Color[3] = ClearColor.a_;
	clearValue.Color[0] = 0.25f;
	clearValue.Color[1] = 0.5f;
	clearValue.Color[2] = 0.1f;
	clearValue.Color[3] = 0.0f;

	// �e�N�X�`���o�b�t�@����
	newTex->buff_.Create(&heapProp, &resDesc, resState, &clearValue);

	// �e�N�X�`���o�b�t�@�Ƀf�[�^�]��
	Result(newTex->buff_.Get()->WriteToSubresource(
		0,
		nullptr, // �S�̈�փR�s�[
		imageData, // ���f�[�^�A�h���X
		sizeof(UINT) * (UINT)textureWidth, // 1���C���T�C�Y
		sizeof(UINT) * (UINT)imageDataCount // �S�T�C�Y
	));

	// �f�[�^�J��
	delete[] imageData;

	// �V�F�[�_���\�[�X�r���[�ݒ�
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = resDesc.Format;  // RGBA float
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; // 2D�e�N�X�`��
	srvDesc.Texture2D.MipLevels = 1;

	// SRV����
	DescriptorHeap::Handle handle{};
	handle = Common::spDescHeap_->CreateSRV(newTex->buff_.Get(), srvDesc, false);

	// �n���h�����
	newTex->srvCpuHandle_ = handle.cpu_;
	newTex->srvGpuHandle_ = handle.gpu_;


	// �|�C���^���l��
	Texture* newTexPtr = newTex.get();

	// �e�N�X�`����ۑ�
	sTexs_.push_back(std::move(newTex));

	// �e�N�X�`���|�C���^��Ԃ�
	return newTexPtr;
}

Texture* Texture::Load(const std::string& texFileName, const bool mipMap)
{
	// �f�B���N�g���p�X��ݒ�
	const std::string& directoryPath = "Resources/Textures/";
	
	// �e�N�X�`���ǂݍ���
	return Load(directoryPath, texFileName, mipMap);
}

Texture* Texture::Load(const std::string& directoryPath, const std::string texFileName, const bool mipMap)
{
	// �ǂݍ��񂾂��Ƃ����邩�`�F�b�N
	for (size_t i = 0; i < sTexs_.size(); i++)
	{
		// �t�@�C���p�X �������Ȃ�
		if( directoryPath + texFileName == sTexs_[i]->fileName_)
		{
			// ���̃e�N�X�`���|�C���^��Ԃ�
			return sTexs_[i].get();
		}
	}

	// �e�N�X�`������
	unique_ptr<Texture> newTex = std::make_unique<Texture>();

	DirectX::TexMetadata metadata{};
	DirectX::ScratchImage scratchImg{};

	// �t�@�C����
	std::string filePath = directoryPath + texFileName;
	std::wstring wFilePath = std::wstring(filePath.begin(), filePath.end());
	const wchar_t* fileName = wFilePath.c_str();

	// �g���q�擾
	std::string ext = YUtil::FileExtension(texFileName);

	if (ext == "png" || ext == "jpg") // png || jpg �� WIC
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

	// �q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};
	//texState.heapProp_.Type = D3D12_HEAP_TYPE_DEFAULT;
	heapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	
	// ���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resDesc.Format = metadata.format;
	resDesc.Width = metadata.width;   // ��
	resDesc.Height = (UINT)metadata.height; // ����
	resDesc.DepthOrArraySize = (UINT16)metadata.arraySize;
	resDesc.MipLevels = (UINT16)metadata.mipLevels;
	resDesc.SampleDesc.Count = 1;

	// �e�N�X�`���o�b�t�@����
	newTex->buff_.Create(&heapProp, &resDesc);

	// �e�N�X�`���o�b�t�@�Ƀf�[�^�]��
	//�S�~�b�v�}�b�v�ɂ���
	for (size_t i = 0; i < metadata.mipLevels; i++)
	{
		// �~�b�v�}�b�v���w�肵�ăC���[�W�擾
		const DirectX::Image* img = scratchImg.GetImage(i, 0, 0);
		// �e�N�X�`���o�b�t�@�Ƀf�[�^�]��
		Result(newTex->buff_.Get()->WriteToSubresource(
			(UINT)i,
			nullptr, // �S�̈�փR�s�[
			img->pixels, // ���f�[�^�A�h���X
			(UINT)img->rowPitch, // 1���C���T�C�Y
			(UINT)img->slicePitch // 1���T�C�Y
		));
	}

	// �V�F�[�_���\�[�X�r���[�ݒ�
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; // 2D�e�N�X�`��
	srvDesc.Texture2D.MipLevels = resDesc.MipLevels;

	// SRV����
	DescriptorHeap::Handle handle{};
	handle = Common::spDescHeap_->CreateSRV(newTex->buff_.Get(), srvDesc, false);

	// �n���h�����
	newTex->srvCpuHandle_ = handle.cpu_;
	newTex->srvGpuHandle_ = handle.gpu_;

	// �f�B���N�g���p�X�� + �t�@�C�������
	newTex->fileName_ = directoryPath + texFileName;


	// �|�C���^���l��
	Texture* newTexPtr = newTex.get();

	// �e�N�X�`����ۑ�
	sTexs_.push_back(std::move(newTex));

	// �e�N�X�`���|�C���^��Ԃ�
	return newTexPtr;
}

void Texture::AllClear()
{
	// �e�N�X�`���S����
	for (size_t i = 0; i < sTexs_.size(); i++)
	{
		sTexs_[i].reset(nullptr);
	}
	sTexs_.clear();
}

void Texture::SetDrawCommand(const UINT rootParamIndex)
{	
	// �V�F�[�_�[�Ƀe�N�X�`����ݒ�
	Common::spCmdList_->SetGraphicsRootDescriptorTable(rootParamIndex, srvGpuHandle_);
}

ID3D12Resource* Texture::Buffer()
{
	// �e�N�X�`���o�b�t�@��Ԃ�
	return buff_.Get();
}

void Texture::Common::StaticInitialize(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCmdList, YDX::DescriptorHeap* pDescHeap)
{
	// null�`�F�b�N
	assert(pDevice);
	assert(pCmdList);
	assert(pDescHeap);

	// ���
	spDevice_ = pDevice;
	spCmdList_ = pCmdList;
	spDescHeap_ = pDescHeap;
}