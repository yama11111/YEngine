#pragma once
#include "ParticleManager.h"

namespace YGame
{
	// �G�t�F�N�g���N���X
	class IEffect
	{
	public:
		// �����t���O
		bool isAlive_ = false;
	public:
		// �X�V
		virtual void Update() = 0;
		// �`��
		virtual void Draw() = 0;
	protected:
		// �ÓI�p�[�e�B�N���}�l�[�W���[�|�C���^
		static ParticleManager* spParticleMan_;
	public:
		// �ÓI������
		static void StaticInitialize(ParticleManager* pParticleMan);
	public:
		// �f�X�g���N�^
		virtual ~IEffect() = default;
	};
}

