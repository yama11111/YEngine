#pragma once
#include <d3d12.h>

#pragma comment(lib, "d3d12.lib")

namespace DX
{
	class ShaderSet
	{
	public:
		ID3DBlob* vsBlob = nullptr; // 頂点シェーダオブジェクト
		ID3DBlob* psBlob = nullptr; // ピクセルシェーダオブジェクト
		ID3DBlob* errorBlob = nullptr; // エラーオブジェクト
	public:
		void Load2D();
		void Load3D();
	private:
		void LoadShader(const wchar_t* fileName, const char* entryPoint,
			const char* target, ID3DBlob*& object);
		// 読み込みエラー時処理
		void LoadShaderErrorProcess();
	};
}
