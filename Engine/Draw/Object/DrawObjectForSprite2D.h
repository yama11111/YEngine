#pragma once
#include "BaseDrawObject.h"
#include "ConstBufferObject.h"
#include "CBSprite2DTransform.h"
#include "Sprite2D.h"

namespace YGame
{
	class DrawObjectForSprite2D final:
		public BaseDrawObject
	{

	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="status"> : �g�����X�t�H�[���X�e�[�^�X</param>
		/// <param name="pSprite2D"> : �X�v���C�g2D�|�C���^</param>
		/// <param name="isClearWhenTransition"> : �J�ڎ��N���A���邩</param>
		/// <returns>�I�u�W�F�N�g�|�C���^ (���I�C���X�^���X)</returns>
		static DrawObjectForSprite2D* Create(
			const Transform::Status& status,
			Sprite2D* pSprite2D, 
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
		/// �X�v���C�g2D��ݒ�
		/// </summary>
		/// <param name="pSprite2D"> : �X�v���C�g2D�|�C���^</param>
		void SetSprite2D(Sprite2D* pSprite2D);

	public:

		~DrawObjectForSprite2D() = default;

	private:

		// ���f���p�g�����X�t�H�[���萔�o�b�t�@
		std::unique_ptr<ConstBufferObject<CBSprite2DTransform>> cbTransform_;

	private:

		// �錾�A������֎~
		DrawObjectForSprite2D() = default;

		DrawObjectForSprite2D(const DrawObjectForSprite2D&) = delete;

		const DrawObjectForSprite2D& operator=(const DrawObjectForSprite2D&) = delete;
	};
}
