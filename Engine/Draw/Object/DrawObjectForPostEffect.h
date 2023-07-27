#pragma once
#include "BaseDrawObject.h"
#include "ConstBufferObject.h"
#include "CBPostEffectTransform.h"
#include "PostEffect.h"

namespace YGame
{
	class DrawObjectForPostEffect final:
		public BaseDrawObject
	{

	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="status"> : �g�����X�t�H�[���X�e�[�^�X</param>
		/// <param name="pPostEffect"> : �|�X�g�G�t�F�N�g�|�C���^</param>
		/// <param name="isClearWhenTransition"> : �J�ڎ��N���A���邩</param>
		/// <returns>�I�u�W�F�N�g�|�C���^ (���I�C���X�^���X)</returns>
		static DrawObjectForPostEffect* Create(
			const Transform::Status& status,
			PostEffect* pPostEffect,
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
		/// �|�X�g�G�t�F�N�g��ݒ�
		/// </summary>
		/// <param name="pPostEffect"> : �|�X�g�G�t�F�N�g�|�C���^</param>
		void SetPostEffect(PostEffect* pPostEffect);

	public:

		~DrawObjectForPostEffect() = default;

	private:

		// ���f���p�g�����X�t�H�[���萔�o�b�t�@
		std::unique_ptr<ConstBufferObject<CBPostEffectTransform>> cbTransform_;

	private:

		// �錾�A������֎~
		DrawObjectForPostEffect() = default;

		DrawObjectForPostEffect(const DrawObjectForPostEffect&) = delete;

		const DrawObjectForPostEffect& operator=(const DrawObjectForPostEffect&) = delete;
	};
}
