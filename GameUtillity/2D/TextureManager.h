#pragma once
#include "GPUResource.h"
#include "DescriptorHeap.h"
#include "Vector4.h"
#include <vector>
#include <string>

namespace YGame
{
	// �e�N�X�`���\����
	struct Texture 
	{
		// �e�N�X�`���o�b�t�@
		YDX::GPUResource buff_;
		// SRV�n���h�� (CPU)
		D3D12_CPU_DESCRIPTOR_HANDLE srvCpuHandle_{};
		// SRV�n���h�� (GPU)
		D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle_{};
		// �e�N�X�`���t�@�C����
		std::string fileName_;
	};

	// �e�N�X�`���}�l�[�W���[�R�����N���X
	class TextureManagerCommon 
	{
	protected:
		// �������s�N�Z���� (�e�N�X�`�������p)
		static const size_t textureWidth = 1;
		// �c�����s�N�Z���� (�e�N�X�`�������p)
		static const size_t textureHeight = 1;
		// �z��̗v�f�� (�e�N�X�`�������p)
		static const size_t imageDataCount = textureWidth * textureHeight;
	protected:
		// �ÓI�f�o�C�X�|�C���^
		static ID3D12Device* pDevice_;
		// �ÓI�R�}���h���X�g�|�C���^
		static ID3D12GraphicsCommandList* pCmdList_;
		// �ÓI�f�X�N���v�^�[�q�[�v
		static YDX::DescriptorHeap* pDescHeap_;
	public:
		// �ÓI�������ݒ�
		struct StaticInitStatus
		{
			ID3D12Device* pDevice_; // �f�o�C�X�|�C���^
			ID3D12GraphicsCommandList* pCmdList_; // �R�}���h���X�g�|�C���^
			YDX::DescriptorHeap* pDescHeap_; // �f�X�N���v�^�[�q�[�v
		};
	public:
		// �ÓI������
		static void StaticInitialize(const StaticInitStatus& state);
	};

	// �e�N�X�`���}�l�[�W���[�N���X (�V���O���g��)
	class TextureManager : private TextureManagerCommon
	{
	private:
		// �e�N�X�`���pvector�z��
		std::vector<Texture> texs_;
	public:
		/// <summary>
		/// �e�N�X�`������
		/// </summary>
		/// <param name="color"> : �F (0.0 ~ 1.0)</param>
		/// <returns>�e�N�X�`���ԍ�</returns>
		UINT CreateTex(const YMath::Vector4& color = { 1.0f,1.0f,1.0f,1.0f });
		/// <summary>
		/// �e�N�X�`���ǂݍ���
		/// </summary>
		/// <param name="texFileName"> : �e�N�X�`���t�@�C����</param>
		/// <param name="mipMap"> : �~�b�v�}�b�v�𐶐����邩</param>
		/// <returns>�e�N�X�`���ԍ�</returns>
		UINT Load(const std::string& texFileName, const bool mipMap = true);
		/// <summary>
		/// �e�N�X�`���ǂݍ��� (�f�B���N�g���p�X�w��ver)
		/// </summary>
		/// <param name="directoryPath"> : �f�B���N�g���p�X��</param>
		/// <param name="texFileName"> : �e�N�X�`���t�@�C����</param>
		/// <param name="mipMap"> : �~�b�v�}�b�v�𐶐����邩</param>
		/// <returns>�e�N�X�`���ԍ�</returns>
		UINT Load(const std::string& directoryPath, const std::string texFileName, const bool mipMap = true);
		/// <summary>
		/// �e�N�X�`���`��O�R�}���h (�V�F�[�_�[�ɓ]��)
		/// </summary>
		/// <param name="rootParamIndex"> : ���[�g�p�����[�^�ԍ�</param>
		/// <param name="texIndex"> : �e�N�X�`���ԍ�</param>
		void SetDrawCommand(const UINT rootParamIndex, const UINT texIndex);
	public:
		/// <summary>
		/// �e�N�X�`���o�b�t�@�擾
		/// </summary>
		/// <param name="texIndex"> : �e�N�X�`���ԍ�</param>
		/// <returns>�Ή�����e�N�X�`���̃o�b�t�@</returns>
		ID3D12Resource* TextureBuffer(const UINT texIndex);
	public:
		// �C���X�^���X�擾
		static TextureManager* GetInstance();
	private:
		TextureManager() = default;
		~TextureManager() = default;
		TextureManager(const TextureManager&) = delete;
		const TextureManager& operator=(const TextureManager&) = delete;
	};
}

