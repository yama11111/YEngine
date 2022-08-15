#include "ConstBuffer.h"

void ConstBufferMaterial::Color(const Vec4& color)
{
	cMapMate->color = color;
}

void ConstBufferTransform::Mat(const Mat4& mat)
{
	cMapTrfm->mat = mat;
}
