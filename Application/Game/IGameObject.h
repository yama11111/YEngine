#pragma once
#include "IDrawer.h"

namespace YGame
{
	class IGameObject
	{

	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="status"> : �������X�e�[�^�X</param>
		/// <param name="drawer"> : �`��N���X(���I)</param>
		/// <param name="location"> : �`��ʒu</param>
		void Initialize(
			const Transform::Status& status,
			IDrawer* drawer = nullptr, 
			const DrawLocation location = DrawLocation::eCenter);

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void Update();

		/// <summary>
		/// �`��
		/// </summary>
		virtual void Draw();
	
	protected:

		/// <summary>
		/// �`��N���X�ݒ�
		/// </summary>
		/// <param name="drawer"> : �`��N���X(���I)</param>
		void SetDrawer(IDrawer* drawer);

		/// <summary>
		/// �`��ʒu�ݒ�
		/// </summary>
		/// <param name="location"> : �`��ʒu</param>
		void SetDrawLocation(const DrawLocation location);

	public:

		IGameObject() = default;
		
		virtual ~IGameObject() = default;
	
	protected:

		// �g�����X�t�H�[��
		std::unique_ptr<Transform> transform_;

		// �`��N���X
		std::unique_ptr<IDrawer> drawer_;

		// �`��ʒu
		DrawLocation location_;

	};
}
