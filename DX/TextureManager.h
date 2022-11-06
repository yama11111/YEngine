#pragma once
#include "GPUResource.h"
#include <vector>
#include "Vec4.h"

namespace DX
{
	// �e�N�X�`���\����
	struct Texture 
	{
		// �e�N�X�`���o�b�t�@
		GPUResource buff_;
		// SRV�擪�n���h�� (GPU)
		D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle_{};
	};

	class TextureManager
	{
	private:
		// SRV�p�q�[�v
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap_ = nullptr;
		// SRV�擪�n���h�� (CPU)
		D3D12_CPU_DESCRIPTOR_HANDLE srvCpuHandle_{};
		// �e�N�X�`���pvector�z��
		std::vector<Texture> texs_;
		// �f�X�N���v�^�e�[�u���������ԍ��ۑ��p
		UINT rpIndex_ = 0;
	public:
		// ������
		void Initialize();
		// �e�N�X�`������
		UINT CreateTex(const Math::Vec4& color = { 1.0f,1.0f,1.0f,1.0f });
		// �e�N�X�`�����[�h
		UINT Load(const wchar_t* fileName, const bool mipMap = true);
		// SRV�`��O�R�}���h (�ŏ��Ɉ��)
		void SetSRVDrawCommand();
		// �e�N�X�`���`��O�R�}���h 
		void SetDrawCommand(const UINT texIndex);
	private:
		// �e�N�X�`���ݒ�
		void SetTexture(Texture& tex, D3D12_SHADER_RESOURCE_VIEW_DESC* srvDesc);
	public:
		// �f�X�N���v�^�[�e�[�u���ԍ��ݒ�
		void SetRootParameterIndex(UINT rpIndex) { rpIndex_ = rpIndex; }
	private:
		// �ő�e�N�X�`����
		static const UINT MaxSRVCount_ = 2056;
		// �������s�N�Z����
		static const size_t textureWidth = 1;
		// �c�����s�N�Z����
		static const size_t textureHeight = 1;
		// �z��̗v�f��
		static const size_t imageDataCount = textureWidth * textureHeight;
		// �ÓI�f�o�C�X�|�C���^
		static ID3D12Device* pDevice_;
		// �ÓI�R�}���h���X�g�|�C���^
		static ID3D12GraphicsCommandList* pCmdList_;
	public:
		// �ÓI������
		static void StaticInitialize(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCommandList);
	};
}

