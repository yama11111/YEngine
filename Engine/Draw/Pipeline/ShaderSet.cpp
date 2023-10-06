#include "ShaderSet.h"
#include <d3dcompiler.h>
#include "YAssert.h"
#include "FileUtil.h"

#pragma comment(lib, "d3dcompiler.lib")

using YGame::ShaderSet;

void ShaderSet::LoadShader(const std::string& shaderFileName, const ShaderType type)
{
	static const std::string kFolderName = "Resources/Shaders/";
	
	// フルパス
	const std::string kFullPath = kFolderName + shaderFileName;

	std::string target;

	// シェーダーの種類毎にターゲットとキーを変える
	if (type == ShaderType::eVertex)
	{
		target = "vs_5_0";
	}
	else if (type == ShaderType::eGeometry)
	{
		target = "gs_5_0";
	}
	else if (type == ShaderType::ePixel)
	{
		target = "ps_5_0";
	}
	
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

	ID3DBlob* shaderObj = nullptr;

	CreateShaderObject(YFile::StringToWString(kFullPath).c_str(), "main", target.c_str(), shaderObj, errorBlob.Get());

	Microsoft::WRL::ComPtr<ID3DBlob> newShaderObj = shaderObj;


	shaders_.insert({ type, std::move(newShaderObj) });
}

void ShaderSet::CreateShaderObject(
	const wchar_t* fileName, 
	const char* entryPoint, 
	const char* target, 
	ID3DBlob*& shaderBlob, 
	ID3DBlob* errorBlob)
{
	if (YDX::IsFailed(D3DCompileFromFile(
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

void ShaderSet::LoadErrorProcess(ID3DBlob* errorBlob)
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

ID3DBlob* ShaderSet::ShaderPtr(const ShaderType type)
{
	if (shaders_.empty()) { return nullptr; }

	// 探してもなかったら null
	if (shaders_.count(type) <= 0) { return nullptr; }

	return shaders_[type].Get();
}