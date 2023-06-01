#pragma once
#include "SceneExecutive.h"
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
		
		// �V�[���G�O�[�N�e�B�u
		YScene::SceneExecutive* sceneExe_ = nullptr;
		
		// �I���t���O
		bool isEnd_ = false;
	
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
		/// �I���t���O�擾
		/// </summary>
		/// <returns>�I���t���O</returns>
		bool IsEnd() { return isEnd_; }

		/// <summary>
		/// �I���t���O�ݒ�
		/// </summary>
		/// <param name="isEnd"> : �I���t���O</param>
		void SetEnd(const bool isEnd) { isEnd_ = isEnd; }
	
	public:

		/// <summary>
		/// ���s
		/// </summary>
		void Run();
	
	public:
		
		YFramework() = default;
		
		virtual ~YFramework() = default;
	
	};
}
