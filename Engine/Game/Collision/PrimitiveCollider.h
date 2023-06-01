//#pragma once
//#include "BaseCollider.h"
//#include "CollisionPrimitive.h"
//
//namespace YGame
//{
//	class SphereCollider :
//		public BaseCollider,
//		private Sphere
//	{
//	public:
//		/// <summary>
//		/// ������
//		/// </summary>
//		/// <param name="center">/ ���S���W</param>
//		/// <param name="radius">/ ���a</param>
//		/// <param name="offset">/ �I�t�Z�b�g</param>
//		/// <param name="attribute">/ ����(����)</param>
//		/// <param name="mask">/ �}�X�N(����)</param>
//		/// <param name="isInvincible">/ ���G�t���O</param>
//		void Initialize(
//			const YMath::Vector3& center,
//			const float radius,
//			YMath::Vector3 offset = { 0.0f,0.0f,0.0f },
//			uint32_t attribute = 0xffffffff,
//			uint32_t mask = 0xffffffff,
//			bool isInvincible = false);
//		// �Փˎ��R�[���o�b�N�֐�
//		virtual void OnCollision(const CollsionInfo& info) = 0;
//	public:
//		// �ʒu�擾
//		inline YMath::Vector3 GetPos() const override { return center_ + offset_; }
//		// ���S���W�擾
//		inline YMath::Vector3 GetCenter() const { return center_; }
//		// ���S���W�ݒ�
//		inline void SetCenter(const YMath::Vector3& center) { center_ = center; }
//		// ���a�擾
//		inline float GetRadius() const { return radius_; }
//		// ���a�ݒ�
//		inline void SetRadius(const float radius) { SafeSetRadius(radius); }
//	};
//}
//
