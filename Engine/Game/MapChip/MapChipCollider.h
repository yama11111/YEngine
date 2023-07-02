#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include <cstdint>

namespace YGame
{
	class MapChipCollider
	{
	
	public:

		/// <summary>
		/// �ʒu�擾 (�Q��)
		/// </summary>
		/// <returns>�ʒu(�Q��)</returns>
		virtual YMath::Vector3& PosRef() = 0;
		
		/// <summary>
		/// �傫���擾
		/// </summary>
		/// <returns>�傫��</returns>
		inline YMath::Vector3 Scale() const { return scale_; }
		
		/// <summary>
		/// �X�s�[�h�擾 (�Q��)
		/// </summary>
		/// <returns>�X�s�[�h(�Q��)</returns>
		virtual YMath::Vector3& SpeedRef() = 0;

		/// <summary>
		/// �A�^������r�b�g�擾
		/// </summary>
		/// <returns>�A�^������r�b�g</returns>
		inline uint8_t CollisionBit() const { return collisionBit_; }

		/// <summary>
		/// ���˕Ԃ�t���O�擾
		/// </summary>
		/// <returns>���˕Ԃ�t���O</returns>
		inline bool IsBounce() const { return isBounce_; }
		
	public:

		/// <summary>
		/// �A�^������r�b�g�ݒ�
		/// </summary>
		/// <param name="collisionBit"> : �A�^������r�b�g</param>
		inline void SetCollisionBit(const uint8_t collisionBit) { collisionBit_ = collisionBit; }

		/// <summary>
		/// ���˕Ԃ邩�ݒ�
		/// </summary>
		/// <param name="isBounce"> : ���˕Ԃ邩</param>
		inline void SetIsBounce(const bool isBounce) { isBounce_ = isBounce; }
	
	public:

		MapChipCollider() = default;

		virtual ~MapChipCollider() = default;

	protected:

		/// <summary>
		/// �}�b�v�Փːݒ菉����
		/// </summary>
		/// <param name="scale"> : �傫��</param>
		/// <param name="isBounce"> : ���˕Ԃ�t���O</param>
		void Initialize(const  YMath::Vector3& scale, const bool isBounce = true);
	
	private:
		
		// �傫��
		YMath::Vector3 scale_;

		// ���˕Ԃ邩
		bool isBounce_ = true;

		// �A�^������r�b�g
		uint8_t collisionBit_;
	};
}
