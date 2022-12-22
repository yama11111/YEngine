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

void ShaderCommon::LoadErrorProcess(ID3DBlob* errorBlob)
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