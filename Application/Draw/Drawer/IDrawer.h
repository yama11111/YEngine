#pragma once
#include "Model.h"

namespace YGame
{
	class IDrawer
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="pParent"> : �e�|�C���^</param>
		virtual void Initialize(Transform* pParent);

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void Update() = 0;

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="location"> : �ꏊ</param>
		virtual void Draw(const DrawLocation location) = 0;

	public:

		/// <summary>
		/// �A�j���[�V�����Đ�
		/// </summary>
		/// <param name="index"> : �A�j���[�V�����ԍ�</param>
		/// <param name="frame"> : �Đ��t���[��</param>
		virtual void PlayAnimation(const uint16_t index, const uint16_t frame) = 0;

	public:

		IDrawer() = default;

		virtual ~IDrawer() = default;

	protected:

		// 3D�p�I�u�W�F�N�g
		std::unique_ptr<Model::Object> obj_;

		// ���f���|�C���^
		Model* pModel_ = nullptr;
	};
}
