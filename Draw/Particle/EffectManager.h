#pragma once
#include "Effect.h"

namespace YGame
{
	// �G�t�F�N�g�}�l�[�W���[
	class EffectManager
	{
	private:
		// �G�t�F�N�g���X�g
		std::list<std::unique_ptr<IEffect>> effects_;
	public:
		// ������
		void Initialize();
		// �X�V
		void Update();
		// �`��
		void Draw();
	public:
		// �ÓI������
		static void StaticInitialize(ParticleManager* pParticleMan);
	};
}

