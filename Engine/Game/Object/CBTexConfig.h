#pragma once
#include "ConstBuffer.h"
#include "Vector2.h"

namespace YGame
{
	class CBTexConfig
	{

	public:

		// �萔�o�b�t�@�f�[�^�\���� (�e�N�X�`���ݒ�)
		struct CBData
		{
			YMath::Vector2 tiling_; // �^�C�����O�l
			float pad1_;
			float pad2_;
			YMath::Vector2 offset_; // �I�t�Z�b�g�l
			float pad3_;
			float pad4_;
		};

	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="tiling"> : �^�C�����O</param>
		/// <param name="offset"> : �I�t�Z�b�g</param>
		/// <param name="isMutable"> : �V�[���J�ڎ��ɊJ�����邩</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static CBTexConfig* Create(
			const YMath::Vector2& tiling = { 1.0f,1.0f },
			const YMath::Vector2& offset = { 0.0f,0.0f },
			const bool isMutable = true);

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="tiling"> : �^�C�����O</param>
		/// <param name="offset"> : �I�t�Z�b�g</param>
		void Initialize(
			const YMath::Vector2& tiling = { 1.0f,1.0f },
			const YMath::Vector2& offset = { 0.0f,0.0f });

		/// <summary>
		/// �`��O�R�}���h
		/// </summary>
		/// <param name="rootParamIndex"> : ���[�g�p�����[�^�ԍ�</param>
		void SetDrawCommand(const UINT rootParamIndex);

	public:

		/// <summary>
		/// �^�C�����O�l�擾
		/// </summary>
		/// <returns>�^�C�����O�l</returns>
		YMath::Vector2 GetTiling() const { return tiling_; }


		/// <summary>
		/// �^�C�����O�l�ݒ�
		/// </summary>
		/// <param name="tiling">�^�C�����O�l</param>
		void SetTiling(const YMath::Vector2& tiling) { tiling_ = tiling; }

	public:

		/// <summary>
		/// �I�t�Z�b�g�l�擾
		/// </summary>
		/// <returns>�I�t�Z�b�g�l</returns>
		YMath::Vector2 GetOffset() const { return offset_; }


		/// <summary>
		/// �I�t�Z�b�g�l�ݒ�
		/// </summary>
		/// <param name="tiling">�I�t�Z�b�g�l</param>
		void SetOffset(const YMath::Vector2& offset) { offset_ = offset; }

	private:

		CBTexConfig() = default;

	public:

		~CBTexConfig() = default;

	private:

		// �萔�o�b�t�@(�F)
		YDX::ConstBuffer<CBData> cBuff_;

		// �^�C�����O
		YMath::Vector2 tiling_ = { 1.0f,1.0f };
		
		// �I�t�Z�b�g
		YMath::Vector2 offset_ = { 0.0f,0.0f };

	};
}

