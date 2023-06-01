#pragma once
#include "ConstBuffer.h"
#include "Vector3.h"

namespace YGame
{
	// �}�e���A���\����
	struct CBMaterial
	{
	
	public:
		
		// �萔�o�b�t�@�f�[�^�\���� (�}�e���A��)
		struct CBData
		{
			YMath::Vector3 ambient_;  // �A���r�G���g�W��
			float pad1_;
			YMath::Vector3 diffuse_;  // �f�B�t���[�Y�W��
			float pad2_;
			YMath::Vector3 specular_; // �X�y�L�����[�W��
			float alpha_;			  // �A���t�@�l
		};

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="ambient"> : �A���r�G���g�e���x (����)</param>
		/// <param name="diffuse"> : �f�B�t���[�Y�e���x (�g�U���ˌ�)</param>
		/// <param name="specular"> : �X�y�L�����[�e���x (���ʔ��ˌ�)</param>
		/// <param name="alpha"> : �A���t�@�l</param>
		/// <param name="isMutable"> : �V�[���J�ڎ��ɊJ�����邩</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static CBMaterial* Create(
			const YMath::Vector3& ambient = { 1.0f,1.0f,1.0f },
			const YMath::Vector3& diffuse = { 1.0f,1.0f,1.0f },
			const YMath::Vector3& specular = { 1.0f,1.0f,1.0f },
			const float alpha = 1.0f,
			const bool isMutable = true);
	
	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="ambient"> : �A���r�G���g�e���x (����)</param>
		/// <param name="diffuse"> : �f�B�t���[�Y�e���x (�g�U���ˌ�)</param>
		/// <param name="specular"> : �X�y�L�����[�e���x (���ʔ��ˌ�)</param>
		/// <param name="alpha"> : �A���t�@�l</param>
		void Initialize(
			const YMath::Vector3& ambient = { 1.0f,1.0f,1.0f },
			const YMath::Vector3& diffuse = { 1.0f,1.0f,1.0f },
			const YMath::Vector3& specular = { 1.0f,1.0f,1.0f },
			const float alpha = 1.0f);

		/// <summary>
		/// �`��O�R�}���h
		/// </summary>
		/// <param name="rootParamIndex"> : ���[�g�p�����[�^�ԍ�</param>
		void SetDrawCommand(const UINT rootParamIndex);
	
	public:

		/// <summary>
		/// �A���r�G���g�e���x (����)�擾
		/// </summary>
		/// <returns>�A���r�G���g�e���x (����)</returns>
		YMath::Vector3 GetAmbient() { return ambient_; }

		/// <summary>
		/// �A���r�G���g�e���x (����)�ݒ�
		/// </summary>
		/// <param name="ambient">�A���r�G���g�e���x (����)</param>
		void SetAmbient(const YMath::Vector3& ambient);


		/// <summary>
		/// �f�B�t���[�Y�e���x (�g�U���ˌ�)�擾
		/// </summary>
		/// <returns>�f�B�t���[�Y�e���x (�g�U���ˌ�)</returns>
		YMath::Vector3 GetDiffuse() { return diffuse_; }

		/// <summary>
		/// �f�B�t���[�Y�e���x (�g�U���ˌ�)�ݒ�
		/// </summary>
		/// <param name="diffuse">�f�B�t���[�Y�e���x (�g�U���ˌ�)</param>
		void SetDiffuse(const YMath::Vector3& diffuse);


		/// <summary>
		/// �X�y�L�����[�e���x (���ʔ��ˌ�)�擾
		/// </summary>
		/// <returns>�X�y�L�����[�e���x (���ʔ��ˌ�)</returns>
		YMath::Vector3 GetSpecular() { return specular_; }

		/// <summary>
		/// �X�y�L�����[�e���x (���ʔ��ˌ�)�ݒ�
		/// </summary>
		/// <param name="specular">�X�y�L�����[�e���x (���ʔ��ˌ�)</param>
		void SetSpecular(const YMath::Vector3& specular);


		/// <summary>
		/// �A���t�@�l�擾
		/// </summary>
		/// <returns>�A���t�@�l</returns>
		float GetAlpha() { return alpha_; }

		/// <summary>
		/// �A���t�@�l�ݒ�
		/// </summary>
		/// <param name="alpha">�A���t�@�l</param>
		void SetAlpha(const float alpha);

	private:

		CBMaterial() = default;

	public:

		~CBMaterial() = default;

	private:

		// �萔�o�b�t�@(�F)
		YDX::ConstBuffer<CBData> cBuff_;

		// �A���r�G���g�e���x (����)
		YMath::Vector3 ambient_ = { 1.0f,1.0f,1.0f };

		// �f�B�t���[�Y�e���x (�g�U���ˌ�)
		YMath::Vector3 diffuse_ = { 1.0f,1.0f,1.0f };

		// �X�y�L�����[�e���x (���ʔ��ˌ�)
		YMath::Vector3 specular_ = { 1.0f,1.0f,1.0f };

		// �A���t�@�l
		float alpha_ = 1.0f;

	};
}
