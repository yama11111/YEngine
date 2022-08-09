#include "DXShaderManager.h"
#include <d3dcompiler.h>
#include <string>
#include "Result.h"

#pragma comment(lib, "d3dcompiler.lib")

void DXShaderManager::Load()
{
	// 頂点シェーダの読み込みとコンパイル
	LoadShader(L"BasicVS.hlsl", "main", "vs_5_0", vsBlob);
	// ピクセルシェーダの読み込みとコンパイル
	LoadShader(L"BasicPS.hlsl", "main", "ps_5_0", psBlob);
}

void DXShaderManager::LoadShader(const wchar_t* fileName, const char* entryPoint,
	const char* target, ID3DBlob*& object)
{
	if (Result::IsFailed(D3DCompileFromFile(
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

void DXShaderManager::LoadShaderErrorProcess()
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
	Result::Assert(0);
}
