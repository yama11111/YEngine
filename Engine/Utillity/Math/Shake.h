#pragma once
#include "Vector3.h"

namespace YMath
{
	// �h��
	class Shake
	{
	
	private:
		
		// �h��Ă��邩
		bool isAct_ = false;

		// �h���� (����)
		float swing_ = 0.0f;
		
		// ������
		float dekey_ = 0.0f;

		// ��
		float place_ = 0.0f;

		// �h��Ă����
		Vector3 value_{};
	
	public:

		/// <summary>
		/// ������
		/// </summary>
		void Initialize();

		/// <summary>
		/// �X�V
		/// </summary>
		void Update();
		
		/// <summary>
		/// ����J�n
		/// </summary>
		/// <param name="swing"> : �h����</param>
		/// <param name="dekey"> : ������</param>
		/// <param name="place"> : �����_�ȉ��̈�</param>
		void Activate(const float swing, const float dekey, const float place);
	
	public:

		/// <summary>
		/// �h��ʎ擾
		/// </summary>
		/// <returns> : �h���</returns>
		Vector3 Value() const { return value_; }

		/// <summary>
		/// ���쒆���擾
		/// </summary>
		/// <returns> : ���쒆��</returns>
		bool IsAct() const { return isAct_; }
	
	};
}