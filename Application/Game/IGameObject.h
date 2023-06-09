#pragma once
#include "Model.h"
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
		void Initialize(
			const Type type,
			const Transform::Status& status,
			const float radius,
			const bool isSlip = false);

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void Update();

		/// <summary>
		/// �`��
		/// </summary>
		virtual void Draw() = 0;
	
	public:

		/// <summary>
		/// ���f���ݒ�
		/// </summary>
		/// <param name="pModel"> : ���f���|�C���^</param>
		void SetModel(Model* pModel);

	public:

		IGameObject() = default;
		
		virtual ~IGameObject() = default;
	
	protected:

		// �g�����X�t�H�[��
		std::unique_ptr<Transform> transform_;

		// 3D�p�I�u�W�F�N�g
		std::unique_ptr<Model::Object> obj_;

		// ���f���|�C���^
		Model* pModel_ = nullptr;
	};
}

