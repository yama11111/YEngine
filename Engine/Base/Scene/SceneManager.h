#pragma once
#include "ISceneFactory.h"
#include "BaseTransition.h"

namespace YGame
{
	class SceneManager
	{
	public:

		/// <summary>
		/// �V���O���g���C���X�^���X
		/// </summary>
		/// <returns>�C���X�^���X�|�C���^</returns>
		static SceneManager* GetInstance();
	
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
		/// �V�[���؂�ւ�
		/// </summary>
		/// <param name="sceneName"> : ���V�[����</param>
		/// <param name="transitionName"> : �J�ږ�</param>
		void Transition(const std::string& sceneName, const std::string& transitionName);

	public:

		/// <summary>
		/// �V�[���t�@�N�g���[�ݒ�
		/// </summary>
		/// <param name="sceneFactory"> : �V�[���t�@�N�g���[</param>
		void SetSceneFactory(ISceneFactory* sceneFactory);

		/// <summary>
		/// �V�[���J�ڑ}��
		/// </summary>
		/// <param name="transitionName"> : �J�ڂ̖��O</param>
		/// <param name="transition"> : �g�����W�V���� (���I�C���X�^���X)</param>
		void InsertTransition(const std::string& transitionName, BaseTransition* transition);

		/// <summary>
		/// �f�X�N���v�^�q�[�v�|�C���^�ݒ�
		/// </summary>
		/// <param name="sceneFactory"> : �f�X�N���v�^�q�[�v�|�C���^</param>
		void SetDescriptorHeapPointer(YDX::DescriptorHeap* pDescHeap);

		/// <summary>
		/// �I���t���O�ݒ�
		/// </summary>
		/// <param name="isEnd"> : �I���t���O</param>
		void SetEnd(const bool isEnd) { isEnd_ = isEnd; }

		/// <summary>
		/// �I���t���O�擾
		/// </summary>
		/// <returns>�I���t���O</returns>
		bool IsEnd() const { return isEnd_; }

		/// <summary>
		/// �J�ڃt���O�擾
		/// </summary>
		/// <returns>�J�ڃt���O</returns>
		bool IsTransition() const { return isTransition_; }

	private:

		SceneManager() = default;
		~SceneManager() = default;
		SceneManager(const SceneManager&) = delete;
		const SceneManager& operator=(const SceneManager&) = delete;

	private:

		// �J�ڍX�V
		void UpdateTransition();

		// �V�[���؂�ւ�
		void Change();

	private:

		// �V�[��
		std::unique_ptr<BaseScene> scene_;

		// �V�[���t�@�N�g���[
		std::unique_ptr<ISceneFactory> sceneFactory_;

		// �g�����W�V����
		std::unordered_map<std::string, std::unique_ptr<BaseTransition>> transitions_;

		// �f�X�N���v�^�q�[�v�|�C���^
		YDX::DescriptorHeap* pDescHeap_ = nullptr;


		// �V�[���J�ڃt���O
		bool isTransition_ = false;

		// �V�[����
		std::string nextSceneName_ = {};

		// �g�����W�V������
		std::string transitionName_ = {};


		// �I���t���O
		bool isEnd_ = false;

	};
}