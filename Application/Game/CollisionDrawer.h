#pragma once
#include "BaseDrawer.h"

namespace YGame
{
	class CollisionDrawer final :
		public BaseDrawer
	{

	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="pParent"> : �e�|�C���^</param>
		/// <param name="radius"> : ���a</param>
		/// <param name="drawPriority"> : �`��D��x</param>
		/// <returns>�v���C���[�`��N���X�|�C���^ (���I�C���X�^���X)</returns>
		static CollisionDrawer* Create(Transform* pParent, const float radius, const uint16_t drawPriority);

		/// <summary>
		/// �ÓI������
		/// </summary>
		static void StaticInitialize();

		/// <summary>
		/// ���O�擾
		/// </summary>
		/// <returns>���O</returns>
		static std::string Name();

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="pParent"> : �e�|�C���^</param>
		/// <param name="drawPriority"> : �`��D��x</param>
		void Initialize(Transform* pParent, const uint16_t drawPriority) override;

		/// <summary>
		/// ���a�擾
		/// </summary>
		/// <param name="radius"> : ���a</param>
		void SetRadius(const float radius);

	public:

		CollisionDrawer() = default;

		~CollisionDrawer() = default;

	private:

		// ���f���|�C���^
		static Model* spModel_;

	private:

		/// <summary>
		/// �A�j���[�V�����^�C�}�[�}��
		/// </summary>
		void InsertAnimationTimers() override {};

		/// <summary>
		/// �T�u�A�j���[�V�����Đ�
		/// </summary>
		/// <param name="index"> : �A�j���[�V�����ԍ�</param>
		/// <param name="frame"> : �Đ��t���[��</param>
		void PlaySubAnimation(const uint16_t index, const uint32_t frame) override {};

		/// <summary>
		/// �A�j���[�V�����X�V
		/// </summary>
		void UpdateAnimation() override {};

	};
}
