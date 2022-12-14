#pragma once
#include "GPUResource.h"
#include "SRVHeap.h"
#include "Vec4.h"
#include <vector>
#include <string>

namespace Game
{
	// �e�N�X�`���\����
	struct Texture 
	{
		// �e�N�X�`���o�b�t�@
		DX::GPUResource buff_;
		// SRV�擪�n���h�� (CPU)
		D3D12_CPU_DESCRIPTOR_HANDLE srvCpuHandle_{};
		// SRV�擪�n���h�� (GPU)
		D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle_{};
		// �e�N�X�`���t�@�C����
		std::string fileName_;
	};

	class TextureManager
	{
	private:
		// �e�N�X�`���pvector�z��
		std::vector<Texture> texs_;
		// �f�X�N���v�^�e�[�u���������ԍ��ۑ��p
		UINT rpIndex_ = 0;
	public:
		// �e�N�X�`������
		UINT CreateTex(const Math::Vec4& color = { 1.0f,1.0f,1.0f,1.0f });
		// �e�N�X�`���ǂݍ���
		UINT Load(const std::string& texFileName, const bool mipMap = true);
		// �e�N�X�`���ǂݍ���(���f���p)
		UINT Load(const std::string& directoryPath, const std::string texFileName, const bool mipMap = true);
		// �e�N�X�`���`��O�R�}���h 
		void SetDrawCommand(const UINT texIndex);
	public:
		// �f�X�N���v�^�[�e�[�u���ԍ��ݒ�
		void SetRootParameterIndex(UINT rpIndex) { rpIndex_ = rpIndex; }
		// �e�N�X�`���o�b�t�@�擾
		ID3D12Resource* TextureBuffer(const UINT texIndex);
	private:
		// �e�N�X�`���ݒ�
		void SetTexture(Texture& tex, D3D12_SHADER_RESOURCE_VIEW_DESC* srvDesc);
		// �g���q�擾
		static std::string FileExtension(const std::string path);
	private:
		// �������s�N�Z����
		static const size_t textureWidth = 1;
		// �c�����s�N�Z����
		static const size_t textureHeight = 1;
		// �z��̗v�f��
		static const size_t imageDataCount = textureWidth * textureHeight;
	private:
		// �ÓI�f�o�C�X�|�C���^
		static ID3D12Device* pDevice_;
		// �ÓI�R�}���h���X�g�|�C���^
		static ID3D12GraphicsCommandList* pCmdList_;
		// �ÓI�V�F�[�_�[���\�[�X�q�[�v�N���X
		static DX::SRVHeap* pSrvHeap_;
	public:
		// �ÓI������
		static void StaticInitialize(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCommandList, DX::SRVHeap* pSrvHeap);
	};
}

