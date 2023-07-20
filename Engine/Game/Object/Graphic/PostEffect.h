#pragma once
#include "BaseGraphic.h"
#include "Vertices.h"
#include "Texture.h"
#include "ScreenDesc.h"
#include "PipelineSetting.h"
#include "Vector3.h"
#include "Vector2.h"
#include <list>
#include <array>

namespace YGame
{
	// �|�X�g�G�t�F�N�g
	class PostEffect :
		public BaseGraphic
	{

	public:

		// ���_�f�[�^�\����
		struct VData
		{
			YMath::Vector3 pos_; // xyz���W
			YMath::Vector2 uv_;  // uv���W
		};

	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <returns>�|�X�g�G�t�F�N�g�|�C���^</returns>
		static PostEffect* Create();

		/// <summary>
		/// �S�폜
		/// </summary>
		static void AllClear();
		
		/// <summary>
		/// ���f���p�̃p�C�v���C���ݒ�擾
		/// </summary>
		/// <returns>�p�C�v���C���ݒ�</returns>
		static PipelineSetting GetPipelineSetting();

	public:

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="rpIndices"> : ���[�g�p�����[�^��� + �ԍ�</param>
		void SetDrawCommand(std::unordered_map<std::string, uint32_t>& rpIndices) const override;

		/// <summary>
		/// �������݊J�n
		/// </summary>
		void StartRender();

		/// <summary>
		/// �������ݏI��
		/// </summary>
		void EndRender();

	public:

		PostEffect() = default;

		~PostEffect() = default;

	private:

		void CreateRTV();

		void CreateDepthBuff(const YMath::Vector2 & size);

		void CreateDSV();

	private:

		// ���_�f�[�^
		YDX::Vertices<VData> vt_;

		// �e�N�X�`���̐�
		static const size_t kTextureNum_ = 2;

		// �e�N�X�`��
		std::array<Texture*, kTextureNum_> pTexs_;


		// RTV�p�q�[�v
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap_ = nullptr;

		// DSV�p�q�[�v
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap_ = nullptr;

		// �[�x�o�b�t�@
		YDX::GPUResource depthBuff_;

	private:

		// �ÓI�|�X�g�G�t�F�N�g�i�[�pvector�z��
		static std::vector<std::unique_ptr<PostEffect>> sPostEffects_;

	private:

		// �ÓI�f�o�C�X�|�C���^
		static ID3D12Device* spDevice_;

		// �ÓI�R�}���h���X�g�|�C���^
		static ID3D12GraphicsCommandList* spCmdList_;

		// �ÓI�X�N���[���ݒ�|�C���^
		static YDX::ScreenDesc sScreenDesc_;

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		/// <param name="pDevice"> : �f�o�C�X�|�C���^</param>
		/// <param name="pCmdList"> : �R�}���h���X�g�|�C���^</param>
		static void StaticInitialize(
			ID3D12Device * pDevice,
			ID3D12GraphicsCommandList * pCmdList);

	};
}
