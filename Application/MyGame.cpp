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

#include "DustParticle.h"
#include "DebriParticle.h"

#include "UILetterBox.h"
#include "UIDigit.h"

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

#include "UIManager.h"
#include "PauseManager.h"

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
	// 基底クラス初期化処理
	if (YFramework::Initialize() == false) { return false; }

	InitializePipelines();

	InitializeParticles();

	LoadMapData();

	LoadDrawer();

	UILetterBox::StaticInitialize();
	
	UIDigit::StaticInitialize();

	StageManager::GetInstance()->Initialize();
	

	// シーンファクトリー設定
	sceneExe_->SetFactory(new YGameSceneFactory(), new YGameTransitionFactory());

	// シーンエグゼクティブ初期化
	sceneExe_->Initialize(YGameSceneFactory::Title_, YGameTransitionFactory::Blackout_);

	return true;
}

void MyGame::Finalize()
{
	// 基底クラス終了処理
	YFramework::Finalize();
}

void MyGame::Update()
{
	// 基底クラス更新処理
	YFramework::Update();

	// ------------------- 終了処理 ------------------- //
	// ------------------------------------------------ //
}

void MyGame::Draw()
{
	// デスクリプターヒープセット
	descHeap_.SetDrawCommand();

	// シーン描画
	sceneExe_->Draw();

	// パーティクル描画
	pParticleMan_->Draw();

	// 描画準備
	dx_.PreDraw(ClearColor);

	// スクリーン設定セット
	screenDesc_.SetDrawCommand();

	// パイプライン描画
	pPipelineMan_->Draw();

//#ifdef _DEBUG

	// imgui描画
	imguiMan_.Draw();

//#endif // DEBUG

	// 描画後処理
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


	// 描画順を設定
	pPipelineMan_->SetDrawOrder(
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

void MyGame::InitializeParticles()
{
	DustParticle::StaticInitialize();

	DebriParticle::StaticInitialize();
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
}

void MyGame::LoadDrawer()
{
	DefaultDrawer::StaticInitialize();

	PlayerDrawer::StaticInitialize();

	HorseDrawer::StaticInitialize();

	SlimeDrawer::StaticInitialize();

	SlashAttackDrawer::StaticInitialize();

	SnortAttackDrawer::StaticInitialize();

	BlockDrawer::StaticInitialize();

	GoalDrawer::StaticInitialize();

	SkydomeDrawer::StaticInitialize();

	CloudDrawer::StaticInitialize();
	
	AxisDrawer::StaticInitialize();

	CollisionDrawer::StaticInitialize();

	PauseManager::StaticInitialize();

	// UI
	UIManager::Load();
}

