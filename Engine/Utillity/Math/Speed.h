#pragma once
#include "Vector3.h"
#include "WorldRuler.h"

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
		/// <param name="direction"> : ����</param>
		void Update(const Vector3& direction);
	
	public:
		
		// ���x�擾
		Vector3 Velocity() const { return velocity_; }
		
		// �ō����x
		Vector3 Max() const { return max_; }
		
		// ���x�擾 (�Q�Ɠn��)
		Vector3& VelocityRef() { return velocity_; }
		
		// �����擾
		Vector3 Direction() const { return velocity_.Normalized(); }
	
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
