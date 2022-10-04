#pragma once
#include "Model.h"

namespace Object
{
	class Ray
	{
	public:
		Transform trfm{};
		Math::Vec3 start{};
		Math::Vec3 velocity = { 0,0,1 };
		float length = 1.0f;
		Model* model = nullptr;
		UINT tex = 0;
	public:
		struct InitRay
		{
			Math::Vec3 start = { 0,0,0 };
			Math::Vec3 velocity = { 0,0,1 };
			float length = 1.0f;
		};
		void Initialize(const InitRay& init, Model* model, const UINT tex);
		void InitState(const InitRay& init);
		void Update();
		void Draw(MatViewProjection& vp);
		void SetStart(const Math::Vec3& start);
		void SetVelocity(const Math::Vec3& velocity);
		void SetLength(const float length);
	private:
		void Adjust();
	};
}
