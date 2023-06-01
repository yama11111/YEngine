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

		// �j
		std::unique_ptr<Transform> core_;

		// 3D�p�I�u�W�F�N�g
		std::unique_ptr<Model::Object> obj3D_;

		// ���f���|�C���^
		Model* pModel_ = nullptr;
	};
}

