#include "Texture.h"
#include "DXSRVHeap.h"
#include "Result.h"
#include <DirectXTex.h>

void Texture::Create(const Vec4& color)
{
	// �������s�N�Z����
	const size_t textureWidth = 256;
	// �c�����s�N�Z����
	const size_t textureHeight = 256;
	// �z��̗v�f��
	const size_t imageDataCount = textureWidth * textureHeight;
	// �摜�C���[�W�f�[�^�z��
	Vec4* imageData = new Vec4[imageDataCount]; // ���K����ŊJ������

	// �S�s�N�Z���̐F��������
	for (size_t i = 0; i < imageDataCount; i++)
	{
		imageData[i].r = color.r; // R
		imageData[i].g = color.g; // G
		imageData[i].b = color.b; // B
		imageData[i].a = color.a; // A
	}

	// �q�[�v�ݒ�
	texInfo.heapProp;
	texInfo.heapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	texInfo.heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	texInfo.heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	// ���\�[�X�ݒ�
	texInfo.resDesc;
	texInfo.resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	texInfo.resDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	texInfo.resDesc.Width = textureWidth;   // ��
	texInfo.resDesc.Height = textureHeight; // ����
	texInfo.resDesc.DepthOrArraySize = 1;
	texInfo.resDesc.MipLevels = 1;
	texInfo.resDesc.SampleDesc.Count = 1;

	texBuff.Create(texInfo);

	// �e�N�X�`���o�b�t�@�Ƀf�[�^�]��
	Result::Check(texBuff.buff->WriteToSubresource(
		0,
		nullptr, // �S�̈�փR�s�[
		imageData, // ���f�[�^�A�h���X
		sizeof(Vec4) * textureWidth, // 1���C���T�C�Y
		sizeof(Vec4) * imageDataCount // �S�T�C�Y
	));

	// �f�[�^�J��
	delete[] imageData;

	// �V�F�[�_���\�[�X�r���[�ݒ�
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;  // RGBA float
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; // 2D�e�N�X�`��
	srvDesc.Texture2D.MipLevels = 1;

	srvH = DXSRVHeap::GetInstance();
	index = srvH->SetSRV(texBuff.buff, srvDesc);
}

void Texture::Load(const wchar_t* imageName)
{
	TexMetadata metadata{};
	ScratchImage scratchImg{};
	// WIC�e�N�X�`���̃��[�h
	Result::Check(LoadFromWICFile(L"Resources/mario.jpg",
		WIC_FLAGS_NONE, &metadata, scratchImg));

	ScratchImage mipChain{};
	// �~�b�v�}�b�v����
	if (Result::Check(GenerateMipMaps(scratchImg.GetImages(),
		scratchImg.GetImageCount(), scratchImg.GetMetadata(),
		TEX_FILTER_DEFAULT, 0, mipChain)))
	{
		scratchImg = std::move(mipChain);
		metadata = scratchImg.GetMetadata();
	}

	//�ǂݍ��񂾃f�B�t���[�Y�e�N�X�`���� SRGB �Ƃ��Ĉ���
	metadata.format = MakeSRGB(metadata.format);

	TexMetadata metadata2{};
	ScratchImage scratchImg2{};
	// WIC�e�N�X�`���̃��[�h
	Result::Check(LoadFromWICFile(L"Resources/reimu.png",
		WIC_FLAGS_NONE, &metadata2, scratchImg2));
}

void Texture::SetCommand()
{
	srvH->SetRootParameter(index);
}
