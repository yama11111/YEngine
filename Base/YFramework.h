#pragma once
#include "SceneManager.h"
#include "YWindowsApp.h"
#include "YDirectX.h"
#include "ScreenDesc.h"
#include "ImGuiManager.h"
#include <memory>

namespace YBase
{
	class YFramework
	{
	protected:
		// WindowsAPI
		YWindowsApp window_;
		// DirectX12
		YDX::YDirectX dx_;
		// input�}�l�[�W���[
		YInput::InputManager* inputMan_ = nullptr;
		// �X�N���[���ݒ�
		YDX::ScreenDesc screenDesc_;
		// �f�X�N���v�^�[�q�[�v (SRV, UAV, CBV)
		YDX::DescriptorHeap descHeap_;
		// �Q�[�����[��
		YGame::WorldRuler worldRuler_;
		// imgui�}�l�[�W���[
		ImGuiManager imguiMan_;
		// �V�[���}�l�[�W���[
		YScene::SceneManager* sceneMan_ = nullptr;
		// �I���t���O
		bool isEnd_ = false;
	public:
		// ������
		virtual bool Initialize();
		// �I������
		virtual void Finalize();
		// �X�V
		virtual void Update();
		// �`��
		virtual void Draw() = 0;
		// �I���t���O�擾
		virtual bool IsEnd() { return isEnd_; }
	public:
		// ���s
		void Run();
	public:
		YFramework() = default;
		virtual ~YFramework() = default;
	};
}
