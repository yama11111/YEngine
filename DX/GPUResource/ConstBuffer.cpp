#include "ConstBuffer.h"

namespace DG = DX::GPUResource;

void DG::ConstBufferMaterial::Color(const Math::Vec4& color)
{
	mapMate->color = color;
}

void DG::ConstBufferTransform::Mat(const Math::Mat4& mat)
{
	mapTrfm->mat = mat;
}
