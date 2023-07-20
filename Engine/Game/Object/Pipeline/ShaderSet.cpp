#include "ShaderSet.h"
#include <d3dcompiler.h>
#include "YAssert.h"
#include "FileUtil.h"

#pragma comment(lib, "d3dcompiler.lib")

using YGame::ShaderSet;

void ShaderSet::LoadShader(const std::string& shaderFileName, const ShaderType type)
{
	static const std::string kFolderName = "Resources/Shaders/";
	
	// �t���p�X
	const std::string kFullPath = kFolderName + shaderFileName;

	std::string target;

	// �V�F�[�_�[�̎�ޖ��Ƀ^�[�Q�b�g�ƃL�[��ς���
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
		fileName, // �V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
		entryPoint, // �G���g���[�|�C���g�� 
		target, // �V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
		0,
		&shaderBlob,
		&errorBlob)))
	{
		LoadErrorProcess(errorBlob);
	}
}

void ShaderSet::LoadErrorProcess(ID3DBlob* errorBlob)
{
	// errorBlob����G���[���e��string�^�ɃR�s�[
	std::string error;
	error.resize(errorBlob->GetBufferSize());
	std::copy_n((char*)errorBlob->GetBufferPointer(),
		errorBlob->GetBufferSize(),
		error.begin());
	error += "\n";
	
	// �G���[���e���o�̓E�B���h�E�ɕ\��
	OutputDebugStringA(error.c_str());
	assert(false);
}

ID3DBlob* ShaderSet::ShaderPtr(const ShaderType type)
{
	if (shaders_.empty()) { return nullptr; }

	// �T���Ă��Ȃ������� null
	if (shaders_.count(type) <= 0) { return nullptr; }

	return shaders_[type].Get();
}