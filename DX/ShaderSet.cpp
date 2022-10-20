#include "ShaderSet.h"
#include <d3dcompiler.h>
#include <string>
#include "Utility/Result.h"

#pragma comment(lib, "d3dcompiler.lib")

using DX::ShaderSet;

void ShaderSet::Load2D()
{
	ID3DBlob* vs;
	ID3DBlob* ps;

	// 頂点シェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/SpriteVS.hlsl", "main", "vs_5_0", vs);
	// ピクセルシェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/SpritePS.hlsl", "main", "ps_5_0", ps);

	vsBlob = vs;
	psBlob = ps;
}

void ShaderSet::Load3D()
{
	ID3DBlob* vs;
	ID3DBlob* ps;

	// 頂点シェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/ModelVS.hlsl", "main", "vs_5_0", vs);
	// ピクセルシェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/ModelPS.hlsl", "main", "ps_5_0", ps);

	vsBlob = vs;
	psBlob = ps;
}

void ShaderSet::LoadShader(const wchar_t* fileName, const char* entryPoint,
	const char* target, ID3DBlob*& object)
{
	if (Utility::Result::IsFailed(D3DCompileFromFile(
		fileName, // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		entryPoint, target, // エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
		0,
		&object, &errorBlob)))
	{
		LoadShaderErrorProcess();
	}
}

void ShaderSet::LoadShaderErrorProcess()
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
	Utility::Result::Assert(false);
}
