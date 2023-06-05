#pragma once
#include "Vector3.h"

namespace YGame
{
	class CBPointLight
	{
	
	public:
		
		// �萔�o�b�t�@�f�[�^�\���� (��)
		struct Data
		{
			YMath::Vector3 lightPos_; // ���W
			float pad1_;
			YMath::Vector3 lightColor_; // �F
			float pad2_;
			YMath::Vector3 lightAtten_; // ���������W��
			float active_; // ����t���O
		};

	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="pos"> : </param>
		/// <param name="color"> : </param>
		/// <param name="atten"> : </param>
		void Initialize(
			const YMath::Vector3& pos, 
			const YMath::Vector3& color = { 1.0f,1.0f,1.0f }, 
			const YMath::Vector3& atten = { 0.005f,0.005f,0.005f });

		/// <summary>
		/// �萔�f�[�^�擾
		/// </summary>
		/// <returns>�萔�f�[�^</returns>
		Data GetData() const;
	
	public:
		
		// ���W�擾
		YMath::Vector3 Pos() { return pos_; }
		
		// ���W�ݒ�
		void SetPos(const YMath::Vector3& pos);
		
		// �F�擾
		YMath::Vector3 Color() { return color_; }
		
		// �F�ݒ� (0.0f �` 1.0f)
		void SetColor(const YMath::Vector3& color);
		
		// �F�ݒ� (0 �` 255)
		void SetColor(const unsigned int R, const unsigned int G, const unsigned int B);
		
		// ���������W���擾
		YMath::Vector3 Atten() { return atten_; }
		
		// ���������W���ݒ�
		void SetAtten(const YMath::Vector3& atten);
		
		// �L����
		bool IsActive() { return isAct_; }
		
		// �L���t���O�ݒ�
		void SetActive(const bool isAct) { isAct_ = isAct; }
	
	public:
		
		CBPointLight() = default;
		
		~CBPointLight() = default;

	private:
		
		// ���W
		YMath::Vector3 pos_ = { 0.0f,0.0f,0.0f };
		
		// �F
		YMath::Vector3 color_ = { 1.0f,1.0f,1.0f };
		
		// ���������W��
		YMath::Vector3 atten_ = { 0.005f,0.005f,0.005f };
		
		// �L���t���O
		bool isAct_ = false;

	};
}