#pragma once
#include "Transform.h"
#include "ViewProjection.h"
#include "Object.h"
#include "ConstBuffer.h"
#include "CBSprite2DTransform.h"
#include "CBColor.h"
#include "CBTexConfig.h"
#include "Sprite2D.h"

namespace YGame
{
	class Floor
	{
		
	public:

		std::unique_ptr<Transform> transform_;

		std::unique_ptr<Object> obj_;

		std::unique_ptr<ConstBuffer<CBSprite2DTransform::CBData>> cbTransform_;
		
		std::unique_ptr<ConstBuffer<CBColor::CBData>> cbColor_;
		
		std::unique_ptr<ConstBuffer<CBTexConfig::CBData>> cbTexConfig_;
		
		Sprite2D* pSprite2D_ = nullptr;
	
	public:

		void Initialize(const Transform::Status& status = Transform::Status::Default());
		
		void Update();

		void Draw(const std::string& key);
	};
}
