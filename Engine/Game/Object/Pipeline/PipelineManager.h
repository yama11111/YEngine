#pragma once
#include "Pipeline.h"

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
		/// �`������L���[�ɐς�
		/// </summary>
		/// <param name="key"> : �L�[ (�p�C�v���C����)</param>
		/// <param name="priority"> : �D��x</param>
		/// <param name="pObj"> : �I�u�W�F�N�g�|�C���^</param>
		void EnqueueDrawSet(const std::string& key, const uint32_t priority, Object* pObj);

		/// <summary>
		/// �w�肵���p�C�v���C����`��
		/// </summary>
		/// <param name="key"> : �L�[</param>
		void Draw(const std::string& key);

	private:

		// �p�C�v���C���i�[�z��
		std::unordered_map<
			std::string,
			std::unique_ptr<Pipeline>> pipelines_;

	private:

		PipelineManager() = default;

		~PipelineManager() = default;

		PipelineManager(const PipelineManager&) = delete;

		const PipelineManager& operator=(const PipelineManager&) = delete;

	};
}

