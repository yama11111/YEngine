#pragma once
#include "BaseDrawObject.h"
#include "ViewProjection.h"
#include "ConstBufferObject.h"
#include "CBSprite3DTransform.h"
#include "Sprite3D.h"

namespace YGame
{
	class DrawObjectForSprite3D :
		public BaseDrawObject
	{

	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="status"> : �g�����X�t�H�[���X�e�[�^�X</param>
		/// <param name="isXAxisBillboard"> : X���r���{�[�h�t���O</param>
		/// <param name="isYAxisBillboard"> : Y���r���{�[�h�t���O</param>
		/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
		/// <param name="pSprite3D"> : �X�v���C�g3D�|�C���^</param>
		/// <param name="isClearWhenTransition"> : �J�ڎ��N���A���邩</param>
		/// <returns>�I�u�W�F�N�g�|�C���^ (���I�C���X�^���X)</returns>
		static DrawObjectForSprite3D* Create(
			const Transform::Status& status,
			const bool isXAxisBillboard, const bool isYAxisBillboard, 
			ViewProjection* pVP,
			Sprite3D* pSprite3D, 
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
		/// �r���{�[�h�ݒ�
		/// </summary>
		/// <param name="isXAxisBillbord"> : X���r���{�[�h�t���O</param>
		/// <param name="isYAxisBillbord"> : Y���r���{�[�h�t���O</param>
		void SetBillboardFrag(const bool isXAxisBillbord, const bool isYAxisBillbord);

		/// <summary>
		/// �r���[�v���W�F�N�V������ݒ�
		/// </summary>
		/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
		void SetViewProjection(ViewProjection* pVP);

		/// <summary>
		/// �X�v���C�g3D��ݒ�
		/// </summary>
		/// <param name="pSprite3D"> : �X�v���C�g3D�|�C���^</param>
		void SetSprite3D(Sprite3D* pSprite3D);

	public:

		~DrawObjectForSprite3D() = default;

	private:

		// X���r���{�[�h�t���O
		bool isXAxisBillboard_ = false;
		
		// Y���r���{�[�h�t���O
		bool isYAxisBillboard_ = false;

		// �r���[�v���W�F�N�V�����|�C���^
		ViewProjection* pVP_ = nullptr;

		// �X�v���C�g3D�p�g�����X�t�H�[���萔�o�b�t�@
		std::unique_ptr<ConstBufferObject<CBSprite3DTransform>> cbTransform_;

	private:

		// �錾�A������֎~
		DrawObjectForSprite3D() = default;

		DrawObjectForSprite3D(const DrawObjectForSprite3D&) = delete;

		const DrawObjectForSprite3D& operator=(const DrawObjectForSprite3D&) = delete;

	};
}
