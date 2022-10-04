#include "ShaderSet.h"
#include <d3dcompiler.h>
#include <string>
#include "Utility/Result.h"

#pragma comment(lib, "d3dcompiler.lib")

using DX::ShaderSet;

void ShaderSet::Load2D()
{
	// ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	LoadShader(L"Resources/Shaders/SpriteVS.hlsl", "main", "vs_5_0", vsBlob);
	// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	LoadShader(L"Resources/Shaders/SpritePS.hlsl", "main", "ps_5_0", psBlob);
}

void ShaderSet::Load3D()
{
	// ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	LoadShader(L"Resources/Shaders/ModelVS.hlsl", "main", "vs_5_0", vsBlob);
	// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	LoadShader(L"Resources/Shaders/ModelPS.hlsl", "main", "ps_5_0", psBlob);
}

void ShaderSet::LoadShader(const wchar_t* fileName, const char* entryPoint,
	const char* target, ID3DBlob*& object)
{
	if (Utility::Result::IsFailed(D3DCompileFromFile(
		fileName, // �V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
		entryPoint, target, // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
		0,
		&object, &errorBlob)))
	{
		LoadShaderErrorProcess();
	}
}

void ShaderSet::LoadShaderErrorProcess()
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
	Utility::Result::Assert(false);
}
