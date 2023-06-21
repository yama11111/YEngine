#pragma once
#include "UIButtonDrawer.h"
#include "Lerp.h"
#include "Power.h"

namespace YGame
{
    class UIChargeButtonDrawer :
        public UIButtonDrawer
    {

    public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="pButtonTex"> : �{�^���e�N�X�`��</param>
		/// <param name="pPressedTex"> : �����ꂽ�{�^���e�N�X�`��</param>
		/// <param name="pPressedTex"> : ���񂾃{�^���e�N�X�`��</param>
        /// <param name="frame"> : ���܂鎞��</param>
        void Initialize(Texture* pButtonTex, Texture* pPressedTex, Texture* pDeadTex, const unsigned int frame);

        /// <summary>
		/// �X�V
		/// </summary>
		/// <param name="isPush"> : ��������</param>
        void Update(const bool isPush) override;

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="pObject"> : �I�u�W�F�N�g�|�C���^</param>
		void Draw(Sprite2D::Object* pObject) override;
		
		/// <summary>
		/// �`���[�W���^�����擾
		/// </summary>
		/// <returns>�`���[�W���^����</returns>
		bool IsChargeMax() { return chargePower_.IsMax(); }

    public:

		
		std::unique_ptr<Sprite2D::Object> chargeGaugeObj1_;
		std::unique_ptr<Sprite2D::Object> chargeGaugeObj2_;
		std::unique_ptr<Sprite2D::Object> chargeGaugeObj3_;

        // �`���[�W�^�C�}�[
        YMath::Power chargePower_;

        // �`���[�W�C�[�W���O
		YMath::Ease<float> chargeWidthEase_;

		
	public:
		
		static Sprite2D* spChargeGauge_;
		
		static std::unique_ptr<CBColor> sChargeGaugeColor1_;
		static std::unique_ptr<CBColor> sChargeGaugeColor2_;
		static std::unique_ptr<CBColor> sChargeGaugeColor3_;

	public:

		static void StaticInitialize();
    };
}
