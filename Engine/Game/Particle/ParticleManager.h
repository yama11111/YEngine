#pragma once
#include "BaseParticle.h"
#include <array>

namespace YGame
{
	// �p�[�e�B�N���}�l�[�W���[
	class ParticleManager
	{

	public:

		/// <summary>
		/// �V���O���g���C���X�^���X�|�C���^�擾
		/// </summary>
		/// <returns>�C���X�^���X�|�C���^</returns>
		static ParticleManager* GetInstance();

	public:

		/// <summary>
		/// �N���A
		/// </summary>
		void Clear();

		/// <summary>
		/// �p�[�e�B�N����}������
		/// </summary>
		/// <param name="tag"> : �p�[�e�B�N���^�O</param>
		/// <param name="particles"> : �p�[�e�B�N���|�C���^�z��</param>
		void InsertParticles(const std::string& tag, const std::list<BaseParticle*>& particles);

		/// <summary>
		/// �X�V
		/// </summary>
		void Update();

		/// <summary>
		/// �`��
		/// </summary>
		void Draw();

	private:

		// �p�[�e�B�N���|�C���^�}�b�v
		std::unordered_map<
			std::string, 
			std::list<BaseParticle*>> particles_;

	private:

		ParticleManager() = default;

		~ParticleManager() = default;

		ParticleManager(const ParticleManager&) = delete;

		const ParticleManager& operator=(const ParticleManager&) = delete;
	};
}

