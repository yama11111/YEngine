#pragma once
#include "BaseDrawObject.h"
#include "ViewProjection.h"
#include "ConstBufferObject.h"
#include "CBModelTransform.h"
#include "Model.h"

namespace YGame
{
	class DrawObjectForModel final:
		public BaseDrawObject
	{
	
	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="status"> : �g�����X�t�H�[���X�e�[�^�X</param>
		/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
		/// <param name="pModel"> : ���f���|�C���^</param>
		/// <param name="isClearWhenTransition"> : �J�ڎ��N���A���邩</param>
		/// <returns>�I�u�W�F�N�g�|�C���^ (���I�C���X�^���X)</returns>
		static DrawObjectForModel* Create(
			const Transform::Status& status, 
			ViewProjection* pVP, 
			Model* pModel,
			const bool isClearWhenTransition = true);
	
	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="status"> : �g�����X�t�H�[���X�e�[�^�X</param>
		/// <param name="isClearWhenTransition"> : �J�ڎ��N���A���邩</param>
		void Initialize(
			const Transform::Status& status = Transform::Status::Default(),
			const bool isClearWhenTransition = true) override;

		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="status"> : �g�����X�t�H�[���X�e�[�^�X</param>
		void Update(const Transform::Status& status = {}) override;

	public:

		/// <summary>
		/// �r���[�v���W�F�N�V������ݒ�
		/// </summary>
		/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
		void SetViewProjection(ViewProjection* pVP);

		/// <summary>
		/// ���f����ݒ�
		/// </summary>
		/// <param name="pModel"> : ���f���|�C���^</param>
		void SetModel(Model* pModel);
	
	public:

		~DrawObjectForModel() = default;

	private:

		// �r���[�v���W�F�N�V�����|�C���^
		ViewProjection* pVP_ = nullptr;

		// ���f���p�g�����X�t�H�[���萔�o�b�t�@
		std::unique_ptr<ConstBufferObject<CBModelTransform>> cbTransform_;

	private:

		// �錾�A������֎~
		DrawObjectForModel() = default;

		DrawObjectForModel(const DrawObjectForModel&) = delete;

		const DrawObjectForModel& operator=(const DrawObjectForModel&) = delete;
	};
}
