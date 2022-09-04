#pragma once
#include "../Utility/Resource.h"
#include "../../Math/Vec4.h"
#include "../../Math/Mat4.h"

namespace DX
{
	namespace GPUResource
	{
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
			Utility::Resource cbMate;
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
	}
}