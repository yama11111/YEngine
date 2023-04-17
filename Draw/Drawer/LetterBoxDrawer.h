#pragma once
#include "Sprite2D.h"
#include <array>

namespace YGame
{
	class LetterBoxDrawerCommon
	{
	protected:
		// �ÓI�X�v���C�g
		static YGame::Sprite2D* spSpr_;
	public:
		// �ÓI������
		static void StaticInitialize();
	public:
		virtual ~LetterBoxDrawerCommon() = default;
	};

	class LetterBoxDrawer : private LetterBoxDrawerCommon
	{
	private:
		// �X�v���C�g�I�u�W�F�N�g
		std::array<std::unique_ptr<YGame::Sprite2DObject>, 2> sprObjs_;
		// �F
		std::unique_ptr<YGame::Color> color_;

		// ���� (��)
		float topHeight_ = 0.0f;
		// ���� (��)
		float bottomHeight_ = 0.0f;
	public:
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="topHeight"> : �㑤�̍���</param>
		/// <param name="bottoomHeight"> : �����̍���</param>
		void Initialize(const float topHeight, const float bottomHeight);
		// ���Z�b�g (���g����������)
		void Reset();
		// �X�V
		void Update();
		// �`��
		void Draw();
	public:
		~LetterBoxDrawer() = default;
	};
}