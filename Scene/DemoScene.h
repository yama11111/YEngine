#pragma once
#include "BaseScene.h"

#include "Floor.h"
#include "Skydome.h"
#include "Player.h"
#include "EnemyManager.h"
#include "CollisionManager.h"
#include "CollisionPrimitive.h"
#include "MapChipManager.h"
#include "CameraManager.h"
#include "ParticleManager.h"
#include <array>

namespace YScene
{
	// �Q�[���f���V�[��
	class DemoScene : public BaseScene
	{
	public:
#pragma region ���\�[�X

		// ----- �e�N�X�`�� ----- //

		// ���n�摜
		UINT plainTex_ = 0;

		// �}�b�v�`�b�v2D�摜
		UINT mapDispTex_ = 0;
		// �}�b�v�`�b�v3D�摜
		UINT mapTex_ = 0;

		// ----- �I�[�f�B�I ----- //

		// ----- �X�v���C�g (2D) ----- //

		// ��ʑS��
		std::unique_ptr<YGame::Sprite2D> windowSpr_ = nullptr;

		// �}�b�v2D�\���p
		std::unique_ptr<YGame::Sprite2D> mapDispSpr_ = nullptr;

		// ----- �X�v���C�g (3D) ----- //


		// ----- ���f�� ----- //

		// �����̃��f��
		std::unique_ptr<YGame::Model> cubeMod_ = nullptr;

		// �V�����f��
		std::unique_ptr<YGame::Model> skydomeMod_ = nullptr;
		// �r�����f��
		std::unique_ptr<YGame::Model> buildingMod_ = nullptr;
		// �o���A���f��
		std::unique_ptr<YGame::Model> barrierMod_ = nullptr;


#pragma endregion
#pragma region �Q�[���I�u�W�F�N�g

		YMath::Vector3 center_;

		// �v���C���[
		Player player_;
		
		// �r��
		std::array<std::unique_ptr<YGame::ModelObject>, 8> buildings_;
		std::unique_ptr<YGame::Color> buildingColor_;

		// �}�b�v�}�l�[�W���[
		YGame::MapChipManager mapMan_;

		// �p�[�e�B�N���}�l�[�W���[
		YGame::ParticleManager particleMan_;

		// �V��
		YGame::Skydome skydome_;

		// �J�����}�l�[�W���[
		YGame::CameraManager cameraMan_;

		// �]���p���C�g�O���[�v
		std::unique_ptr<YGame::LightGroup> lightGroup_;
		std::unique_ptr<YGame::LightGroup> lightGroup2_;

		// �]���p�r���[�v���W�F�N�V����
		YGame::ViewProjection vp_;

		// �A�^������}�l�[�W���[
		YGame::CollisionManager collMan_;

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
		// �X�v���C�g3D�`��
		void DrawBackSprite3Ds();
		// ���f���`��
		void DrawModels();
		// �X�v���C�g3D�`��
		void DrawFrontSprite3Ds();
		// �O�i�X�v���C�g2D�`��
		void DrawFrontSprite2Ds();
	public:
		// �R���X�g���N�^
		DemoScene() = default;
		// �f�X�g���N�^
		~DemoScene() = default;
	};
}