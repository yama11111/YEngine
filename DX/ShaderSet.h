#pragma once
#include <d3d12.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")

namespace DX
{
	class ShaderSet
	{
	public:
		Microsoft::WRL::ComPtr<ID3DBlob> vsBlob = nullptr; // ���_�V�F�[�_�I�u�W�F�N�g
		Microsoft::WRL::ComPtr<ID3DBlob> psBlob = nullptr; // �s�N�Z���V�F�[�_�I�u�W�F�N�g
		Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr; // �G���[�I�u�W�F�N�g
	public:
		void Load2D();
		void Load3D();
	private:
		void LoadShader(const wchar_t* fileName, const char* entryPoint,
			const char* target, ID3DBlob*& object);
		// �ǂݍ��݃G���[������
		void LoadShaderErrorProcess();
	};
}