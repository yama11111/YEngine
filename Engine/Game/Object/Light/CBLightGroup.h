#pragma once
#include "ConstBuffer.h"
#include "CBDirectionalLight.h"
#include "CBPointLight.h"
#include "CBSpotLight.h"
#include <array>

namespace YGame
{
	class CBLightGroup
	{
	
	public:
		
		// ���s������
		static const size_t DireLightNum_ = 3;
		
		// �_������
		static const size_t PointLightNum_ = 3;
		
		// �X�|�b�g���C�g������
		static const size_t SpotLightNum_ = 1;
	
	public:
		
		// �萔�o�b�t�@�f�[�^�\���� (��)
		struct CBData
		{
			YMath::Vector3 ambientColor_; // �����̐F
			float pad_; // �p�f�B���O
			std::array<CBDirectionalLight::Data, DireLightNum_> direLights_; // ���s����
			std::array<CBPointLight::Data, PointLightNum_> pointLights_; // �_����
			//std::array<CBSpotLight::Data, SpotLightNum_> spotLights_; // �X�|�b�g���C�g����
		};

	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="ambientColor"> : ����</param>
		/// <param name="isMutable"> : �V�[���J�ڎ��ɊJ�����邩</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static CBLightGroup* Create(
			const YMath::Vector3& ambientColor = { 1.0f,1.0f,1.0f },
			const bool isMutable = true);
	
	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="ambientColor"> : ����</param>
		void Initialize(const YMath::Vector3& ambientColor = { 1.0f,1.0f,1.0f });

		/// <summary>
		/// �`��O�R�}���h
		/// </summary>
		/// <param name="rootParamIndex"> : ���[�g�p�����[�^�ԍ�</param>
		void SetDrawCommand(const UINT rootParamIndex);

	public:

		// �F�ݒ� (0.0f �` 1.0f)
		void SetAmbientColor(const YMath::Vector3& color);

	public:

		// �����ݒ� (���s����)
		void SetDirectionalLightDirection(const size_t index, const YMath::Vector3& direction);

		// �F�ݒ� (���s����)
		void SetDirectionalLightColor(const size_t index, const YMath::Vector3& color);

		// �L���t���O�ݒ� (���s����)
		void SetDirectionalLightActive(const size_t index, const bool isAct);

	public:

		// ���W�ݒ� (�_����)
		void SetPointLightPos(const size_t index, const YMath::Vector3& pos);

		// �F�ݒ� (�_����)
		void SetPointLightColor(const size_t index, const YMath::Vector3& color);
		// ���������W���ݒ� (�_����)

		void SetPointLightAtten(const size_t index, const YMath::Vector3& atten);

		// �L���t���O�ݒ� (���s����)
		void SetPointLightActive(const size_t index, const bool isAct);

	public:

		// ���W�ݒ� (�X�|�b�g���C�g����)
		void SetSpotLightPos(const size_t index, const YMath::Vector3& pos);

		// �����ݒ� (�X�|�b�g���C�g����)
		void SetSpotLightDirection(const size_t index, const YMath::Vector3& direction);
		// �F�ݒ� (�X�|�b�g���C�g����)

		void SetSpotLightColor(const size_t index, const YMath::Vector3& color);

		// ���������W���ݒ� (�X�|�b�g���C�g����)
		void SetSpotLightAtten(const size_t index, const YMath::Vector3& atten);

		// �����p�x�ݒ� (�X�|�b�g���C�g����)
		void SetSpotLightFactorAngleCos(const size_t index, const float start, const float end);

		// �L���t���O�ݒ� (�X�|�b�g���C�g����)
		void SetSpotLightActive(const size_t index, const bool isAct);

	private:

		CBLightGroup() = default;
	
	public:

		~CBLightGroup() = default;
	
	private:

		// �萔�o�b�t�@(��)
		YDX::ConstBuffer<CBData> cBuff_;
		
		// �����̐F
		YMath::Vector3 ambientColor_ = { 1.0f,1.0f,1.0f };

		// ���s����
		std::array<CBDirectionalLight, DireLightNum_> direLights_;
		
		// �_����
		std::array<CBPointLight, PointLightNum_> pointLights_;
		
		// �X�|�b�g���C�g����
		std::array<SpotLight, SpotLightNum_> spotLights_;
	};
}
