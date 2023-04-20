#pragma once
#include <d3d12.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")

namespace YDX
{
	class IShaderSet
	{

	public:

		/// <summary>
		/// �V�F�[�_�[�t�@�C���ǂݍ���
		/// </summary>
		virtual void Load() = 0;

	protected:
		
		/// <summary>
		/// �V�F�[�_�[�t�@�C���ǂݍ���
		/// </summary>
		/// <param name="fileName"> : �V�F�[�_�[�t�@�C����</param>
		/// <param name="entryPoint"> : �G���g���[�|�C���g (main)</param>
		/// <param name="target"> : �^�[�Q�b�g (��� + �o�[�W����)</param>
		/// <param name="shaderBlob"> : �V�F�[�_�[�I�u�W�F�N�g</param>
		/// <param name="errorBlob"> : �G���[�p</param>
		void LoadShader(const wchar_t* fileName, const char* entryPoint, const char* target,
			ID3DBlob*& shaderBlob, ID3DBlob* errorBlob);
	
	private:
		
		/// <summary>
		/// �ǂݍ��݃G���[������
		/// </summary>
		/// <param name="errorBlob"> : �G���[�p</param>
		void LoadErrorProcess(ID3DBlob* errorBlob);

	};
}
