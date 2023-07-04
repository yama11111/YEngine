#pragma once
#include "BaseDrawer.h"
#include "BaseCollider.h"

namespace YGame
{
	class GameObject : 
		public DebugTextAttacher
	{

	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="name"> : ���O</param>
		/// <param name="status"> : �������X�e�[�^�X</param>
		/// <param name="pParent"> : �e�|�C���^</param>
		void Initialize(
			const std::string name, 
			const Transform::Status& status,
			GameObject* pParent = nullptr);

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
		/// �g�����X�t�H�[���|�C���^�擾
		/// </summary>
		/// <returns>�g�����X�t�H�[���|�C���^</returns>
		inline Transform* TransformPtr() const { return transform_.get(); }

		/// <summary>
		/// �R���C�_�[�|�C���^�擾
		/// </summary>
		/// <returns>�R���C�_�[�|�C���^</returns>
		inline BaseCollider* ColliderPtr() const { return collider_.get(); }
		
		/// <summary>
		/// �`��N���X�|�C���^
		/// </summary>
		/// <returns>�`��N���X�|�C���^</returns>
		inline BaseDrawer* DrawerPtr() const { return drawer_.get(); }
	
	public:
		
		/// <summary>
		/// �e�q�֌W�ݒ�
		/// </summary>
		/// <param name="pParent"> : �e�|�C���^</param>
		void SetParent(GameObject* pParent);

		/// <summary>
		/// �R���C�_�[�ݒ�
		/// </summary>
		/// <param name="collider"> : �R���C�_�[�C���X�^���X (���I)</param>
		void SetCollider(BaseCollider* collider);

		/// <summary>
		/// �`��N���X�ݒ�
		/// </summary>
		/// <param name="drawer"> : �`��C���X�^���X (���I)</param>
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

		// �e�|�C���^
		GameObject* pParent_ = nullptr;

	protected:

		/// <summary>
		/// �f�o�b�O�e�L�X�g�{��
		/// </summary>
		virtual void DrawDebugTextContent() override;
	};
}
