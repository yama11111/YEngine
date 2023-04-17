#pragma once
#include "ConstBuffer.h"
#include "Texture.h"
#include "Vector3.h"

namespace YGame
{
	// �}�e���A���\����
	struct Material
	{
	public:
		// �萔�o�b�t�@�f�[�^�\���� (�}�e���A��)
		struct CBData
		{
			YMath::Vector3 ambient_;  // �A���r�G���g�W��
			float pad1_; // �p�f�B���O1
			YMath::Vector3 diffuse_;  // �f�B�t���[�Y�W��
			float pad2_; // �p�f�B���O2
			YMath::Vector3 specular_; // �X�y�L�����[�W��
			float alpha_;			  // �A���t�@�l
		};
	public:
		// �}�e���A����
		std::string name_;
		// �A���r�G���g�e���x
		YMath::Vector3 ambient_;
		// �f�B�t���[�Y�e���x
		YMath::Vector3 diffuse_;
		// �X�y�L�����[�e���x
		YMath::Vector3 specular_;
		// �A���t�@�l
		float alpha_;

		// �e�N�X�`���t�@�C����
		std::string texFileName_;
		// �e�N�X�`��
		Texture* pTex_ = nullptr;
		
		// �萔�o�b�t�@(�}�e���A��)
		YDX::ConstBuffer<CBData> cBuff_;
	public:
		/// <summary>
		/// �}�e���A���ǂݍ���
		/// </summary>
		/// <param name="directoryPath"> : �f�B���N�g���p�X</param>
		/// <param name="fileName"> : �t�@�C����</param>
		/// <returns>�}�e���A��</returns>
		static Material Load(const std::string& directoryPath, const std::string& fileName);
	public:
		/// <summary>
		/// �摜�ǂݍ���
		/// </summary>
		/// <param name="texFileName"> : �摜�t�@�C����</param>
		void LoadTexture(const std::string& texFileName);
		/// <summary>
		/// �`��O�R�}���h
		/// </summary>
		/// <param name="mateRPIndex"> : ���[�g�p�����[�^�ԍ�</param>
		/// <param name="texRPIndex"> : ���[�g�p�����[�^�ԍ�</param>
		void SetDrawCommand(UINT mateRPIndex, UINT texRPIndex);
	private:
		// �ÓI�f�t�H���g�e�N�X�`��
		static Texture* spDefTexIndex_;
	public:
		// �ÓI������
		static void StaticInitialize();
	public:
		// �R���X�g���N�^
		Material();
	};
}
