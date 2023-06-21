#pragma once
#include "IDrawer.h"

namespace YGame
{
	class HorseDrawer :
		public IDrawer
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="pParent"> : �e�|�C���^</param>
		void Initialize(Transform* pParent) override;

		/// <summary>
		/// �X�V
		/// </summary>
		void Update() override;

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="location"> : �ꏊ</param>
		void Draw(const DrawLocation location) override;

	public:

		/// <summary>
		/// �A�j���[�V�����Đ�
		/// </summary>
		/// <param name="index"> : �A�j���[�V�����ԍ�</param>
		/// <param name="frame"> : �Đ��t���[��</param>
		void PlayAnimation(const uint16_t index, const uint16_t frame) override;

	public:

		HorseDrawer() = default;

		~HorseDrawer() = default;

	private:

	};
}
