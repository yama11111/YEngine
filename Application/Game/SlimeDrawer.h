#pragma once
#include "BaseDrawer.h"
#include "SlimeActor.h"
#include "HitActor.h"

namespace YGame
{
	class SlimeDrawer final :
		public BaseDrawer,
		public SlimeActor,
		public HitActor
	{

	public:

		// �A�j���[�V����
		enum class AnimationType : uint16_t
		{
			// ����
			eIdle	 = 0b1,

			// �W�����v
			eJump	 = 0b1 << 1,

			// ���n
			eLanding = 0b1 << 2,

			// ��e
			eHit	 = 0b1 << 3,

			// ���S
			eDead	 = 0b1 << 4,
		};

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

		SlimeDrawer() = default;

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="drawPriority"> : �`��D��x</param>
		SlimeDrawer(const uint32_t drawPriority);

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="pParent"> : �e�|�C���^</param>
		/// <param name="drawPriority"> : �`��D��x</param>
		SlimeDrawer(Transform * pParent, const uint32_t drawPriority);

		~SlimeDrawer() = default;

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		static void StaticInitialize();

	private:

		// ����
		YMath::Timer IdleTimer_;

		// �W�����v
		YMath::Timer JumpTimer_;

		// ���n
		YMath::Timer LandingTimer_;

		// ��e
		YMath::Timer HitTimer_;

		// ���S
		YMath::Timer DeadTimer_;


		// ���f���|�C���^
		static Model* spModel_;

	private:

		/// <summary>
		/// �^�C�}�[�X�V
		/// </summary>
		void TimerUpdate();

		/// <summary>
		/// �A�j���[�V�����A�b�v�f�[�g
		/// </summary>
		void AnimationUpdate();
	};
}