#include "MyGame.h"
#include "Def.h"
#include "YGameSceneFactory.h"

#include "GameObject.h"

#include "CBModelTransform.h"
#include "CBSprite2DTransform.h"
#include "CBSprite3DTransform.h"
#include "CBPostEffectTransform.h"
#include "CBColor.h"
#include "CBMaterial.h"
#include "CBLightGroup.h"
#include "CBTexConfig.h"
#include "CBTime.h"
#include "CBOutline.h"

#include "DustParticle.h"
#include "DebriParticle.h"
#include "WaveParticle.h"
#include "RecoveryParticle.h"
#include "DamageParticle.h"

#include "BlackoutTransition.h"
#include "WindBlocks.h"
#include "WaveTransition.h"

#include "StageManager.h"

#include "DefaultDrawer.h"
#include "PlayerDrawer.h"
#include "HorseDrawer.h"
#include "SlimeDrawer.h"
#include "CoinDrawer.h"
#include "LifeDrawer.h"
#include "MagnetDrawer.h"
#include "NeedleAttackDrawer.h"
#include "BlockDrawer.h"
#include "GoalDrawer.h"
#include "CloudDrawer.h"
#include "SkydomeDrawer.h"
#include "AxisDrawer.h"
#include "CollisionDrawer.h"

#include "TitleDrawer.h"
#include "SelectDrawer.h"
#include "StageDrawer.h"
#include "StageStatusDrawer.h"
#include "BeginingDrawer.h"

#include "UIDrawer.h"
#include "ScoreDrawer.h"
#include "PauseDrawer.h"

#include "UILetterBox.h"
#include "UIDigit.h"

#pragma region 名前空間宣言
using YBase::MyGame;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;
using namespace YGame;
#pragma endregion 

bool MyGame::Initialize()
{
	if (YFramework::Initialize() == false) { return false; }

	LoadMapData();

	LoadDrawer();

	InitializePipelines();

	InitializeParticles();

	InitializeTransition();

	sceneMan_->SetSceneFactory(std::move(std::make_unique<YGameSceneFactory>()));

	//sceneMan_->Initialize(YGameSceneFactory::Title_);
	//sceneMan_->Initialize(YGameSceneFactory::Select_);
	sceneMan_->Initialize(YGameSceneFactory::Play_);

	return true;
}

void MyGame::Finalize()
{
	YFramework::Finalize();
}

void MyGame::Update()
{
	YFramework::Update();
}

void MyGame::Draw()
{
	// デスクリプターヒープ設定
	descHeap_.SetDrawCommand();

	// ----- 描画を積む ----- //
	
	sceneMan_->Draw();

	pParticleMan_->Draw();

	// ---------------------- //

	// ----- 描画処理 ----- //
	
	dx_.PreDraw(ClearColor);

	screenDesc_.SetDrawCommand();

	pPipelineMan_->Draw();

//#ifdef _DEBUG

	// デバッグテキスト描画
	imguiMan_.Draw();

//#endif // DEBUG

	dx_.PostDraw();
	
	// -------------------- //
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

	// ModelOutline
	{
		ShaderSet shader;

		shader.LoadShader("OutlineVS.hlsl", ShaderSet::ShaderType::eVertex);
		shader.LoadShader("OutlinePS.hlsl", ShaderSet::ShaderType::ePixel);

		PipelineSetting setting = Model::GetPipelineSetting();
		setting.cullMode = D3D12_CULL_MODE_FRONT;

		Pipeline* newPipeline =
			Pipeline::Create(
				shader,
				{
					CBModelTransform::Tag(),
					CBOutline::Tag(),
				},
				{
					"Texture0",
				},
				1, setting,
				Pipeline::BlendState::Alpha, 2
				);

		pPipelineMan_->Insert("ModelOutline", newPipeline);
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


	// 描画順序設定
	pPipelineMan_->SetDrawOrder(
		{
			"ModelDefault",
			"ModelOutline",
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
	
	WaveParticle::StaticInitialize();

	RecoveryParticle::StaticInitialize();
	
	DamageParticle::StaticInitialize();
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
	StageManager::GetInstance()->Load();
	StageManager::GetInstance()->Initialize();
}

void MyGame::LoadDrawer()
{
	// UI
	{
		UILetterBox::LoadResource();

		UIDigit::LoadResource();

		UIDrawer::LoadResource();

		PauseDrawer::LoadResource();
	}

	// Game
	{
		DefaultDrawer::LoadResource();

		PlayerDrawer::LoadResource();

		HorseDrawer::LoadResource();

		SlimeDrawer::LoadResource();

		NeedleAttackDrawer::LoadResource();

		CoinDrawer::LoadResource();
		
		LifeDrawer::LoadResource();
		
		MagnetDrawer::LoadResource();

		BlockDrawer::LoadResource();

		GoalDrawer::LoadResource();

		SkydomeDrawer::LoadResource();

		CloudDrawer::LoadResource();

		AxisDrawer::LoadResource();

		CollisionDrawer::LoadResource();
	}

	// Scene
	{
		TitleDrawer::LoadResource();

		StageDrawer::LoadResource();

		StageStatusDrawer::LoadResource();

		SelectDrawer::LoadResource();

		BeginingDrawer::LoadResource();
	}
}

