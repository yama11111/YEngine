#include "MyGame.h"
#include "Def.h"
#include "YGameSceneFactory.h"
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

#include "DustParticle.h"
#include "DebriParticle.h"

#include "BlackoutTransition.h"
#include "WindBlocks.h"
#include "WaveTransition.h"

#include "StageManager.h"

#include "DefaultDrawer.h"
#include "PlayerDrawer.h"
#include "HorseDrawer.h"
#include "SlimeDrawer.h"
#include "SlashAttackDrawer.h"
#include "SnortAttackDrawer.h"
#include "BlockDrawer.h"
#include "GoalDrawer.h"
#include "CloudDrawer.h"
#include "SkydomeDrawer.h"
#include "AxisDrawer.h"
#include "CollisionDrawer.h"

#include "TitleDrawer.h"
#include "SelectDrawer.h"
#include "EarthDrawer.h"
#include "StageDrawer.h"
#include "CardDrawer.h"

#include "UIManager.h"
#include "UILetterBox.h"
#include "UIDigit.h"

#include "PauseManager.h"

#pragma region ���O��Ԑ錾
using YBase::MyGame;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;
using namespace YGame;
#pragma endregion 

bool MyGame::Initialize()
{
	// ���N���X����������
	if (YFramework::Initialize() == false) { return false; }

	InitializePipelines();

	InitializeParticles();

	InitializeTransition();

	LoadMapData();

	LoadDrawer();
	

	// �V�[���t�@�N�g���[�ݒ�
	sceneMan_->SetSceneFactory(new YGameSceneFactory());

	// �V�[���}�l�[�W���[������
	sceneMan_->Initialize(YGameSceneFactory::Title_);

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
	sceneMan_->Draw();

	// �p�[�e�B�N���`��
	pParticleMan_->Draw();

	// �`�揀��
	dx_.PreDraw(ClearColor);

	// �X�N���[���ݒ�Z�b�g
	screenDesc_.SetDrawCommand();

	// �p�C�v���C���`��
	pPipelineMan_->Draw();

#ifdef _DEBUG

	// imgui�`��
	imguiMan_.Draw();

#endif // DEBUG

	// �`��㏈��
	dx_.PostDraw();
}

void MyGame::InitializePipelines()
{
	pPipelineMan_->Clear();

	// ModelDefault
	{
		ShaderSet shader;

		shader.LoadShader("ModelVS.hlsl", ShaderSet::ShaderType::eVertex);
		shader.LoadShader("ModelPS.hlsl", ShaderSet::ShaderType::ePixel);

		Pipeline* newPipeline =
			Pipeline::Create(
				shader,
				{ 
					CBModelTransform::Tag(),
					CBColor::Tag(),
					CBMaterial::Tag(),
					CBLightGroup::Tag(),
					CBTexConfig::Tag(),
				},
				{ 
					"Texture0" ,
				},
				1, Model::GetPipelineSetting(),
				Pipeline::BlendState::Alpha, 2
			);

		pPipelineMan_->Insert("ModelDefault", newPipeline);
	}

	// ModelSingleColor
	{
		ShaderSet shader;

		shader.LoadShader("ModelVS.hlsl", ShaderSet::ShaderType::eVertex);
		shader.LoadShader("SingleColorPS.hlsl", ShaderSet::ShaderType::ePixel);

		Pipeline* newPipeline =
			Pipeline::Create(
				shader,
				{
					CBModelTransform::Tag(),
					CBColor::Tag(),
					CBMaterial::Tag(),
					CBLightGroup::Tag(),
					CBTexConfig::Tag(),
				},
				{
					"Texture0",
				},
				1, Model::GetPipelineSetting(),
				Pipeline::BlendState::Alpha, 2
				);

		pPipelineMan_->Insert("ModelSingleColor", newPipeline);
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
					CBModelTransform::Tag(),
					CBColor::Tag(),
					CBMaterial::Tag(),
					CBLightGroup::Tag(),
					CBTexConfig::Tag(),
				},
				{
					"Texture0",
				},
				1, Model::GetPipelineSetting(),
				Pipeline::BlendState::Alpha, 2
			);

		pPipelineMan_->Insert("ModelPhong", newPipeline);
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
					CBModelTransform::Tag(),
					CBColor::Tag(),
					CBMaterial::Tag(),
					CBLightGroup::Tag(),
					CBTexConfig::Tag(),
				},
				{
					"Texture0",
				},
				1, Model::GetPipelineSetting(),
				Pipeline::BlendState::Alpha, 2
			);

		pPipelineMan_->Insert("ModelToon", newPipeline);
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
					CBSprite2DTransform::Tag(),
					CBColor::Tag(),
					CBTexConfig::Tag(),
				},
				{
					"Texture0",
				},
				1, Sprite2D::GetPipelineSetting(),
				Pipeline::BlendState::Alpha, 1
			);

		pPipelineMan_->Insert("Sprite2DDefault", newPipeline);
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
					CBSprite3DTransform::Tag(),
					CBColor::Tag(),
					CBTexConfig::Tag(),
				},
				{
					"Texture0",
				},
				1, Sprite3D::GetPipelineSetting(),
				Pipeline::BlendState::Alpha, 2
			);

		pPipelineMan_->Insert("Sprite3DDefault", newPipeline);
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
					CBPostEffectTransform::Tag(),
					CBColor::Tag(),
					CBTexConfig::Tag(),
				},
				{
					"Texture0",
				},
				1, PostEffect::GetPipelineSetting(),
				Pipeline::BlendState::Alpha, 1
			);

		pPipelineMan_->Insert("PostEffectDefault", newPipeline);
	}


	// �`�揇��ݒ�
	pPipelineMan_->SetDrawOrder(
		{
			"ModelDefault", 
			"ModelSingleColor", 
			"ModelPhong", 
			"ModelToon", 
			
			"Sprite3DDefault", 
			
			"Sprite2DDefault", 
			
			"PostEffectDefault", 
		}
	);
}

void MyGame::InitializeParticles()
{
	DustParticle::StaticInitialize();

	DebriParticle::StaticInitialize();
}

void MyGame::InitializeTransition()
{
	BlackoutTransition::LoadResource();
	sceneMan_->InsertTransition("BLACKOUT", new BlackoutTransition());

	WindBlocks::LoadResource();
	sceneMan_->InsertTransition("WIND", new WindBlocks());

	WaveTransition::LoadResource();
	sceneMan_->InsertTransition("WAVE", new WaveTransition(false));
	sceneMan_->InsertTransition("WAVE_REV", new WaveTransition(true));
}

void MyGame::LoadMapData()
{
	MapChipManager::GetInstance()->Load("title.csv");
	MapChipManager::GetInstance()->Load("stage1.csv");
	MapChipManager::GetInstance()->Load("stage2.csv");
	MapChipManager::GetInstance()->Load("stage3.csv");
	MapChipManager::GetInstance()->Load("stage4.csv");
	MapChipManager::GetInstance()->Load("stage5.csv");
	MapChipManager::GetInstance()->Load("stage6.csv");
	MapChipManager::GetInstance()->Load("stage7.csv");
	MapChipManager::GetInstance()->Load("stage8.csv");
	MapChipManager::GetInstance()->Load("stage9.csv");
	MapChipManager::GetInstance()->Load("stage10.csv");

	StageManager::GetInstance()->Initialize();
}

void MyGame::LoadDrawer()
{	
	UILetterBox::LoadResource();

	UIDigit::LoadResource();

	UIManager::LoadResource();

	PauseManager::LoadResource();

	DefaultDrawer::LoadResource();

	PlayerDrawer::LoadResource();

	HorseDrawer::LoadResource();

	SlimeDrawer::LoadResource();

	SlashAttackDrawer::LoadResource();

	SnortAttackDrawer::LoadResource();

	BlockDrawer::LoadResource();

	GoalDrawer::LoadResource();

	SkydomeDrawer::LoadResource();

	CloudDrawer::LoadResource();
	
	AxisDrawer::LoadResource();

	CollisionDrawer::LoadResource();
	
	TitleDrawer::LoadResource();

	SelectDrawer::LoadResource();
	
	EarthDrawer::LoadResource();

	StageDrawer::LoadResource();

	CardDrawer::LoadResource();
}

