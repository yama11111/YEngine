#pragma once
#include "Vec3.h"
#include <cstdint>

namespace Collision
{
	class Collider
	{
	private:
		// ���a
		float radius_ = 0.0f;
		// ���� (����)
		uint32_t attribute_ = 0xffffffff;
		// �}�X�N (����)
		uint32_t mask_ = 0xffffffff;
		// ����ʂ��t���O
		bool isSlip_ = false;
	public:
		struct CollisionStatus 
		{
			float radius_; // ���a
			uint32_t attribute_; // ���� (����)
			uint32_t mask_; // �}�X�N (����)
			bool isSlip_ = false; // ����ʂ��t���O
		};
	public:
		// �Փːݒ菉����
		void InitializeCollisionStatus(const CollisionStatus& state);
		// �Փˎ�����
		virtual void OnCollision(const uint32_t attribute) = 0;
	public:
		// �ʒu�擾
		virtual Math::Vec3 Pos() = 0;
		// ���a�擾
		float Radius() { return radius_; }
		// ���a�ݒ�
		void SetRadius(const float radius) { radius_ = radius; }
	public:
		// �����擾
		uint32_t Attribute() { return attribute_; }
		// �����ݒ�
		void SetAttribute(const uint32_t attribute) { attribute_ = attribute; }
		// �}�X�N�擾
		uint32_t Mask() { return mask_; }
		// �}�X�N�ݒ�
		void SetMask(const uint32_t mask) { mask_ = mask; }
		// ����ʂ��擾
		bool IsSlip() { return isSlip_; }
		// ����ʂ��ݒ�
		void SetIsSlip(const bool isSlip) { isSlip_ = isSlip; }
	};
}
