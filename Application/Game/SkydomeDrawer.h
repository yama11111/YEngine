#pragma once
#include "BaseDrawer.h"

namespace YGame
{
	class SkydomeDrawer final :
		public BaseDrawer
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="pParent"> : �e�|�C���^</param>
		/// <param name="location"> : �`��ʒu</param>
		virtual void Initialize(Transform* pParent, const DrawLocation location) override;

		/// <summary>
		/// �X�V
		/// </summary>
		void Update() override;

		/// <summary>
		/// �`��
		/// </summary>
		void Draw() override;

	public:

		/// <summary>
		/// �A�j���[�V�����Đ�
		/// </summary>
		/// <param name="index"> : �A�j���[�V�����ԍ�</param>
		/// <param name="frame"> : �Đ��t���[��</param>
		void PlayAnimation(const uint16_t index, const uint32_t frame) override;

	public:

		SkydomeDrawer() = default;

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="location"> : �`��ʒu</param>
		SkydomeDrawer(const DrawLocation location);

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="pParent"> : �e�|�C���^</param>
		/// <param name="location"> : �`��ʒu</param>
		SkydomeDrawer(Transform* pParent, const DrawLocation location);

		~SkydomeDrawer() = default;

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
