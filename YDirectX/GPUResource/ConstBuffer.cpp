#include "ConstBuffer.h"

namespace DG = DX::GPUResource;

void DG::ConstBufferMaterial::Color(const Vec4& color)
{
	cMapMate->color = color;
}

void DG::ConstBufferTransform::Mat(const Mat4& mat)
{
	cMapTrfm->mat = mat;
}
