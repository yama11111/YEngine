#pragma once
#include <d3d12.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")

namespace YDX
{
	class ShaderCommon
	{
	protected:
		// �V�F�[�_�[�t�@�C���ǂݍ���
		void LoadShader(const wchar_t* fileName, const char* entryPoint, const char* target,
			ID3DBlob*& shaderBlob, ID3DBlob* errorBlob);
	private:
		// �ǂݍ��݃G���[������
		void LoadErrorProcess(ID3DBlob* errorBlob);
	};
}
