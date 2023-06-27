#pragma once
#include "BaseDrawer.h"
#include "BaseCollider.h"

namespace YGame
{
	class GameObject
	{

	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="status"> : �������X�e�[�^�X</param>
		void Initialize(const Transform::Status& status);

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void Update();

		/// <summary>
		/// �`��
		/// </summary>
		virtual void Draw();

		/// <summary>
		/// �Փ˔���
		/// </summary>
		virtual void OnCollision();

	public:

		/// <summary>
		/// �R���C�_�[�|�C���^�擾
		/// </summary>
		/// <returns>�R���C�_�[�|�C���^</returns>
		BaseCollider* ColliderPtr() const { return collider_.get(); }
	
	protected:
		
		/// <summary>
		/// �R���C�_�[�ݒ�
		/// </summary>
		/// <param name="collider"> : �R���C�_�[�N���X (���I)</param>
		void SetCollider(BaseCollider* collider);

		/// <summary>
		/// �`��N���X�ݒ�
		/// </summary>
		/// <param name="drawer"> : �`��N���X (���I)</param>
		void SetDrawer(BaseDrawer* drawer);

	public:

		GameObject() = default;
		
		virtual ~GameObject() = default;
	
	protected:

		// �g�����X�t�H�[��
		std::unique_ptr<Transform> transform_;
		
		// �R���C�_�[�N���X
		std::unique_ptr<BaseCollider> collider_;

		// �`��N���X
		std::unique_ptr<BaseDrawer> drawer_;

	};
}
