#pragma once
#include "UINumber.h"
#include "CBColor.h"
#include "Ease.h"
#include "Power.h"
#include <memory>

namespace YGame
{
	class ScoreManager final
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		void Initialize();

		/// <summary>
		/// �X�V
		/// </summary>
		void Update();

		/// <summary>
		/// �`��
		/// </summary>
		void Draw();
	
	public:

		/// <summary>
		/// ���\�[�X�ǂݍ���
		/// </summary>
		static void LoadResource();

	private:

		// UI
		std::unique_ptr<UINumber> uiNum_;

		// �X�R�A
		uint32_t score_;


	};
}
