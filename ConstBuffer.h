#pragma once
#include "DXResource.h"
#include "Vec4.h"
#include "Mat4.h"

// 定数バッファ用データ構造体 (マテリアル)
struct ConstBufferDataMaterial
{
	Vec4 color; // 色 (RGBA)
};
// 定数バッファ用データ構造体 (3D変換行列)
struct ConstBufferDataTransform
{
	Mat4 mat; // 3D変換行列
};

class ConstBuffer 
{
public:
	DXResource cbMate;
};

class ConstBufferMaterial : public ConstBuffer
{
public:
	ConstBufferDataMaterial* cMapMate = nullptr;
public:
	void Color(const Vec4& color);
};

class ConstBufferTransform : public ConstBuffer
{
public:
	ConstBufferDataTransform* cMapTrfm = nullptr;
public:
	void Mat(const Mat4& mat);
};