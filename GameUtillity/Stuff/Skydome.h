#pragma once
#include "Model.h"

namespace YGame
{
	class Skydome
	{
	private:
		std::unique_ptr<ObjectModel> obj_;
		YMath::Vector3* pPos_ = nullptr;
		YGame::Model* pModel_ = nullptr;
	public:
		void Initialize(const BaseObject::Status state, YGame::Model* model);
		void Update();
		void Draw(YGame::ViewProjection& vp, YGame::LightGroup* lightGroup, YGame::Color* color);
	};
}
