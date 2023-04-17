#pragma once
#include "ISceneFactory.h"
#include "ITransitionFactory.h"

namespace YScene
{
	class SceneManager
	{
	private:
		
		// �V�[��
		std::unique_ptr<BaseScene> scene_;
		
		// ���̃V�[��
		BaseScene* nextScene_ = nullptr;
		
		// �f�X�N���v�^�q�[�v�|�C���^
		YDX::DescriptorHeap* pDescHeap_ = nullptr;

		// �V�[���t�@�N�g���[
		std::unique_ptr<ISceneFactory> sceneFactory_;
		
		// �J�ڃt�@�N�g���[
		std::unique_ptr<ITransitionFactory> transitionFactory_;

		// �I���t���O
		bool isEnd_ = false;
	
	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="sceneName"> : �����V�[��</param>
		void Initialize(const std::string& sceneName);

		/// <summary>
		/// �I������
		/// </summary>
		void Finalize();

		/// <summary>
		/// �X�V
		/// </summary>
		void Update();

		/// <summary>
		/// �`��
		/// </summary>
		void Draw();
	
	public:

		/// <summary>
		/// ���V�[���\��
		/// </summary>
		/// <param name="sceneName"> : ���V�[���̖��O</param>
		/// <param name="transitionName"> : �J�ڂ̖��O</param>
		void Change(const std::string& sceneName, const std::string& transitionName);
		

		/// <summary>
		/// �V�[���t�@�N�g���[�ݒ�
		/// </summary>
		/// <param name="sceneFactory"> : �V�[���t�@�N�g���[</param>
		void SetSceneFactory(ISceneFactory* sceneFactory);

		/// <summary>
		/// �J�ڃt�@�N�g���[�ݒ�
		/// </summary>
		/// <param name="transitionFactory"> : �J�ڃt�@�N�g���[</param>
		void SetTransitionFactory(ITransitionFactory* transitionFactory);
	
		/// <summary>
		/// �f�X�N���v�^�q�[�v�|�C���^�ݒ�
		/// </summary>
		/// <param name="sceneFactory"> : �f�X�N���v�^�q�[�v�|�C���^</param>
		void SetDescriptorHeapPointer(YDX::DescriptorHeap* pDescHeap);

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
		
		// �V���O���g��
		static SceneManager* GetInstance();
	
	private:
		
		SceneManager() = default;
		
		~SceneManager() = default;
		
		SceneManager(const SceneManager&) = delete;
		
		const SceneManager& operator=(const SceneManager&) = delete;
	
	};
}
