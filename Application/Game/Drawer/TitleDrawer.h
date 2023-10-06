#pragma once
#include "PlayerDrawer.h"
#include "HorseDrawer.h"
#include "MapchipManager.h"

#include "Level.h"

#include "UIButton.h"
#include "UILetterBox.h"

namespace YGame
{
	class TitleDrawer
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
		/// �J�n�A�j���[�V����
		/// </summary>
		void StartAnimation();
		
		/// <summary>
		/// �I�[�v�j���O�A�j���[�V����
		/// </summary>
		void OpeningAnimation();
	
	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		static void LoadResource();
	
	private:

		// �^�C�g��
		std::unique_ptr<DrawObjectForSprite2D> logoObj_;
		std::unique_ptr<DrawObjectForSprite2D> lineObj_;
		std::unique_ptr<DrawObjectForSprite2D> nameObj_;

		// �X�^�[�g
		std::unique_ptr<DrawObjectForSprite2D> startObj_;
		std::unique_ptr<ConstBufferObject<CBColor>> startColor_;

		// �X�^�[�g�{�^��
		std::unique_ptr<UIButton> startButton_;

		// ����
		std::unique_ptr<UILetterBox> letterBox_;

		// �v���C���[
		Transform player_;
		std::unique_ptr<PlayerDrawer> playerDra_;

		// �E�}
		Transform horse_;
		std::unique_ptr<HorseDrawer> horseDra_;

		// ���x��
		Level* pLevel_ = nullptr;

		
		std::array<YMath::Timer, 2> openingTims_;
		std::array<YMath::Ease<YMath::Vector3>, 2> titlePosEass_;
		std::array<YMath::Ease<float>, 2> titleScaleEass_;
		SlimeActor slimeActor_;

	private:

		static Sprite2D* spLogoSpr_;
		static Sprite2D* spLineSpr_;
		static Sprite2D* spNameSpr_;
		
		static Sprite2D* spStartSpr_;
		static Sprite2D* spButtonSpr_;
		
		static MapChipManager* spMapChipManager_;

	};
}

