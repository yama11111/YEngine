#pragma once
#include "IMapChip.h"
#include "IDrawer.h"

namespace YGame
{
	class MapChip :
		public IMapChip
	{

	public:

		/// <summary>
		/// ���Z�b�g
		/// </summary>
		void Reset() override;

		/// <summary>
		/// �X�V
		/// </summary>
		void Update() override;

		/// <summary>
		/// �`��
		/// </summary>
		void Draw() override;

	private:

		// �`�b�v���Ƃ̃A�^������
		bool CollisionChip(const int x, const int y) override;

	private:

		// �`�b�v�f�[�^
		struct ChipData
		{
			// �g�����X�t�H�[��
			Transform transform_;

			// �`��N���X
			std::unique_ptr<IDrawer> drawer_;

			// �A�^������|�C���^
			bool* pIsColl_ = nullptr;
		};

	private:

		// �`�b�v���X�g
		std::list<std::unique_ptr<ChipData>> chips_;

	};
}
