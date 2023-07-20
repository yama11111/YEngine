#include "YFramework.h"
#include "MathUtil.h"
#include "Def.h"
#include <cassert>

#include "ConstBufferCommon.h"
#include "PipelineManager.h"

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


	// �f�o�C�X�|�C���^
	ID3D12Device* pDev = dx_.DevicePtr();
	// �R�}���h���X�g�|�C���^
	ID3D12GraphicsCommandList* pCmdList = dx_.CommandListPtr();

	// �X�N���[���ݒ�
	ScreenDesc::StaticInitialize(pCmdList);
	screenDesc_.Initialize({ 0,0 }, WinSize);

	// GPUResource �ÓI������
	GPUResource::StaticInitialize(pDev);

	// �f�X�N���v�^�[�q�[�v (SRV, UAV, CBV)
	DescriptorHeap::StaticInitialize(pDev, pCmdList);
	descHeap_.Initialize();

	// ���_
	VertexCommon::StaticInitialize(pCmdList);

	// �萔�o�b�t�@�ÓI������
	ConstBufferCommon::StaticInitialize(pCmdList, &descHeap_);

	// �e�N�X�`���ÓI������
	Texture::Common::StaticInitialize(pDev, pCmdList, &descHeap_);
	Texture::AllClear();

	// �|�X�g�G�t�F�N�g
	PostEffect::StaticInitialize(pDev, pCmdList);

	// �p�C�v���C���ÓI������
	Pipeline::StaticInitialize(pDev, pCmdList);

	// FBXLoader�ǂݍ���
	Model::FbxLoader::StaticInitialize();

	// imgui������
	imguiMan_.Initialize({ window_.HandleWindow(), pDev, pCmdList, &descHeap_, dx_.BackBufferCount() });

	// �I�[�f�B�I������
	Audio::Base::StaticInitialize();
	Audio::AllClear();

	// �V�[���J�ڏ�����
	TransitionManager::StaticInitialize();

	// �V�[��������
	BaseScene::StaticInitialize();
	SceneManager::GetInstance()->SetDescriptorHeapPointer(&descHeap_);
	
	// �V�[���G�O�[�N�e�B�u
	sceneExe_ = SceneExecutive::GetInstance();


	isEnd_ = false;

	return true;
}

void YFramework::Finalize()
{
	// FBXLoader�J��
	Model::FbxLoader::StaticFinalize();

	// imgui���N���[��
	imguiMan_.Finalize();

	// �E�B���h�E�N���X��o�^����
	window_.FinalProcess();

	// �V�[���I������
	SceneManager::GetInstance()->Finalize();
	
	// �V�[���J�ڏI������
	TransitionManager::GetInstance()->Finalize();

	// �p�C�v���C���N���A
	PipelineManager::GetInstance()->Clear();
	
	// ���\�[�X�S�N���A
	PostEffect::AllClear();
	Model::AllClear();
	Sprite2D::AllClear();
	Sprite3D::AllClear();
	Texture::AllClear();
	Audio::AllClear();
}

void YFramework::Update()
{
	// imgui��t�J�n
	imguiMan_.Begin();
	
	// input�X�V
	inputMan_->Update();

	// �V�[���X�V����
	sceneExe_->Update();

	// �f�X�N���v�^�J�E���g�\��
	//descHeap_.ShowCount();

	// imgui��t�I��
	imguiMan_.End();

	// ------------------- �I������ ------------------- //
	
	// �~�{�^���ŏI�����b�Z�[�W
	if (window_.CheckMessage()) { isEnd_ = true; }

	// �V�[���}�l�[�W���[�I���t���O
	if (SceneManager::GetInstance()->IsEnd()) { isEnd_ = true; }

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
