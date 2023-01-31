#pragma once
#include "ISceneFactory.h"

namespace YScene
{
	class SceneManager
	{
	private:
		// シーン
		std::unique_ptr<BaseScene> scene_;
		// 次のシーン
		BaseScene* nextScene_ = nullptr;
		// シーンファクトリー
		std::unique_ptr<ISceneFactory> sceneFactory_;
	public:
		// 読み込み
		void Load();
		// 初期化
		void Initialize();
		// 終了処理
		void Finalize();
		// 更新
		void Update();
		// 描画
		void Draw();
	public:
		// 次シーン予約
		void Change(const std::string& sceneName);
		// シーンファクトリー設定
		void SetSceneFactory(ISceneFactory* sceneFactory);
	public:
		// シングルトン
		static SceneManager* GetInstance();
	private:
		SceneManager() = default;
		~SceneManager() = default;
		SceneManager(const SceneManager&) = delete;
		const SceneManager& operator=(const SceneManager&) = delete;
	};
}
