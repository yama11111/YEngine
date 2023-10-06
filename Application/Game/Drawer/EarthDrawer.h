#pragma once
#include "BaseDrawer.h"

namespace YGame
{
	class EarthDrawer final : 
		public BaseDrawer
	{

	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="pParent"> : �e�|�C���^</param>
		/// <param name="drawPriority"> : �`��D��x</param>
		/// <returns>�`��N���X�|�C���^ (���I�C���X�^���X)</returns>
		static EarthDrawer* Create(Transform* pParent, const size_t drawPriority);

		/// <summary>
		/// �ÓI������
		/// </summary>
		static void LoadResource();

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="pParent"> : �e�|�C���^</param>
		/// <param name="drawPriority"> : �`��D��x</param>
		void Initialize(Transform* pParent, const size_t drawPriority) override;

	public:

		EarthDrawer() = default;

		~EarthDrawer() = default;

	private:

		// ���f���|�C���^
		static Model* spModel_;

	private:

		/// <summary>
		/// �A�j���[�V�����^�C�}�[�}��
		/// </summary>
		void InsertAnimationTimers() override;

		/// <summary>
		/// �T�u�A�j���[�V�����Đ�
		/// </summary>
		/// <param name="index"> : �A�j���[�V�����ԍ�</param>
		/// <param name="frame"> : �Đ��t���[��</param>
		void PlaySubAnimation(const uint16_t index, const uint32_t frame) override;

		/// <summary>
		/// �A�j���[�V�����X�V
		/// </summary>
		void UpdateAnimation() override;
	};
}