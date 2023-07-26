#include "MyGame.h"
#include "Def.h"
#include "YGameSceneFactory.h"
#include "YGameTransitionFactory.h"
#include "MapChipManager.h"

#include "CBModelTransform.h"
#include "CBSprite2DTransform.h"
#include "CBSprite3DTransform.h"
#include "CBPostEffectTransform.h"
#include "CBColor.h"
#include "CBMaterial.h"
#include "CBLightGroup.h"
#include "CBTexConfig.h"
#include "CBTime.h"

#pragma region ���O��Ԑ錾
using YBase::MyGame;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YScene;
using namespace YGame;
#pragma endregion 

bool MyGame::Initialize()
{
	// ���N���X����������
	if (YFramework::Initialize() == false) { return false; }

	// �p�C�v���C��������
	pipelineMan_ = PipelineManager::GetInstance();
	InitializePipelines();

	// �X�e�[�W
	MapChipManager::GetInstance()->Load("demo.csv");

	// �V�[���t�@�N�g���[�ݒ�
	sceneExe_->SetFactory(new YGameSceneFactory(), new YGameTransitionFactory());

	// �V�[���G�O�[�N�e�B�u������
	sceneExe_->Initialize(YGameSceneFactory::Play_, YGameTransitionFactory::Blackout_);

	return true;
}

void MyGame::Finalize()
{
	// ���N���X�I������
	YFramework::Finalize();
}

void MyGame::Update()
{
	// ���N���X�X�V����
	YFramework::Update();

	// ------------------- �I������ ------------------- //
	// ------------------------------------------------ //
}

void MyGame::Draw()
{
	// �f�X�N���v�^�[�q�[�v�Z�b�g
	descHeap_.SetDrawCommand();

	// �V�[���`��
	sceneExe_->Draw();

	// �`�揀��
	dx_.PreDraw(ClearColor);

	// �X�N���[���ݒ�Z�b�g
	screenDesc_.SetDrawCommand();

	// �Q�[���V�[���`��
	pipelineMan_->Draw();

#ifdef _DEBUG

	// imgui�`��
	imguiMan_.Draw();

#endif // DEBUG

	// �`��㏈��
	dx_.PostDraw();
}

void MyGame::InitializePipelines()
{
	pipelineMan_->Clear();

	// ModelDefault
	{
		ShaderSet shader;

		shader.LoadShader("ModelVS.hlsl", ShaderSet::ShaderType::eVertex);
		shader.LoadShader("ModelPS.hlsl", ShaderSet::ShaderType::ePixel);

		Pipeline* newPipeline =
			Pipeline::Create(
				shader,
				{ 
					CBModelTransform::TypeName(),
					CBColor::TypeName(),
					CBMaterial::TypeName(),
					CBLightGroup::TypeName(),
					CBTexConfig::TypeName(),
				},
				{ 
					"Texture" ,
				},
				1, Model::GetPipelineSetting(),
				Pipeline::BlendState::Alpha, 2
			);

		pipelineMan_->Insert("ModelDefault", newPipeline);
	}

	// ModelPhong
	{
		ShaderSet shader;

		shader.LoadShader("ModelVS.hlsl", ShaderSet::ShaderType::eVertex);
		shader.LoadShader("PhongPS.hlsl", ShaderSet::ShaderType::ePixel);

		Pipeline* newPipeline =
			Pipeline::Create(
				shader,
				{
					CBModelTransform::TypeName(),
					CBColor::TypeName(),
					CBMaterial::TypeName(),
					CBLightGroup::TypeName(),
					CBTexConfig::TypeName(),
				},
				{
					"Texture",
				},
				1, Model::GetPipelineSetting(),
				Pipeline::BlendState::Alpha, 2
			);

		pipelineMan_->Insert("ModelPhong", newPipeline);
	}

	// ModelToon
	{
		ShaderSet shader;

		shader.LoadShader("ModelVS.hlsl", ShaderSet::ShaderType::eVertex);
		shader.LoadShader("ToonPS.hlsl", ShaderSet::ShaderType::ePixel);

		Pipeline* newPipeline =
			Pipeline::Create(
				shader,
				{
					CBModelTransform::TypeName(),
					CBColor::TypeName(),
					CBMaterial::TypeName(),
					CBLightGroup::TypeName(),
					CBTexConfig::TypeName(),
				},
				{
					"Texture",
				},
				1, Model::GetPipelineSetting(),
				Pipeline::BlendState::Alpha, 2
			);

		pipelineMan_->Insert("ModelToon", newPipeline);
	}

	
	// Sprite2DDefault
	{
		ShaderSet shader;

		shader.LoadShader("Sprite2DVS.hlsl", ShaderSet::ShaderType::eVertex);
		shader.LoadShader("Sprite2DPS.hlsl", ShaderSet::ShaderType::ePixel);

		Pipeline* newPipeline =
			Pipeline::Create(
				shader,
				{
					CBSprite2DTransform::TypeName(),
					CBColor::TypeName(),
					CBTexConfig::TypeName(),
				},
				{
					"Texture0",
				},
				1, Sprite2D::GetPipelineSetting(),
				Pipeline::BlendState::Alpha, 1
			);

		pipelineMan_->Insert("Sprite2DDefault", newPipeline);
	}

	
	// Sprite3DDefault
	{
		ShaderSet shader;

		shader.LoadShader("Sprite3DVS.hlsl", ShaderSet::ShaderType::eVertex);
		shader.LoadShader("Sprite3DGS.hlsl", ShaderSet::ShaderType::eGeometry);
		shader.LoadShader("Sprite3DPS.hlsl", ShaderSet::ShaderType::ePixel);

		Pipeline* newPipeline =
			Pipeline::Create(
				shader,
				{
					CBSprite3DTransform::TypeName(),
					CBColor::TypeName(),
					CBTexConfig::TypeName(),
				},
				{
					"Texture",
				},
				1, Sprite3D::GetPipelineSetting(),
				Pipeline::BlendState::Alpha, 2
			);

		pipelineMan_->Insert("Sprite3DDefault", newPipeline);
	}


	// PostEffectDefault
	{
		ShaderSet shader;

		shader.LoadShader("PostEffectVS.hlsl", ShaderSet::ShaderType::eVertex);
		shader.LoadShader("PostEffectPS.hlsl", ShaderSet::ShaderType::ePixel);

		Pipeline* newPipeline =
			Pipeline::Create(
				shader,
				{
					CBPostEffectTransform::TypeName(),
					CBColor::TypeName(),
					CBTexConfig::TypeName(),
				},
				{
					"Texture0",
					"Texture1",
				},
				2, PostEffect::GetPipelineSetting(),
				Pipeline::BlendState::Alpha, 1
			);

		pipelineMan_->Insert("PostEffectDefault", newPipeline);
	}


	// �`�揇��ݒ�
	pipelineMan_->SetDrawOrder(
		{
			"ModelDefault", 
			"ModelPhong", 
			"ModelToon", 
			
			"Sprite3DDefault", 
			
			"Sprite2DDefault", 
			
			"PostEffectDefault", 
		}
	);
}

void MyGame::DrawGameScene()
{	
	pipelineMan_->Draw();
}
