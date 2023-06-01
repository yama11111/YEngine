#pragma once
#include "SceneManager.h"
#include "TransitionManager.h"

namespace YScene
{
	class SceneExecutive
	{

	private:
		
		// シーンマネージャー
		SceneManager* sceneMan_ = nullptr;
		
		// 次シーンの名前
		std::string nextSceneName_ = {};

		// シーン遷移マネージャー
		TransitionManager* transitionMan_ = nullptr;

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="sceneName"> : 初期シーン名</param>
		/// <param name="transitionName"> : 遷移名</param>
		void Initialize(const std::string& sceneName, const std::string& transitionName);

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();

	public:

		/// <summary>
		/// 次シーン予約
		/// </summary>
		/// <param name="sceneName"> : 次シーン名</param>
		/// <param name="transitionName"> : 遷移名</param>
		/// <param name="loadFrame"> : 読み込む時間</param>
		/// <param name="leftTop"> : 1番左上のブロックの位置</param>
		void Change(
			const std::string& sceneName, 
			const std::string& transitionName,
			const uint32_t changeFrame, const uint32_t loadFrame);

	public:
				
		/// <summary>
		/// ファクトリー設定
		/// </summary>
		/// <param name="sceneFactory"> : シーンファクトリー</param>
		/// <param name="transitionFactory"> : 遷移ファクトリー</param>
		static void SetFactory(ISceneFactory* sceneFactory, ITransitionFactory* transitionFactory);

	public:

		// シングルトン
		static SceneExecutive* GetInstance();

	private:

		SceneExecutive() = default;

		~SceneExecutive() = default;

		SceneExecutive(const SceneExecutive&) = delete;

		const SceneExecutive& operator=(const SceneExecutive&) = delete;

	};
}

