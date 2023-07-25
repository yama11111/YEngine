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

#pragma region 名前空間宣言
using YBase::MyGame;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YScene;
using namespace YGame;
#pragma endregion 

bool MyGame::Initialize()
{
	// 基底クラス初期化処理
	if (YFramework::Initialize() == false) { return false; }

	// パイプライン初期化
	pipelineMan_ = PipelineManager::GetInstance();
	InitializePipelines();

	// ステージ
	MapChipManager::GetInstance()->Load("demo.csv");

	// シーンファクトリー設定
	sceneExe_->SetFactory(new YGameSceneFactory(), new YGameTransitionFactory());

	// シーンエグゼクティブ初期化
	sceneExe_->Initialize(YGameSceneFactory::Task_, YGameTransitionFactory::Blackout_);

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

	// 描画準備
	dx_.PreDraw(ClearColor);

	// スクリーン設定セット
	screenDesc_.SetDrawCommand();

	// ゲームシーン描画
	pipelineMan_->Draw();

#ifdef _DEBUG

	// imgui描画
	imguiMan_.Draw();

#endif // DEBUG

	// 描画後処理
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
					CBModelTransform::KeyName(),
					CBColor::KeyName(),
					CBMaterial::KeyName(),
					CBLightGroup::KeyName(),
					CBTexConfig::KeyName(),
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
					CBModelTransform::KeyName(),
					CBColor::KeyName(),
					CBMaterial::KeyName(),
					CBLightGroup::KeyName(),
					CBTexConfig::KeyName(),
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
					CBModelTransform::KeyName(),
					CBColor::KeyName(),
					CBMaterial::KeyName(),
					CBLightGroup::KeyName(),
					CBTexConfig::KeyName(),
				},
				{
					"Texture",
				},
				1, Model::GetPipelineSetting(),
				Pipeline::BlendState::Alpha, 2
			);

		pipelineMan_->Insert("ModelToon", newPipeline);
	}

	// ModelDissolve
	{
		ShaderSet shader;

		shader.LoadShader("DissolveVS.hlsl", ShaderSet::ShaderType::eVertex);
		shader.LoadShader("DissolvePS.hlsl", ShaderSet::ShaderType::ePixel);

		PipelineSetting setting = Model::GetPipelineSetting();
		setting.cullMode = D3D12_CULL_MODE_BACK;

		Pipeline* newPipelineFront =
			Pipeline::Create(
				shader,
				{
					CBModelTransform::KeyName(),
					CBTime::KeyName(),
					CBColor::KeyName(),
					CBTexConfig::KeyName(),
				},
				{
					"Texture",
					"Mask",
				},
				2, setting,
				Pipeline::BlendState::Alpha, 2
				);
		
		pipelineMan_->Insert("ModelDissolveFront", newPipelineFront);
		
		setting.cullMode = D3D12_CULL_MODE_FRONT;

		Pipeline* newPipelineBack =
			Pipeline::Create(
				shader,
				{
					CBModelTransform::KeyName(),
					CBTime::KeyName(),
					CBColor::KeyName(),
					CBTexConfig::KeyName(),
				},
				{
					"Texture",
					"Mask",
				},
				2, setting,
				Pipeline::BlendState::Alpha, 2
				);

		pipelineMan_->Insert("ModelDissolveBack", newPipelineBack);

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
					CBSprite2DTransform::KeyName(),
					CBColor::KeyName(),
					CBTexConfig::KeyName(),
				},
				{
					"Texture0",
				},
				1, Sprite2D::GetPipelineSetting(),
				Pipeline::BlendState::Alpha, 1
			);

		pipelineMan_->Insert("Sprite2DDefault", newPipeline);
	}


	// Sprite2DTextureBlend
	{
		ShaderSet shader;

		shader.LoadShader("Sprite2DVS.hlsl", ShaderSet::ShaderType::eVertex);
		shader.LoadShader("TextureBlendPS.hlsl", ShaderSet::ShaderType::ePixel);

		Pipeline* newPipeline =
			Pipeline::Create(
				shader,
				{
					CBSprite2DTransform::KeyName(),
					CBColor::KeyName(),
					CBTexConfig::KeyName(),
				},
				{
					"Texture0",
					"Texture1",
					"Mask",
				},
				3, Sprite2D::GetPipelineSetting(),
				Pipeline::BlendState::Alpha, 1
				);

		pipelineMan_->Insert("Sprite2DTextureBlend", newPipeline);
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
					CBSprite3DTransform::KeyName(),
					CBColor::KeyName(),
					CBTexConfig::KeyName(),
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
					CBPostEffectTransform::KeyName(),
					CBColor::KeyName(),
					CBTexConfig::KeyName(),
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

	// PostEffectColorInversion
	{
		ShaderSet shader;

		shader.LoadShader("PostEffectVS.hlsl", ShaderSet::ShaderType::eVertex);
		shader.LoadShader("ColorInversionPS.hlsl", ShaderSet::ShaderType::ePixel);

		Pipeline* newPipeline =
			Pipeline::Create(
				shader,
				{
					CBPostEffectTransform::KeyName(),
					CBColor::KeyName(),
					CBTexConfig::KeyName(),
				},
				{
					"Texture0",
					"Texture1",
				},
				2, PostEffect::GetPipelineSetting(),
				Pipeline::BlendState::Alpha, 1
			);

		pipelineMan_->Insert("PostEffectColorInversion", newPipeline);
	}

	// PostEffectGaussianBlur
	{
		ShaderSet shader;

		shader.LoadShader("PostEffectVS.hlsl", ShaderSet::ShaderType::eVertex);
		shader.LoadShader("GaussianBlurPS.hlsl", ShaderSet::ShaderType::ePixel);

		Pipeline* newPipeline =
			Pipeline::Create(
				shader,
				{
					CBPostEffectTransform::KeyName(),
					CBColor::KeyName(),
					CBTexConfig::KeyName(),
				},
				{
					"Texture0",
					"Texture1",
				},
				2, PostEffect::GetPipelineSetting(),
				Pipeline::BlendState::Alpha, 1
			);

		pipelineMan_->Insert("PostEffectGaussianBlur", newPipeline);
	}

	// PostEffectUVShiftBlur
	{
		ShaderSet shader;

		shader.LoadShader("PostEffectVS.hlsl", ShaderSet::ShaderType::eVertex);
		shader.LoadShader("UVShiftBlurPS.hlsl", ShaderSet::ShaderType::ePixel);

		Pipeline* newPipeline =
			Pipeline::Create(
				shader,
				{
					CBPostEffectTransform::KeyName(),
					CBColor::KeyName(),
					CBTexConfig::KeyName(),
				},
				{
					"Texture0",
					"Texture1",
				},
				2, PostEffect::GetPipelineSetting(),
				Pipeline::BlendState::Alpha, 1
			);

		pipelineMan_->Insert("PostEffectUVShiftBlur", newPipeline);
	}

	// PostEffectBloom
	{
		ShaderSet shader;

		shader.LoadShader("PostEffectVS.hlsl", ShaderSet::ShaderType::eVertex);
		shader.LoadShader("BloomPS.hlsl", ShaderSet::ShaderType::ePixel);

		Pipeline* newPipeline =
			Pipeline::Create(
				shader,
				{
					CBPostEffectTransform::KeyName(),
					CBColor::KeyName(),
					CBTexConfig::KeyName(),
				},
				{
					"Texture0",
					"Texture1",
				},
				2, PostEffect::GetPipelineSetting(),
				Pipeline::BlendState::Alpha, 1
			);

		pipelineMan_->Insert("PostEffectBloom", newPipeline);
	}


	// 描画順を設定
	pipelineMan_->SetDrawOrder(
		{
			"ModelDefault", 
			"ModelPhong", 
			"ModelToon", 
			
			"ModelDissolveBack",
			"ModelDissolveFront",
			
			"Sprite3DDefault", 
			
			"Sprite2DDefault", 
			"Sprite2DTextureBlend", 
			
			"PostEffectDefault", 
			"PostEffectColorInversion", 
			"PostEffectGaussianBlur", 
			"PostEffectUVShiftBlur", 
			"PostEffectBloom", 
		}
	);
}

void MyGame::DrawGameScene()
{	
	pipelineMan_->Draw();
}
