#pragma once
#include "Vector3.h"
#include "WorldRuler.h"

namespace YMath
{
	// �X�s�[�h
	class Speed : public YGame::WorldRuleAdopter
	{
	private:
		// �����x
		Vector3 acceleration_;
		// �ō����x
		Vector3 max_;
		// ���l
		Vector3 value_;

		bool isGravity_ = false;
	public:
		// ������
		void Initialize(const Vector3& acceleration, const Vector3& max, const bool isGravity = true);
		// ���Z�b�g
		void Reset();
		// �X�V
		void Update(const Vector3& power);
	private:
		// �v�Z
		static void Calculate(float& value, const float power, const float acceleration, const float max, const float dekey);
		// �v�Z (�d��)
		static void Gravity(float& value, const float power, const float acceleration, const float max, const float dekey);
	public:
		// ���l�擾
		Vector3 Value() const { return value_; }
		// �ō����x
		Vector3 Max() const { return max_; }
		// ���l�擾 (�Q�Ɠn��)
		Vector3& ValueRef() { return value_; }
		// �����擾
		Vector3 Direction() const { return value_.Normalized(); }
	};
}
