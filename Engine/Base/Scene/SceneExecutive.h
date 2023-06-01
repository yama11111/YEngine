#pragma once
#include "SceneManager.h"
#include "TransitionManager.h"

namespace YScene
{
	class SceneExecutive
	{

	private:
		
		// �V�[���}�l�[�W���[
		SceneManager* sceneMan_ = nullptr;
		
		// ���V�[���̖��O
		std::string nextSceneName_ = {};

		// �V�[���J�ڃ}�l�[�W���[
		TransitionManager* transitionMan_ = nullptr;

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="sceneName"> : �����V�[����</param>
		/// <param name="transitionName"> : �J�ږ�</param>
		void Initialize(const std::string& sceneName, const std::string& transitionName);

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
		/// <param name="transitionName"> : �J�ږ�</param>
		/// <param name="loadFrame"> : �ǂݍ��ގ���</param>
		/// <param name="leftTop"> : 1�ԍ���̃u���b�N�̈ʒu</param>
		void Change(
			const std::string& sceneName, 
			const std::string& transitionName,
			const uint32_t changeFrame, const uint32_t loadFrame);

	public:
				
		/// <summary>
		/// �t�@�N�g���[�ݒ�
		/// </summary>
		/// <param name="sceneFactory"> : �V�[���t�@�N�g���[</param>
		/// <param name="transitionFactory"> : �J�ڃt�@�N�g���[</param>
		static void SetFactory(ISceneFactory* sceneFactory, ITransitionFactory* transitionFactory);

	public:

		// �V���O���g��
		static SceneExecutive* GetInstance();

	private:

		SceneExecutive() = default;

		~SceneExecutive() = default;

		SceneExecutive(const SceneExecutive&) = delete;

		const SceneExecutive& operator=(const SceneExecutive&) = delete;

	};
}

