#pragma once
#include "Sprite2D.h"
#include <array>

namespace YGame
{
	class UIButtonDrawer
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="pButtonTex"> : �{�^���e�N�X�`��</param>
		/// <param name="pPressedTex"> : �����ꂽ�{�^���e�N�X�`��</param>
		/// <param name="pPressedTex"> : ���񂾃{�^���e�N�X�`��</param>
		void Initialize(Texture* pButtonTex, Texture* pPressedTex, Texture* pDeadTex = nullptr);

		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="isPush"> : ��������</param>
		virtual void Update(const bool isPush);

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="pObject"> : �I�u�W�F�N�g�|�C���^</param>
		virtual void Draw(Sprite2D::Object* pObject);

	public:

		/// <summary>
		/// �{�^�����E����
		/// </summary>
		void SetIsDead(const bool isDead);

	public:

		~UIButtonDrawer() = default;

	protected:

		// �{�^���X�v���C�g�z��
		std::array<Sprite2D*, 2> pButtonSpr_{};
		
		// �f�b�h�{�^���X�v���C�g
		Sprite2D* pDeadButtonSpr_ = nullptr;

		// ��������
		bool isPush_ = false;

		// �����Ȃ���
		bool isDead_ = false;
	};
}

