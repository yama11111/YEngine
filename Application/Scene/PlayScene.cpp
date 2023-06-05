#include "PlayScene.h"
#include "SceneExecutive.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#pragma region ���O��Ԑ錾

using YScene::PlayScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;

#pragma endregion 

#pragma region Static�֘A
#pragma endregion 


#pragma region �ǂݍ���
void PlayScene::Load()
{
	pModel_ = Model::CreateCube("face.png");

}
#pragma endregion


#pragma region ������
void PlayScene::Initialize()
{
	modelObj_.reset(Model::Object::Create());
	modelObj_->SetViewProjection(&transferVP_);

	// �r���[�v���W�F�N�V����������
	transferVP_.Initialize();
	transferVP_.eye_ = Vector3(0, +2.5f, -20.0f);
}
#pragma endregion


#pragma region �I������
void PlayScene::Finalize()
{
}
#pragma endregion


#pragma region �X�V
void PlayScene::Update()
{
	modelObj_->rota_.y_ += 0.025f;
	modelObj_->UpdateMatrix();

	// �r���[�v���W�F�N�V�����X�V
	transferVP_.UpdateMatrix();
}
#pragma endregion


#pragma region �`��
void PlayScene::Draw()
{
	pModel_->SetDrawCommand(modelObj_.get(), DrawLocation::eCenter);
}
#pragma endregion