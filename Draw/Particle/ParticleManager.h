#pragma once
#include "Particle.h"
#include <list>
#include <memory>

namespace YGame
{
	class ParticleManager
	{
	private:
		std::list<std::unique_ptr<IParticle>> particles_;
	public:
		void Initialize();
		void Update();
		void Draw();
	public:
		void EmitFireSpark(
			const YMath::Vector3& pos, 
			const YMath::Vector3& range, 
			const float maxScale, 
			const YMath::Vector3& speed, 
			const YMath::Vector4& color, 
			const uint32_t frame, const size_t num);
	public:
		static YGame::Model* pModel_;
	public:
		static void StaticInitialize(YGame::Model* pModel);
	};
}

