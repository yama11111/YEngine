#pragma once
#include "BaseDrawer.h"

namespace YGame
{
	class AxisDrawer final :
		public BaseDrawer
	{

	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="pParent"> : �e�|�C���^</param>
		/// <param name="drawPriority"> : �`��D��x</param>
		/// <returns>�v���C���[�`��N���X�|�C���^ (���I�C���X�^���X)</returns>
		static AxisDrawer* Create(Transform* pParent, const uint16_t drawPriority);

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
		/// �X�V
		/// </summary>
		void Update() override;

		/// <summary>
		/// �`��
		/// </summary>
		void Draw() override;

		/// <summary>
		/// �e�g�����X�t�H�[���ݒ�
		/// </summary>
		/// <param name="pParent"> : �e�g�����X�t�H�[���|�C���^</param>
		void SetParent(Transform* pParent) override;

	public:

		AxisDrawer() = default;

		~AxisDrawer() = default;

	private:

		// �I�u�W�F�N�g
		std::array<std::unique_ptr<DrawObjectForModel>, 3> objs_;

		// �F�萔�o�b�t�@
		std::array<std::unique_ptr<ConstBufferObject<CBColor>>, 3> cbColors_;
	
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
		void UpdateAnimtion() override {};
	};
}
