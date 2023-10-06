#pragma once
#include "DrawObjectForSprite2D.h"
#include "UINumber.h"
#include "CBColor.h"
#include "Ease.h"
#include "Timer.h"
#include "Power.h"

namespace YGame
{
	class CardDrawer
	{
	
	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="pParent"> : �e�g�����X�t�H�[���|�C���^</param>
		/// <param name="number"> : �ԍ�</param>
		/// <param name="isClear"> : �N���A�t���O</param>
		void Initialize(Transform* pParent, const int32_t number, const bool isClear = false);
		
		/// <summary>
		/// ���Z�b�g
		/// </summary>
		/// <param name="isClear"> : �N���A�t���O</param>
		void Reset(const bool isClear = false);
		
		/// <summary>
		/// �X�V
		/// </summary>
		void Update();
		
		/// <summary>
		/// �`��
		/// </summary>
		void Draw(uint16_t p);
	
	public:
		
		/// <summary>
		/// ����
		/// </summary>
		void Decision() { isDecided_ = true;  }
		
		/// <summary>
		/// �I��ݒ�
		/// </summary>
		/// <param name="isSelect"></param>
		void SetSelect(const bool isSelect) { isSelected_ = isSelect; }
	
	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		static void LoadResource();
	
	private:
	
		// �j
		Transform core_;

		// �����p�I�u�W�F�N�g
		Transform numberTra_;
		std::unique_ptr<UINumber> numberUI_;
		
		// �X�e�[�W�J�[�h
		std::unique_ptr<DrawObjectForSprite2D> cardObj_;
		std::unique_ptr<ConstBufferObject<CBColor>> color_;

		// ����
		int32_t number_ = 0;

		// �I������Ă��邩
		bool isSelected_ = false;
		// �I������Ă�����
		bool isElderSelected_ = false;
		// ���肳�ꂽ��
		bool isDecided_ = false;

		// �ړ��p�C�[�W���O
		YMath::Ease<float> moveEas_;
		// �g��p�C�[�W���O
		YMath::Ease<float> scaleEas_;
		// �I��p�p���[
		YMath::Power selectPow_;

		// �����p�F
		//std::unique_ptr<ConstBufferObject<CBColor>> color_;
		
		// �N���A������
		bool isClear_ = false;

	private:

		static Sprite2D* spCardSpr_;

	private:

		// �I���A�j���[�V�����X�V
		void UpdateSelectAnimation();
	};
}
