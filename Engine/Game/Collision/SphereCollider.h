#pragma once
#include "BaseCollider.h"
#include "CollisionPrimitive.h"

namespace YGame
{
	// ���R���C�_�[�N���X
	class SphereCollider final:
		public BaseCollider,
		public Sphere
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="offset"> : �I�t�Z�b�g</param>
		/// <param name="attribute"> : ����</param>
		/// <param name="mask"> : �}�X�N</param>
		/// <param name="radius"> : ���a</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		void Initialize(
			const YMath::Vector3& offset,
			const AttributeType attribute, const AttributeType mask,
			const float radius, 
			const bool isSlip = false);

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="pParent"> : �e�g�����X�t�H�[���|�C���^</param>
		/// <param name="offset"> : �I�t�Z�b�g</param>
		/// <param name="attribute"> : ����</param>
		/// <param name="mask"> : �}�X�N</param>
		/// <param name="radius"> : ���a</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		void Initialize(
			Transform* pParent, const YMath::Vector3& offset,
			const AttributeType attribute, const AttributeType mask,
			const float radius, 
			const bool isSlip = false);

		/// <summary>
		/// �X�V
		/// </summary>
		void Update() override;

	public:

		SphereCollider() = default;
		
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="offset"> : �I�t�Z�b�g</param>
		/// <param name="attribute"> : ����</param>
		/// <param name="mask"> : �}�X�N</param>
		/// <param name="radius"> : ���a</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		SphereCollider(
			const YMath::Vector3& offset,
			const AttributeType attribute, const AttributeType mask,
			const float radius,
			const bool isSlip = false);
		
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="pParent"> : �e�g�����X�t�H�[���|�C���^</param>
		/// <param name="offset"> : �I�t�Z�b�g</param>
		/// <param name="attribute"> : ����</param>
		/// <param name="mask"> : �}�X�N</param>
		/// <param name="radius"> : ���a</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		SphereCollider(
			Transform* pParent, const YMath::Vector3& offset,
			const AttributeType attribute, const AttributeType mask,
			const float radius,
			const bool isSlip = false);
		
		~SphereCollider() = default;

	};
}
