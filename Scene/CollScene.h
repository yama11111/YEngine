#pragma once
#include "BaseScene.h"

#include "Floor.h"
#include "Skydome.h"
#include "CollisionManager.h"
#include "CollisionPrimitive.h"
#include <array>

namespace YScene
{
	// �R���W�����V�[��
	class CollScene : public BaseScene
	{
	public:
#pragma region ���\�[�X

		// ----- �e�N�X�`�� ----- //

		// ���n�摜
		UINT plainTex_ = 0;

		// ----- �I�[�f�B�I ----- //

		//UINT aA_ = 0;

		// ----- �X�v���C�g (2D) ----- //

		// ��ʑS��
		std::unique_ptr<YGame::Sprite2D> windowSpr_ = nullptr;

		// ----- �X�v���C�g (3D) ----- //

		// ----- ���f�� ----- //

		// �����̃��f��
		std::unique_ptr<YGame::Model> cubeMod_ = nullptr;

		std::unique_ptr<YGame::Model> sphereMod_ = nullptr;
		std::unique_ptr<YGame::Model> groundMod_ = nullptr;
		std::unique_ptr<YGame::Model> triangleMod_ = nullptr;

#pragma endregion
#pragma region �Q�[���I�u�W�F�N�g

		std::unique_ptr<YGame::ModelObject> planeObj_ = nullptr;
		YGame::Plane plane_;
		std::unique_ptr<YGame::Color> planeColor_;

		std::unique_ptr<YGame::ModelObject> rayObj_ = nullptr;
		YGame::Ray ray_;
		std::unique_ptr<YGame::Color> rayColor_;

		std::unique_ptr<YGame::ModelObject> triangleObj_ = nullptr;
		YGame::Triangle triangle_;
		std::unique_ptr<YGame::Color> triangleColor_;

		std::unique_ptr<YGame::ModelObject> sphereObj_ = nullptr;
		YGame::Sphere sphere_;
		std::unique_ptr<YGame::Color> sphereColor_;

		// �]���p���C�g�O���[�v
		std::unique_ptr<YGame::LightGroup> lightGroup_;

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
		CollScene() = default;
		// �f�X�g���N�^
		~CollScene() = default;
	};
}
