#pragma once
#include "Particle.h"
#include <list>

namespace YGame
{
	// �p�[�e�B�N���}�l�[�W���[
	class ParticleManager
	{
	private:
		// �p�[�e�B�N�����X�g
		std::list<std::unique_ptr<IParticle>> particles_;
	public:
		// ������
		void Initialize();
		// �X�V
		void Update();
		// �`��
		void Draw();
	public:
		// �ÓI������
		static void StaticInitialize(YGame::ViewProjection* pVP);
	public:
		~ParticleManager() = default;
	};
}

