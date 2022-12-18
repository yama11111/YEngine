#include "ShaderSet.h"
#include <d3dcompiler.h>
#include <string>
#include "YAssert.h"

#pragma comment(lib, "d3dcompiler.lib")

using YDX::IShaderSet;
using YDX::SpriteShaderSet;
using YDX::ModelShaderSet;
using YDX::BillboardShaderSet;

void IShaderSet::LoadShader(const wchar_t* fileName, const char* entryPoint, const char* target,
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
		LoadShaderErrorProcess(errorBlob);
	}
}

void IShaderSet::LoadShaderErrorProcess(ID3DBlob* errorBlob)
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

void SpriteShaderSet::Load(ID3DBlob* errorBlob)
{
	ID3DBlob* vs = nullptr;
	ID3DBlob* ps = nullptr;

	// 頂点シェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/SpriteVS.hlsl", "main", "vs_5_0", vs, errorBlob);
	// ピクセルシェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/SpritePS.hlsl", "main", "ps_5_0", ps, errorBlob);

	vsBlob_ = vs;
	psBlob_ = ps;

}

void ModelShaderSet::Load(ID3DBlob* errorBlob)
{
	ID3DBlob* vs = nullptr;
	ID3DBlob* ps = nullptr;

	// 頂点シェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/ModelVS.hlsl", "main", "vs_5_0", vs, errorBlob);
	// ピクセルシェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/ModelPS.hlsl", "main", "ps_5_0", ps, errorBlob);

	vsBlob_ = vs;
	psBlob_ = ps;
}

void BillboardShaderSet::Load(ID3DBlob* errorBlob)
{
	ID3DBlob* gs = nullptr;
	ID3DBlob* vs = nullptr;
	ID3DBlob* ps = nullptr;

	// 頂点シェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/BillboardVS.hlsl", "main", "vs_5_0", vs, errorBlob);
	// ジオメトリシェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/BillboardGS.hlsl", "main", "gs_5_0", gs, errorBlob);
	// ピクセルシェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/BillboardPS.hlsl", "main", "ps_5_0", ps, errorBlob);

	gsBlob_ = gs;
	vsBlob_ = vs;
	psBlob_ = ps;
}
