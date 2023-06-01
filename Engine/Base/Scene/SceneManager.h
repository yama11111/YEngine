#pragma once
#include "ISceneFactory.h"

namespace YScene
{
	class SceneManager
	{
	
	private:
		
		// �V�[��
		std::unique_ptr<BaseScene> scene_;

		// ���݃V�[����
		std::string sceneName_ = {};

		// �V�[���t�@�N�g���[
		static std::unique_ptr<ISceneFactory> sceneFactory_;

		// �f�X�N���v�^�q�[�v�|�C���^
		YDX::DescriptorHeap* pDescHeap_ = nullptr;

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
		/// <param name="sceneName"> : ���V�[����</param>
		void Change(const std::string& sceneName);
	
	public:

		/// <summary>
		/// �V�[���t�@�N�g���[�ݒ�
		/// </summary>
		/// <param name="sceneFactory"> : �V�[���t�@�N�g���[</param>
		static void SetSceneFactory(ISceneFactory* sceneFactory);
	
		/// <summary>
		/// �f�X�N���v�^�q�[�v�|�C���^�ݒ�
		/// </summary>
		/// <param name="sceneFactory"> : �f�X�N���v�^�q�[�v�|�C���^</param>
		void SetDescriptorHeapPointer(YDX::DescriptorHeap* pDescHeap);

		/// <summary>
		/// ���݂̃V�[�����擾
		/// </summary>
		/// <returns>���݂̃V�[����</returns>
		std::string CurrentSceneName() const { return sceneName_; }

		/// <summary>
		/// �I���t���O�擾
		/// </summary>
		/// <returns>�I���t���O</returns>
		bool IsEnd() const { return isEnd_; }

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
