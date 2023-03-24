#pragma once
#include "Vector3.h"

namespace YMath
{
	// �h��
	class Shake
	{
	private:
		// �h��Ă����
		Vector3 value_{};
		// �h��Ă��邩
		bool isAct_ = false;
		// �h���� (����)
		int swing_ = 0;
		// ������
		int dekey_ = 0;
	public:
		// ������
		void Initialize();
		// �X�V
		void Update();
		/// <summary>
		/// ����J�n
		/// </summary>
		/// <param name="swing"> : �h����</param>
		/// <param name="dekey"> : ������</param>
		void Activate(const int swing, const int dekey);
	public:
		// �h���
		Vector3 Value() const { return value_; }
		// ���쒆��
		bool IsAct() const { return isAct_; }
	};
}