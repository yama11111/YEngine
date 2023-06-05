#pragma once
#include "Vector3.h"
#include <cstdint>

namespace YGame
{

	// �R���C�_�[���N���X
	class BaseCollider
	{

	public:

		// �Փˌ^
		enum class ShapeType
		{
			eUnkown = -1, // ���ݒ�

			eSphere, // ��
		};
	
	protected:
		
		// �I�t�Z�b�g
		YMath::Vector3 offset_;
		
		// �Փˌ^
		ShapeType shape_ = ShapeType::eUnkown;
		
		// ���� (����)
		uint32_t attribute_ = 0xffffffff;
		
		// �}�X�N (����)
		uint32_t mask_ = 0xffffffff;
		
		// ���蔲���t���O
		bool isSlip_ = false;
	
	public:
		
		// �Փˏ��
		struct CollsionInfo
		{
		
		public:
			BaseCollider* pair_ = nullptr; // �R���C�_�[ (����)
			//YMath::Vector3 inter; // �Փ˓_
		};
	
	public:
		
		// �X�V
		virtual void Update() = 0;
		
		// �Փˎ��R�[���o�b�N�֐�
		virtual void OnCollision(const CollsionInfo& info) = 0;
	
	public:
		// �I�t�Z�b�g�l�擾
		inline virtual YMath::Vector3 GetPos() const;
		// �I�t�Z�b�g�l�擾
		inline YMath::Vector3 SetOffset() const { return offset_; }
		// �I�t�Z�b�g�l�ݒ�
		inline void SetOffset(const YMath::Vector3& offset) { offset_ = offset; }
		// �Փˌ^�擾
		inline ShapeType GetShapeType() const { return shape_; }
		// �����擾
		inline uint32_t GetAttribute() const { return attribute_; }
		// �����ݒ�
		inline void SetAttribute(const uint32_t attribute) { attribute_ = attribute; }
		// �}�X�N�擾
		inline uint32_t GetMask() const { return mask_; }
		// �}�X�N�ݒ�
		inline void SetMask(const uint32_t mask) { mask_ = mask; }
		// ���蔲���t���O�擾
		inline bool GetIsSlip() const { return isSlip_; }
		// ���蔲���t���O�ݒ�
		inline void SetIsSlip(const bool isSlip) { isSlip_ = isSlip; }
	public:
		BaseCollider() = default;
		virtual ~BaseCollider() = default;
	};
}
