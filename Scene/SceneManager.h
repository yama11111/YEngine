#pragma once
#include "ISceneFactory.h"

namespace YScene
{
	class SceneManager
	{
	private:
		// �V�[��
		std::unique_ptr<BaseScene> scene_;
		// ���̃V�[��
		BaseScene* nextScene_ = nullptr;
		// �V�[���t�@�N�g���[
		std::unique_ptr<ISceneFactory> sceneFactory_;
	public:
		// �ǂݍ���
		void Load();
		// ������
		void Initialize();
		// �I������
		void Finalize();
		// �X�V
		void Update();
		// �`��
		void Draw();
	public:
		// ���V�[���\��
		void Change(const std::string& sceneName);
		// �V�[���t�@�N�g���[�ݒ�
		void SetSceneFactory(ISceneFactory* sceneFactory);
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
