#pragma once
#include "BaseDrawer.h"
namespace YGame
{
	class GoalDrawer final :
		public BaseDrawer
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="pParent"> : �e�|�C���^</param>
		/// <param name="drawPriority"> : �`��D��x</param>
		void Initialize(Transform* pParent, const uint32_t drawPriority) override;

		/// <summary>
		/// �X�V
		/// </summary>
		void Update() override;

		/// <summary>
		/// �`��
		/// </summary>
		void Draw() override;

		/// <summary>
		/// �A�j���[�V�����Đ�
		/// </summary>
		/// <param name="index"> : �A�j���[�V�����ԍ�</param>
		/// <param name="frame"> : �Đ��t���[��</param>
		void PlayAnimation(const uint16_t index, const uint32_t frame) override;

	public:

		GoalDrawer() = default;

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="drawPriority"> : �`��D��x</param>
		GoalDrawer(const uint32_t drawPriority);

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="pParent"> : �e�|�C���^</param>
		/// <param name="drawPriority"> : �`��D��x</param>
		GoalDrawer(Transform * pParent, const uint32_t drawPriority);

		~GoalDrawer() = default;

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		static void StaticInitialize();

	private:

		// ���f���|�C���^
		static Model* spModel_;

	};
}