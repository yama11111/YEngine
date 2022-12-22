#include "ShaderCommon.h"
#include <d3dcompiler.h>
#include <string>
#include "YAssert.h"

#pragma comment(lib, "d3dcompiler.lib")

using YDX::ShaderCommon;

void ShaderCommon::LoadShader(const wchar_t* fileName, const char* entryPoint, const char* target,
		ID3DBlob*& shaderBlob, ID3DBlob* errorBlob)
{
	if (IsFailed(D3DCompileFromFile(
		fileName, // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		entryPoint, // エントリーポイント名 
		target, // シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
		0,
		&shaderBlob, 
		&errorBlob)))
	{
		LoadErrorProcess(errorBlob);
	}
}

void ShaderCommon::LoadErrorProcess(ID3DBlob* errorBlob)
{
	// errorBlobからエラー内容をstring型にコピー
	std::string error;
	error.resize(errorBlob->GetBufferSize());
	std::copy_n((char*)errorBlob->GetBufferPointer(),
		errorBlob->GetBufferSize(),
		error.begin());
	error += "\n";
	// エラー内容を出力ウィンドウに表示
	OutputDebugStringA(error.c_str());
	assert(false);
}