#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <string>
#include <unordered_map>

namespace YGame
{
	class ShaderSet
	{

	public:

		// �V�F�[�_�[�̎��
		enum class ShaderType
		{
			// ���_�V�F�[�_�[
			eVertex,
			
			// �W�I���g���V�F�[�_�[
			eGeometry,

			// �s�N�Z���V�F�[�_�[
			ePixel,
		};

	public:

		/// <summary>
		/// �V�F�[�_�[�t�@�C���ǂݍ���
		/// </summary>
		/// <param name="shaderFileName"> : �V�F�[�_�[�̎��</param>
		/// <param name="type"> : �V�F�[�_�[�̎��</param>
		void LoadShader(const std::string& shaderFileName, const ShaderType type);

		/// <summary>
		/// �V�F�[�_�[�|�C���^�擾
		/// </summary>
		/// <param name="type"> : �V�F�[�_�[�̎��</param>
		/// <returns>�V�F�[�_�[�|�C���^</returns>
		ID3DBlob* ShaderPtr(const ShaderType type);

	private:

		// �V�F�[�_�[�i�[�z��
		std::unordered_map<
			ShaderType,
			Microsoft::WRL::ComPtr<ID3DBlob>> shaders_;

	private:

		/// <summary>
		/// �V�F�[�_�[�I�u�W�F�N�g�ǂݍ���
		/// </summary>
		/// <param name="fileName"> : �V�F�[�_�[�t�@�C����</param>
		/// <param name="entryPoint"> : �G���g���[�|�C���g (main)</param>
		/// <param name="target"> : �^�[�Q�b�g (��� + �o�[�W����)</param>
		/// <param name="shaderBlob"> : �V�F�[�_�[�I�u�W�F�N�g</param>
		/// <param name="errorBlob"> : �G���[�p</param>
		void CreateShaderObject(
			const wchar_t* fileName,
			const char* entryPoint,
			const char* target,
			ID3DBlob*& shaderBlob,
			ID3DBlob* errorBlob);

		/// <summary>
		/// �ǂݍ��݃G���[������
		/// </summary>
		/// <param name="errorBlob"> : �G���[�p</param>
		void LoadErrorProcess(ID3DBlob* errorBlob);

	};
}
