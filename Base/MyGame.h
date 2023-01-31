#pragma once
#include "YFramework.h"
#include "YWindowsApp.h"
#include "YDirectX.h"
#include "ScreenDesc.h"
#include "InputManager.h"
#include "ImGuiContoroller.h"
#include "GameScene.h"
#include <memory>

namespace YBase
{
	class MyGame : public YFramework
	{
	private:
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
		// �e�N�X�`���}�l�[�W���[
		YGame::TextureManager texMan_;
		// audio�}�l�[�W���[
		YGame::AudioManager audioMan_;
		// imgui�}�l�[�W���[
		ImGuiContoroller imguiCon_;
		// �V�[��
		std::unique_ptr<YScene::BaseScene> scene_;
	public:
		// ������
		bool Initialize() override;
		// �I������
		void Finalize() override;
		// �X�V
		void Update() override;
		// �`��
		void Draw() override;
	};
}
