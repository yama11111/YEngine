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
		// �F�ւ��p
		void EmitFireWorks(
			const uint32_t frame, const size_t num, 
			const YMath::Vector3& pos, const float scale,
			const YMath::Vector4& color);
	public:
		// �ÓI������
		static void StaticInitialize(YGame::ViewProjection* pVP);
	public:
		~ParticleManager() = default;
	};
}

