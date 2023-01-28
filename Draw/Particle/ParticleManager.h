#pragma once
#include "Particle.h"
#include <list>
#include <memory>

namespace YParticle
{
	class ParticleManager
	{
	private:
		std::list<std::unique_ptr<IParticle>> particles_;
	public:
		void Initialize();
		void Update();
		void Draw(const YGame::ViewProjection& vp);
	public:
		void EmitDust(YMath::Vec3& pos, YMath::Vec3& direction, uint32_t frame, size_t num);
		void EmitExprosion(YMath::Vec3& pos, float speed, YMath::Vec4 color, uint32_t frame, size_t num);
		void EmitEruption(YMath::Vec3& pos, YMath::Vec3& direction, uint32_t frame, size_t num);
	public:
		static YGame::Model* pModel_;
	public:
		struct StaticInitStatus
		{
			YGame::Model* pModel_;
		};
	public:
		static void StaticInitialize(const StaticInitStatus& state);
	};
}

