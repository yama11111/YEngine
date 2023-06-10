#pragma once
#include "IDrawer.h"
#include "GameObjectCollider.h"

namespace YGame
{
	class IGameObject : 
		public GameObjectCollider
	{

	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="type"> : ���</param>
		/// <param name="status"> : �������X�e�[�^�X</param>
		/// <param name="radius"> : ���a</param>
		/// <param name="isSlip"> : ����ʂ��t���O</param>
		/// <param name="drawer"> : �`��N���X</param>
		void Initialize(
			const Type type,
			const Transform::Status& status,
			const float radius,
			const bool isSlip = false,
			IDrawer* drawer = nullptr);

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void Update();

		/// <summary>
		/// �`��
		/// </summary>
		virtual void Draw() = 0;
	
	protected:

		/// <summary>
		/// �`��N���X�ݒ�
		/// </summary>
		/// <param name="drawer"> : �`��N���X</param>
		void SetDrawer(IDrawer* drawer);

	public:

		IGameObject() = default;
		
		virtual ~IGameObject() = default;
	
	protected:

		// �g�����X�t�H�[��
		std::unique_ptr<Transform> transform_;

		// �`��N���X
		std::unique_ptr<IDrawer> drawer_;
	};
}
