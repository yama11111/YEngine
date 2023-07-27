#pragma once
#include "GPUResource.h"
#include "DescriptorHeap.h"
#include "Vector4.h"
#include <vector>
#include <string>
#include <memory>

namespace YGame
{
	// �e�N�X�`��
	class Texture
	{
		
	private:
		
		// �e�N�X�`���o�b�t�@
		YDX::GPUResource buff_;
		
		// SRV�n���h�� (CPU)
		D3D12_CPU_DESCRIPTOR_HANDLE srvCpuHandle_{};
		
		// SRV�n���h�� (GPU)
		D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle_{};
	
		// �e�N�X�`���t�@�C����
		std::string fileName_;

	private:
		
		// �ÓI�e�N�X�`���i�[�pvector�z��
		static std::vector<std::unique_ptr<Texture>> sTexs_;

	public:
		
		/// <summary>
		/// �e�N�X�`������
		/// </summary>
		/// <param name="color"> : �F (0.0 ~ 1.0)</param>
		/// <returns>�e�N�X�`���|�C���^</returns>
		static Texture* Create(const YMath::Vector4& color = { 1.0f,1.0f,1.0f,1.0f });

		/// <summary>
		/// �����_�[�e�N�X�`������
		/// </summary>
		/// <returns>�e�N�X�`���|�C���^</returns>
		static Texture* CreateRender();

		/// <summary>
		/// �e�N�X�`���ǂݍ���
		/// </summary>
		/// <param name="texFileName"> : �e�N�X�`���t�@�C����</param>
		/// <param name="mipMap"> : �~�b�v�}�b�v�𐶐����邩</param>
		/// <returns>�e�N�X�`���|�C���^</returns>
		static Texture* Load(const std::string& texFileName, const bool mipMap = true);

		/// <summary>
		/// �e�N�X�`���ǂݍ��� (�f�B���N�g���p�X�w��ver)
		/// </summary>
		/// <param name="directoryPath"> : �f�B���N�g���p�X��</param>
		/// <param name="texFileName"> : �e�N�X�`���t�@�C����</param>
		/// <param name="mipMap"> : �~�b�v�}�b�v�𐶐����邩</param>
		/// <returns>�e�N�X�`���|�C���^</returns>
		static Texture* Load(const std::string& directoryPath, const std::string texFileName, const bool mipMap = true);

		/// <summary>
		/// �S�폜
		/// </summary>
		static void AllClear();

	public:

		/// <summary>
		/// �`��R�}���h (�V�F�[�_�[�ɓ]��)
		/// </summary>
		/// <param name="rootParamIndex"> : ���[�g�p�����[�^�ԍ�</param>
		void SetDrawCommand(const UINT rootParamIndex);
	
		/// <summary>
		/// �e�N�X�`���o�b�t�@�擾
		/// </summary>
		ID3D12Resource* Buffer();

	public:
		
		// �R�����N���X
		class Common
		{
		public:

			// �ÓI�f�o�C�X�|�C���^
			static ID3D12Device* spDevice_;
			
			// �ÓI�R�}���h���X�g�|�C���^
			static ID3D12GraphicsCommandList* spCmdList_;
			
			// �ÓI�f�X�N���v�^�[�q�[�v
			static YDX::DescriptorHeap* spDescHeap_;

		public:

			/// <summary>
			/// �ÓI������
			/// </summary>
			/// <param name="pDevice"> : �f�o�C�X�|�C���^</param>
			/// <param name="pCmdList"> : �R�}���h���X�g�|�C���^</param>
			/// <param name="pDescHeap"> : �f�X�N���v�^�[�q�[�v�|�C���^</param>
			static void StaticInitialize(
				ID3D12Device* pDevice, 
				ID3D12GraphicsCommandList* pCmdList, 
				YDX::DescriptorHeap* pDescHeap);

		public:

			Common() = default;

			~Common() = default;

		};

	public:

		Texture() = default;

		~Texture() = default;
	};
}

