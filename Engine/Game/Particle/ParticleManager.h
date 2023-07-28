#pragma once
#include "BaseParticle.h"
#include <list>

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
		/// �}��
		/// </summary>
		/// <param name="newParticle"> : �p�[�e�B�N�� (���I�C���X�^���X)</param>
		void PushBack(BaseParticle* newParticle);

		/// <summary>
		/// �X�V
		/// </summary>
		void Update();

		/// <summary>
		/// �`��
		/// </summary>
		void Draw();

	private:

		// �p�[�e�B�N�����X�g
		std::list<std::unique_ptr<BaseParticle>> particles_;

	private:

		ParticleManager() = default;

		~ParticleManager() = default;

		ParticleManager(const ParticleManager&) = delete;

		const ParticleManager& operator=(const ParticleManager&) = delete;
	};
}

