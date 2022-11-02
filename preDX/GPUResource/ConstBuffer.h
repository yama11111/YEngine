#pragma once
#include "Utility/Resource.h"
#include "Vec4.h"
#include "Mat4.h"

namespace DX
{
	namespace GPUResource
	{
		// 定数バッファ用データ構造体 (マテリアル)
		struct ConstBufferDataMaterial
		{
			Math::Vec4 color; // 色 (RGBA)
		};
		// 定数バッファ用データ構造体 (3D変換行列)
		struct ConstBufferDataTransform
		{
			Math::Mat4 mat; // 3D変換行列
		};

		class ConstBuffer
		{
		public:
			Utility::Resource mate;
		};

		class ConstBufferMaterial : public ConstBuffer
		{
		public:
			ConstBufferDataMaterial* mapMate = nullptr;
		public:
			void Color(const Math::Vec4& color);
		};

		class ConstBufferTransform : public ConstBuffer
		{
		public:
			ConstBufferDataTransform* mapTrfm = nullptr;
		public:
			void Mat(const Math::Mat4& mat);
		};
	}
}