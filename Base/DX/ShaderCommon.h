#pragma once
#include <d3d12.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")

namespace YDX
{
	class ShaderCommon
	{
	protected:
		// シェーダーファイル読み込み
		void LoadShader(const wchar_t* fileName, const char* entryPoint, const char* target,
			ID3DBlob*& shaderBlob, ID3DBlob* errorBlob);
	private:
		// 読み込みエラー時処理
		void LoadErrorProcess(ID3DBlob* errorBlob);
	};
}
