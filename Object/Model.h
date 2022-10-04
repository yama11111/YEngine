#pragma once
#include "Transform.h"
#include "MatViewProjection.h"
#include "GPUResource/VertexIndex.h"
#include "GPUResource/TextureManager.h"

namespace Object
{
	class Model
	{
	private:
		DX::GPUResource::VertexIndex vtIdx;
	public:
		Model();
		void Draw(Transform& trfm, MatViewProjection& vp, const UINT tex);
	private:
		static DX::GPUResource::TextureManager* texManager;
	public:
		static void StaticInit();
	};
}
