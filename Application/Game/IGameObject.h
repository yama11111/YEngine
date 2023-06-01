#pragma once
#include "Model.h"

namespace YGame
{
	class IGameObject
	{
	
	public:

	public:

		IGameObject() = default;
		
		~IGameObject() = default;

	protected:

		// 核
		std::unique_ptr<Transform> core_;

		// 3D用オブジェクト
		std::unique_ptr<Model::Object> obj3D_;

		// モデルポインタ
		Model* pModel_ = nullptr;
	};
}

