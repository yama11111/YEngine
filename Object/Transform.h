#pragma once
#include "GPUResource/ConstBufferManager.h"
#include "MatWorld.h"

namespace Object
{
	class Transform
	{
	public:
		MatWorld mW;
		DX::GPUResource::ConstBufferMaterial cbM;
		DX::GPUResource::ConstBufferTransform cbT;
		MatWorld* parent = nullptr;
	public:
		Transform();
		void Update();
		void SetCommand();
		void Affine(Math::Mat4& view, Math::Mat4& projection);
		void SetParent(MatWorld* parent);
	private:
		static DX::GPUResource::ConstBufferManager* cbManager;
	public:
		static void StaticInit();
	};
}
