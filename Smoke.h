#pragma once
#include "Transform.h"
#include "ViewProjection.h"
#include "Object.h"
#include "ConstBuffer.h"
#include "CBModelTransform.h"
#include "CBTime.h"
#include "CBColor.h"
#include "CBTexConfig.h"
#include "Model.h"

namespace YGame
{
	class Smoke
	{

	public:

		std::unique_ptr<Transform> transform_;

		std::vector<std::unique_ptr<Object>> objs_{};

		std::unique_ptr<ConstBuffer<CBModelTransform::CBData>> cbTransform_;
		
		std::unique_ptr<ConstBuffer<CBTime::CBData>> cbTime_;

		std::unique_ptr<ConstBuffer<CBColor::CBData>> cbColor_;

		std::unique_ptr<ConstBuffer<CBTexConfig::CBData>> cbTexConfig_;

		std::vector<Model*> pModels_{};

	public:

		void Initialize(const Transform::Status& status = Transform::Status::Default());

		void Update(const YGame::ViewProjection& vp);

		void Draw(const std::string& key, const size_t index);
	};
}
