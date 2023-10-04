#pragma once
#include "Pipeline.h"
#include "PostEffect.h"

namespace YGame
{
	class PipelineManager
	{

	public:
		
		/// <summary>
		/// �V���O���g���C���X�^���X�|�C���^�擾
		/// </summary>
		/// <returns>�C���X�^���X�|�C���^</returns>
		static PipelineManager* GetInstance();
	
	public:

		/// <summary>
		/// �N���A
		/// </summary>
		void Clear();

		/// <summary>
		/// �}��
		/// </summary>
		/// <param name="key"> : �L�[</param>
		/// <param name="pipeline"> : �p�C�v���C�� (���I�C���X�^���X)</param>
		void Insert(const std::string& key, Pipeline* pipeline);

		/// <summary>
		/// �p�C�v���C���̕`�揇
		/// </summary>
		/// <param name="pipelineKeys">�p�C�v���C���L�[vector�z��</param>
		void SetDrawOrder(const std::vector<std::string> pipelineKeys);

		/// <summary>
		/// �`������L���[�ɐς�
		/// </summary>
		/// <param name="key"> : �L�[ (�p�C�v���C����)</param>
		/// <param name="priority"> : �D��x</param>
		/// <param name="drawSet"> : �`��Z�b�g</param>
		/// <param name="-----------------------------------------"></param>
		/// <param name="(ConstBufferPtrSet*) pCBPtrSet"> : �萔�o�b�t�@�|�C���^�Z�b�g�|�C���^</param>
		/// <param name="(BaseGraphic*) pGraphic"> : �O���t�B�b�N�|�C���^</param>
		void EnqueueDrawSet(const std::string& key, const size_t priority, const Pipeline::DrawSet& drawSet);
		
		/// <summary>
		/// �|�X�g�G�t�F�N�g�ɏ�������
		/// </summary>
		/// <param name="pPostEffect"> : �|�X�g�G�t�F�N�g�|�C���^vector�z��</param>
		void RenderToPostEffect(std::vector<PostEffect*> pPostEffects);
		
		/// <summary>
		/// �`��
		/// </summary>
		void Draw();

	private:

		// �p�C�v���C���i�[�z��
		std::unordered_map<
			std::string,
			std::unique_ptr<Pipeline>> pipelines_;

		// �`�揇
		std::vector<std::string> drawOrder_;

	private:

		PipelineManager() = default;

		~PipelineManager() = default;

		PipelineManager(const PipelineManager&) = delete;

		const PipelineManager& operator=(const PipelineManager&) = delete;

	};
}

