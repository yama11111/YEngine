#pragma once
#include <d3d12.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")

namespace DX
{
	// �V�F�[�_�[�Z�b�g�C���^�[�t�F�[�X
	class IShaderSet
	{
	protected:
		// �V�F�[�_�[�t�@�C���ǂݍ���
		void LoadShader(const wchar_t* fileName, const char* entryPoint, const char* target,
			ID3DBlob*& shaderBlob, ID3DBlob* errorBlob);
	private:
		// �ǂݍ��݃G���[������
		void LoadShaderErrorProcess(ID3DBlob* errorBlob);
	};

	// �X�v���C�g�p�V�F�[�_�[�Z�b�g
	class SpriteShaderSet : public IShaderSet
	{
	public:
		// ���_�V�F�[�_�I�u�W�F�N�g
		Microsoft::WRL::ComPtr<ID3DBlob> vsBlob_ = nullptr;
		// �s�N�Z���V�F�[�_�I�u�W�F�N�g
		Microsoft::WRL::ComPtr<ID3DBlob> psBlob_ = nullptr;
	public:
		// �V�F�[�_�[�t�@�C���ǂݍ���
		void Load(ID3DBlob* errorBlob);
	};

	// ���f���p�V�F�[�_�[�Z�b�g
	class ModelShaderSet : public IShaderSet
	{
	public:
		// ���_�V�F�[�_�I�u�W�F�N�g
		Microsoft::WRL::ComPtr<ID3DBlob> vsBlob_ = nullptr;
		// �s�N�Z���V�F�[�_�I�u�W�F�N�g
		Microsoft::WRL::ComPtr<ID3DBlob> psBlob_ = nullptr;
	public:
		// �V�F�[�_�[�t�@�C���ǂݍ���
		void Load(ID3DBlob* errorBlob);
	};
}
