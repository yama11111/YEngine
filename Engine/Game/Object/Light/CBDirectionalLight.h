#pragma once
#include "Vector3.h"

namespace YGame
{
	class CBDirectionalLight
	{
	
	public:
		
		// �萔�o�b�t�@�f�[�^�\���� (��)
		struct Data
		{
			YMath::Vector3 lightVec_; // ����
			float pad_;
			YMath::Vector3 lightColor_; // �F
			float active_; // ����t���O
		};
	
	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="direction"> : ����</param>
		/// <param name="color"> : �F</param>
		void Initialize(const YMath::Vector3& direction, const YMath::Vector3& color = { 1.0f,1.0f,1.0f });

		/// <summary>
		/// �萔�f�[�^�擾
		/// </summary>
		/// <returns>�萔�f�[�^</returns>
		Data GetData() const;
	
	public:
		
		// �����擾
		YMath::Vector3 Direction() { return direction_; }
		
		// ����
		void SetDirection(const YMath::Vector3& direciton);
		
		// �F�擾
		YMath::Vector3 Color() { return color_; }
		
		// �F�ݒ� (0.0f �` 1.0f)
		void SetColor(const YMath::Vector3& color);
		
		// �L����
		bool IsActive() { return isAct_; }
		
		// �L���t���O�ݒ�
		void SetActive(const bool isAct) { isAct_ = isAct; }
	
	public:
		
		CBDirectionalLight() = default;
		
		~CBDirectionalLight() = default;

	private:
		
		// ����
		YMath::Vector3 direction_ = { 1.0f,1.0f,1.0f };
		
		// �F
		YMath::Vector3 color_ = { 1.0f,1.0f,1.0f };
		
		// �L���t���O
		bool isAct_ = false;
	
	};
}

