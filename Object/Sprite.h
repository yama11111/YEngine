#pragma once
#include "Transform.h"
#include "GPUResource/Vertices2D.h"
#include "GPUResource/TextureManager.h"
#include "MatProjection.h"

namespace Object
{
	class Sprite
	{
	public:
		const Math::Vec2 size;
	private:
		DX::GPUResource::Vertices2D vt;
	public:
		Sprite(const Math::Vec2& size);
		void Draw(Transform& trfm, const UINT tex);
	private:
		static MatProjection mP;
		static DX::GPUResource::TextureManager* texManager;
	public:
		static void StaticInit();
	};
}
