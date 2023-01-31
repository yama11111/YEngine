#pragma once
#include "SceneManager.h"

namespace YBase
{
	class YFramework
	{
	protected:
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
	protected:
		// �V�[���}�l�[�W���[
		static YScene::SceneManager* sceneMan_;
	public:
		struct StaticInitStatus 
		{
			YScene::SceneManager* sceneMan_;
		};
	public:
		// �ÓI������
		static void StaticInitialize(const StaticInitStatus& state);
	};
}
