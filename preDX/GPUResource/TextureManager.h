#pragma once
#include "Vec4.h"
#include "ShaderResourceView.h"

namespace DX
{
	namespace GPUResource
	{
		class TextureManager
		{
		private:
			static ShaderResourceView* srv;
		public:
			UINT CreateTex(const Math::Vec4& color = { 1.0f,1.0f,1.0f,1.0f });
			UINT Load(const wchar_t* fileName, const bool mipMap = true);
			void SetCommand(const UINT index);
		public:
			static void StaticInit();
			static TextureManager* GetInstance();
		private:
			TextureManager() = default;
			~TextureManager() = default;
			TextureManager(const TextureManager&) = delete;
			const TextureManager& operator=(const TextureManager&) = delete;
		};
	}
}
