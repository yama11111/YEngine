#pragma once
#include "Vector3.h"

namespace YMath
{
	// �X�s�[�h
	class Speed
	{
	
	public:
		
		/// <summary>
		/// </summary>
		/// ������
		/// <param name="acceleration"> : �����x</param>
		/// <param name="max"> : �ő呬�x</param>
		/// <param name="isGravity"> : �d�̓t���O</param>
		void Initialize(const Vector3& acceleration, const Vector3& max, const bool isGravity = true);

		/// <summary>
		/// ���Z�b�g
		/// </summary>
		void Reset();

		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="power"> : �̓x�N�g��</param>
		void Update(const Vector3& power);
	
	public:
		
		// ���x�擾
		Vector3 Velocity() const { return velocity_; }
		
		// �ō����x
		Vector3 Max() const { return max_; }
		
		// ���x�擾 (�Q�Ɠn��)
		Vector3& VelocityRef() { return velocity_; }
		
		// �����擾
		Vector3 Direction() const { return velocity_.Normalized(); }
	
	public:

		inline void SetAcceleration(const Vector3& acceleration) { acceleration_ = acceleration; }
		
		inline void SetMax(const Vector3& max) { max_ = max; }

		inline void SetIsGravity(const bool isGravity) { isGravity_ = isGravity; }
	
	private:
		
		// �����x
		Vector3 acceleration_;
		
		// �ō����x
		Vector3 max_;
		
		// ���x
		Vector3 velocity_;


		// �d�̓t���O
		bool isGravity_ = false;
	
	};
}
