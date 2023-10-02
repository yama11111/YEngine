#pragma once
#include "SceneManager.h"
#include "YWindowsApp.h"
#include "YDirectX.h"
#include "ScreenDesc.h"
#include "PipelineManager.h"
#include "ParticleManager.h"
#include "ImGuiManager.h"
#include <memory>

namespace YBase
{
	class YFramework
	{
	
	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <returns>����������</returns>
		virtual bool Initialize();

		/// <summary>
		/// �I������
		/// </summary>
		virtual void Finalize();

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void Update();
		
		/// <summary>
		/// �`��
		/// </summary>
		virtual void Draw() = 0;

		/// <summary>
		/// ���s
		/// </summary>
		void Run();
	
	public:
		
		YFramework() = default;
		
		virtual ~YFramework() = default;

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
		
		// imgui�}�l�[�W���[
		ImGuiManager imguiMan_;

		// �p�C�v���C���}�l�[�W���[
		YGame::PipelineManager* pPipelineMan_ = nullptr;
		
		// �p�[�e�B�N���}�l�[�W���[
		YGame::ParticleManager* pParticleMan_ = nullptr;
		
		// �V�[���}�l�[�W���[
		YGame::SceneManager* sceneMan_ = nullptr;
		
		// �I���t���O
		bool isEnd_ = false;
	
	};
}
