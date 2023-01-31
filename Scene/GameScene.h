#pragma once
#include "BaseScene.h"

#include "Floor.h"
#include "Skydome.h"
#include "Player.h"
#include "PlayerDrawer.h"
#include "EnemyManager.h"
#include "CollisionManager.h"
#include "MapChipManager.h"
#include "CameraManager.h"

namespace YScene
{
	class GameScene : public BaseScene
	{
	public:
#pragma region ���\�[�X

		// ----- �e�N�X�`�� ----- //
		
		// ���n�摜
		UINT plainT_ = 0;
		// �v���C���[�摜
		UINT playerT_ = 0;
		// �G�l�~�[�摜
		UINT enemyT_ = 0;
		// �}�b�v�摜
		UINT mapT_ = 0;
		// �}�b�v2D�\���p�摜
		UINT mapDispT_ = 0;

		// ----- �I�[�f�B�I ----- //

		//UINT aA_ = 0;

		// ----- �X�v���C�g ----- //
		
		// ��ʑS��
		std::unique_ptr<YGame::Sprite2D> windowS_ = nullptr;
		// �V�[���J�ڗp
		std::unique_ptr<YGame::Sprite2D> curtenS_ = nullptr;
		// �}�b�v2D�\���p
		std::unique_ptr<YGame::Sprite2D> mapDispS_ = nullptr;

		// ----- ���f�� ----- //
		
		// �����̃��f��
		std::unique_ptr<YGame::Model> cubeM_ = nullptr;
		// �V�����f��
		std::unique_ptr<YGame::Model> skydomeM_ = nullptr;
		// �X���C�����f��
		std::unique_ptr<YGame::Model> slimeM_ = nullptr;

		// ���񂾂��񃂃f��
		std::unique_ptr<YGame::Model> zundamonM_ = nullptr;

		// ----- �r���{�[�h ----- //


#pragma endregion
#pragma region �Q�[���I�u�W�F�N�g

		// �v���C���[
		std::unique_ptr<YGame::ObjectModel> player_;
		YDrawer::PlayerDrawer playerDra_;

		// �}�b�v�}�l�[�W���[
		MapChipManager mapMan_;

		// �p�[�e�B�N���}�l�[�W���[
		//YParticle::ParticleManager particleMan_;

		// �V��
		//Skydome skydome_;

		// �J�����}�l�[�W���[
		YCamera::CameraManager cameraMan_;

		// �]���p���C�g�O���[�v
		std::unique_ptr<YGame::LightGroup> lightGroup_;
		YMath::Vec3 lightDire1_;
		YMath::Vec3 lightDire2_;

		// �]���p�r���[�v���W�F�N�V����
		YGame::ViewProjection vp_;

		// �A�^������}�l�[�W���[
		YCollision::CollisionManager collMan_;

		// �V�[���}�l�[�W���[
		//SceneManager sceneMan_;

#pragma endregion
	public:
		// �ǂݍ���
		void Load() override;
		// ������
		void Initialize() override;
		// �I������
		void Finalize() override;
		// �X�V
		void Update() override;
		// �`��
		void Draw() override;
	private:
		// �w�i�X�v���C�g2D�`��
		void DrawBackSprite2Ds();
		// ���f���`��
		void DrawModels();
		// �X�v���C�g3D�`��
		void DrawSprite3Ds();
		// �O�i�X�v���C�g2D�`��
		void DrawFrontSprite2Ds();
	public:
		// �R���X�g���N�^
		GameScene() = default;
		// �f�X�g���N�^
		~GameScene() = default;
	};
}
