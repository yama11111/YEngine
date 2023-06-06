#pragma once
#include "Model.h"

namespace YGame
{
	class IGameObject
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
		virtual void Update() = 0;

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

		// �j
		std::unique_ptr<Transform> core_;

		// 3D�p�I�u�W�F�N�g
		std::unique_ptr<Model::Object> obj_;

		// ���f���|�C���^
		Model* pModel_ = nullptr;
	};
}

