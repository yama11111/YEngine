#pragma once
#include "ConstBuffer.h"
#include "DirectionalLight.h"
#include <array>

namespace YGame
{
	class LightGroup
	{
	public:
		// ���s������
		static const size_t DireLightNum_ = 3;
	public:
		// �萔�o�b�t�@�f�[�^�\���� (��)
		struct CBData
		{
			YMath::Vec3 ambientColor_; // �����̐F
			float pad_; // �p�f�B���O
			std::array<DirectionalLight::CBData, DireLightNum_> direLights_; // ���s����
		};
	private:
		// �����̐F
		YMath::Vec3 ambientColor_;
		// �萔�o�b�t�@(��)
		YDX::ConstBuffer<CBData> cBuff_;
	private:
		// ���s����
		std::array<DirectionalLight, DireLightNum_> direLights_;
	public:
		// ����
		static LightGroup* Create();
	public:
		// ������
		void Initialize(const YMath::Vec3& ambientColor = { 1.0f,1.0f,1.0f });
		// �`��O�R�}���h
		void SetDrawCommand(const UINT rootParamIndex);
	public:
		// �F�ݒ� (0.0f �` 1.0f)
		void SetAmbientColor(const YMath::Vec3& color);
		// �F�ݒ� (0 �` 255)
		void SetAmbientColor(const UINT R, const UINT G, const UINT B);
	public:
		// �����ݒ� (���s����)
		void SetDirectionalLightDirection(const size_t index, const YMath::Vec3& direction);
		// �F�ݒ� (���s����)
		void SetDirectionalLightColor(const size_t index, const YMath::Vec3& color);
		// �L���t���O�ݒ� (���s����)
		void SetDirectionalLightActive(const size_t index, const bool isAct);
	public:
		LightGroup();
		~LightGroup() = default;
	};
}
