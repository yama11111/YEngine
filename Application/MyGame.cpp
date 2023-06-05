#include "MyGame.h"
#include "Def.h"
#include "YGameSceneFactory.h"
#include "YGameTransitionFactory.h"

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

	// �V�[���t�@�N�g���[�ݒ�
	sceneExe_->SetFactory(new YGameSceneFactory(), new YGameTransitionFactory());

	// �V�[���G�O�[�N�e�B�u������
	sceneExe_->Initialize(YGameSceneFactory::Play_, YGameTransitionFactory::Blackout_);

	postEffectObject_.reset(PostEffect::Object::Create({ {WinSize.x_ / 2.0f, WinSize.y_ / 2.0f, 0.0f}, {}, {1.0f,1.0f,1.0f} }));
	
	pPostEffect_ = PostEffect::Create({}, { Texture::CreateRender() });

	pPostEffect_->SetDrawCommand(postEffectObject_.get(), PostEffect::ShaderType::eGaussian);
	shaderSwitch_ = true;

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

	pPostEffect_->StartRender();

	
	// �Q�[���V�[���`��
	DrawGameScene();
	
	
	pPostEffect_->EndRender();

	if (Keys::GetInstance()->IsTrigger(DIK_SPACE))
	{
		if (shaderSwitch_)
		{
			pPostEffect_->SetDrawCommand(postEffectObject_.get());
			shaderSwitch_ = false;
		}
		else
		{
			pPostEffect_->SetDrawCommand(postEffectObject_.get(), PostEffect::ShaderType::eGaussian);
			shaderSwitch_ = true;
		}
	}

	// �`�揀��
	dx_.PreDraw(ClearColor);

	// �X�N���[���ݒ�Z�b�g
	screenDesc_.SetDrawCommand();
	
	// �|�X�g�G�t�F�N�g�`��
	PostEffect::Pipeline::StaticDraw();

	// �|�X�g�G�t�F�N�g�`��Z�b�g�N���A
	PostEffect::Pipeline::StaticClearDrawSet();

#ifdef _DEBUG

	// imgui�`��
	imguiMan_.Draw();

#endif // DEBUG

	// �`��㏈��
	dx_.PostDraw();
}

void MyGame::DrawGameScene()
{
	// �V�[���`��
	sceneExe_->Draw();

	// �`��ꏊ�̐�����
	for (size_t i = 0; i < DrawLocationNum; i++)
	{
		// �ϊ�
		DrawLocation location = static_cast<DrawLocation>(i);


		// ���f���`��
		Model::Pipeline::StaticDraw(location);

		// �X�v���C�g3D�`��
		Sprite3D::Pipeline::StaticDraw(location);

		// �X�v���C�g2D�`��
		Sprite2D::Pipeline::StaticDraw(location);


		// ���f���`��Z�b�g�N���A
		Model::Pipeline::StaticClearDrawSet(location);

		// �X�v���C�g3D�`��Z�b�g�N���A
		Sprite3D::Pipeline::StaticClearDrawSet(location);

		// �X�v���C�g2D�`��Z�b�g�N���A
		Sprite2D::Pipeline::StaticClearDrawSet(location);
	}
}