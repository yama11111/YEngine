#include "YFramework.h"
#include "MathUtillity.h"
#include "Def.h"
#include <cassert>

#pragma region ���O��Ԑ錾

using YBase::YFramework;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YScene;
using namespace YGame;

#pragma endregion

bool YFramework::Initialize()
{
#pragma region Base

	// Windows ������
	window_.Create(WindowTitle, WinSize.x_, WinSize.y_);

	// DirectX ������
	YDirectX::SetFPS(FixFPS);
	if (!dx_.Initialize(window_.HandleWindow(), WinSize)) { return false; }

	// Input ������
	inputMan_ = InputManager::GetInstance();
	inputMan_->Create(window_.HandleWindowInstance(), window_.PointerHandleWindow());

	// ����������
	Srand();

	// �Q�[�����[��������
	worldRuler_.Initailze();
	WorldRuleAdopter::StaticInitialize(&worldRuler_);

#pragma endregion

#pragma region Pipeline

	// �f�o�C�X�|�C���^
	ID3D12Device* pDev = dx_.Device();
	// �R�}���h���X�g�|�C���^
	ID3D12GraphicsCommandList* pCmdList = dx_.CommandList();

	// �X�N���[���ݒ�
	ScreenDesc::StaticInitialize(pCmdList);
	screenDesc_.Initialize({ 0,0 }, WinSize);

	// GPUResource �ÓI������
	GPUResource::StaticInitialize(pDev);

	// �f�X�N���v�^�[�q�[�v (SRV, UAV, CBV)
	DescriptorHeap::StaticInitialize({ pDev, pCmdList });
	descHeap_.Initialize();

	// �萔�o�b�t�@�ÓI������
	ConstBufferCommon::StaticInitialize({ pCmdList, &descHeap_ });

	// �e�N�X�`���}�l�[�W���[�ÓI������
	TextureManagerCommon::StaticInitialize({ pDev, pCmdList, &descHeap_ });

	// �p�C�v���C���ÓI������
	PipelineSet::StaticInitialize(pDev, pCmdList);

	// ���_
	Vertices<Sprite2DCommon::VData>	::StaticInitialize(pCmdList);
	Vertices<Sprite3DCommon::VData>	::StaticInitialize(pCmdList);
	Vertices<ModelCommon::VData>	::StaticInitialize(pCmdList);

	// �R�����N���X�ÓI������
	Sprite2DCommon	::StaticInitialize();
	Sprite3DCommon	::StaticInitialize();
	ModelCommon		::StaticInitialize();

	// �I�u�W�F�N�g�ÓI������
	Sprite2DObjectCommon::StaticInitialize();
	Sprite3DObjectCommon::StaticInitialize();
	ModelObjectCommon	::StaticInitialize();

	// �}�e���A���ÓI������
	Material::StaticInitialize();

#pragma endregion

#pragma region Game

	// imgui������
	imguiMan_.Initialize({ window_.PointerHandleWindow(), pDev, dx_.BackBufferCount(), pCmdList });

	// �I�[�f�B�I������
	AudioManager::GetInstance()->Initialize();

	// �V�[��������
	BaseScene::StaticInitialize(&worldRuler_);
	sceneMan_ = SceneManager::GetInstance();

#pragma endregion

	isEnd_ = false;

	return true;
}

void YFramework::Finalize()
{
	// imgui���N���[��
	imguiMan_.Finalize();

	// �E�B���h�E�N���X��o�^����
	window_.FinalProcess();

	// �V�[���I������
	sceneMan_->Finalize();
}

void YFramework::Update()
{
	// input�X�V
	inputMan_->Update();

	// imgui��t�J�n
	imguiMan_.Begin();

	// �Q�[�����[���X�V����
	worldRuler_.Update();

	// �V�[���X�V����
	sceneMan_->Update();

	// imgui��t�I��
	imguiMan_.End();

	// ------------------- �I������ ------------------- //
	// �~�{�^���ŏI�����b�Z�[�W
	if (window_.CheckMessage()) { isEnd_ = true; }
	// ESC�L�[�ŏI��
	if (inputMan_->keys_->IsTrigger(DIK_ESCAPE)) { isEnd_ = true; }
	// ------------------------------------------------ //
}

void YFramework::Run()
{
	// ������
	bool isSuccess = Initialize();

	// �Q�[�����[�v
	while (isSuccess)
	{
		// �X�V
		Update();

		// �`��
		Draw();

		// �I��
		if (IsEnd()) { break; }
	}

	// �I������
	Finalize();
}
