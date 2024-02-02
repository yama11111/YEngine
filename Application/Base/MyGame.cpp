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
#include "CBCircleShadow.h"
#include "CBShadowGroup.h"
#include "CBTexConfig.h"
#include "CBTime.h"
#include "CBOutline.h"
#include "CBDiscardColor.h"

#include "DustParticle.h"
#include "DebriParticle.h"
#include "WaveParticle.h"
#include "RecoveryParticle.h"
#include "DamageParticle.h"

#include "BlackoutTransition.h"
#include "WindBlocks.h"
#include "WaveTransition.h"

#include "StageManager.h"

#include "ResourceLoader.h"

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

	ResourceLoader::Load();

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

void MyGame::UpdateContent()
{
	YFramework::UpdateContent();

	ResourceLoader::RenderDebug();
}

void MyGame::Draw()
{
	// デスクリプターヒープ設定
	descHeap_.SetDrawCommand();

	// 描画を積む
	sceneMan_->Draw();

	// ----- 描画処理 ----- //
	
	dx_.PreDraw(ClearColor);

	screenDesc_.SetDrawCommand();

	pPipelineMan_->Draw();

#ifdef _DEBUG

	// デバッグテキスト描画
	imguiMan_.Draw();

#endif // DEBUG

	dx_.PostDraw();
	
	// -------------------- //
}

void MyGame::InitializePipelines()
{
	pPipelineMan_->Clear();

#pragma region Model

	// ModelDefault
	{
		ShaderSet shader;

		shader.LoadShader("Model/ModelVS.hlsl", ShaderSet::ShaderType::eVertex);
		shader.LoadShader("Model/ModelPS.hlsl", ShaderSet::ShaderType::ePixel);

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
				Pipeline::BlendState::Alpha, 1
				);

		pPipelineMan_->Insert("ModelDefault", newPipeline);
	}

	// ModelOutline
	{
		ShaderSet shader;

		shader.LoadShader("Model/OutlineVS.hlsl", ShaderSet::ShaderType::eVertex);
		shader.LoadShader("Model/OutlinePS.hlsl", ShaderSet::ShaderType::ePixel);

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
				Pipeline::BlendState::Alpha, 1
				);

		pPipelineMan_->Insert("ModelOutline", newPipeline);
	}

	// ModelSingleColor
	{
		ShaderSet shader;

		shader.LoadShader("Model/SingleColorVS.hlsl", ShaderSet::ShaderType::eVertex);
		shader.LoadShader("Model/SingleColorPS.hlsl", ShaderSet::ShaderType::ePixel);

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
				Pipeline::BlendState::Alpha, 1
				);

		pPipelineMan_->Insert("ModelSingleColor", newPipeline);
	}

	// ModelPhong
	{
		ShaderSet shader;

		shader.LoadShader("Model/PhongVS.hlsl", ShaderSet::ShaderType::eVertex);
		shader.LoadShader("Model/PhongPS.hlsl", ShaderSet::ShaderType::ePixel);

		Pipeline* newPipeline =
			Pipeline::Create(
				shader,
				{
					CBModelTransform::Tag(),
					CBColor::Tag(),
					CBMaterial::Tag(),
					CBTexConfig::Tag(),
				},
				{
					"Texture0",
				},
				1, Model::GetPipelineSetting(),
				Pipeline::BlendState::Alpha, 1
				);

		pPipelineMan_->Insert("ModelPhong", newPipeline);
	}

	// ModelToon
	{
		ShaderSet shader;

		shader.LoadShader("Model/ToonVS.hlsl", ShaderSet::ShaderType::eVertex);
		shader.LoadShader("Model/ToonPS.hlsl", ShaderSet::ShaderType::ePixel);

		Pipeline* newPipeline =
			Pipeline::Create(
				shader,
				{
					CBModelTransform::Tag(),
					CBColor::Tag(),
					CBMaterial::Tag(),
					CBTexConfig::Tag(),
					CBShadowGroup::Tag(),
				},
				{
					"Texture0",
				},
				1, Model::GetPipelineSetting(),
				Pipeline::BlendState::Alpha, 1
				);

		pPipelineMan_->Insert("ModelToon", newPipeline);
	}

#pragma endregion

#pragma region Sprite2D

	// Sprite2DDefault
	{
		ShaderSet shader;

		shader.LoadShader("Sprite2D/Sprite2DVS.hlsl", ShaderSet::ShaderType::eVertex);
		shader.LoadShader("Sprite2D/Sprite2DPS.hlsl", ShaderSet::ShaderType::ePixel);

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

#pragma endregion

#pragma region Sprite3D

	// Sprite3DDefault
	{
		ShaderSet shader;

		shader.LoadShader("Sprite3D/Sprite3DVS.hlsl", ShaderSet::ShaderType::eVertex);
		shader.LoadShader("Sprite3D/Sprite3DGS.hlsl", ShaderSet::ShaderType::eGeometry);
		shader.LoadShader("Sprite3D/Sprite3DPS.hlsl", ShaderSet::ShaderType::ePixel);

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
				Pipeline::BlendState::Alpha, 1
				);

		pPipelineMan_->Insert("Sprite3DDefault", newPipeline);
	}

	// Sprite3DUI
	{
		ShaderSet shader;

		shader.LoadShader("Sprite3D/Sprite3DVS.hlsl", ShaderSet::ShaderType::eVertex);
		shader.LoadShader("Sprite3D/Sprite3DGS.hlsl", ShaderSet::ShaderType::eGeometry);
		shader.LoadShader("Sprite3D/Sprite3DPS.hlsl", ShaderSet::ShaderType::ePixel);

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
				Pipeline::BlendState::Alpha, 1
				);

		pPipelineMan_->Insert("Sprite3DUI", newPipeline);
	}

#pragma endregion

#pragma region PostEffect

	// PostEffectDefault
	{
		ShaderSet shader;

		shader.LoadShader("PostEffect/PostEffectVS.hlsl", ShaderSet::ShaderType::eVertex);
		shader.LoadShader("PostEffect/PostEffectPS.hlsl", ShaderSet::ShaderType::ePixel);

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

	// World_Fever
	{
		ShaderSet shader;

		shader.LoadShader("PostEffect/DiscardColorVS.hlsl", ShaderSet::ShaderType::eVertex);
		shader.LoadShader("PostEffect/DiscardColorPS.hlsl", ShaderSet::ShaderType::ePixel);

		Pipeline* newPipeline =
			Pipeline::Create(
				shader,
				{
					CBPostEffectTransform::Tag(),
					CBColor::Tag(),
					CBTexConfig::Tag(),
					CBDiscardColor::Tag(),
				},
				{
					"Texture0",
				},
				1, PostEffect::GetPipelineSetting(),
				Pipeline::BlendState::Alpha, 1
				);

		pPipelineMan_->Insert("World_Fever", newPipeline);
	}

	// World_0
	{
		ShaderSet shader;

		shader.LoadShader("PostEffect/DiscardColorVS.hlsl", ShaderSet::ShaderType::eVertex);
		shader.LoadShader("PostEffect/DiscardColorPS.hlsl", ShaderSet::ShaderType::ePixel);

		Pipeline* newPipeline =
			Pipeline::Create(
				shader,
				{
					CBPostEffectTransform::Tag(),
					CBColor::Tag(),
					CBTexConfig::Tag(),
					CBDiscardColor::Tag(),
				},
				{
					"Texture0",
				},
				1, PostEffect::GetPipelineSetting(),
				Pipeline::BlendState::Alpha, 1
				);

		pPipelineMan_->Insert("World_0", newPipeline);
	}

#pragma endregion

	// 描画順序設定
	pPipelineMan_->SetDrawOrder(
		{
			"PostEffectDefault",
			"World_Fever",
			"World_0",
			
			"ModelOutline",
			"ModelSingleColor",
			"ModelPhong",
			"ModelToon",
			
			"Sprite3DDefault",
			"Sprite3DUI",

			"Sprite2DDefault",
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
	sceneMan_->InsertTransition("BLACKOUT", new BlackoutTransition());

	sceneMan_->InsertTransition("WIND", new WindBlocks());

	sceneMan_->InsertTransition("WAVE", new WaveTransition(false));
	sceneMan_->InsertTransition("WAVE_REV", new WaveTransition(true));
}

void MyGame::LoadMapData()
{
	StageManager::GetInstance()->Load();
	StageManager::GetInstance()->Initialize();
}

