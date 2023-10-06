#pragma once
#include "ISceneFactory.h"
#include "BaseTransition.h"

namespace YGame
{
	class SceneManager
	{
	public:

		/// <summary>
		/// シングルトンインスタンス
		/// </summary>
		/// <returns>インスタンスポインタ</returns>
		static SceneManager* GetInstance();
	
	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="sceneName"> : 初期シーン</param>
		void Initialize(const std::string& sceneName);

		/// <summary>
		/// 終了処理
		/// </summary>
		void Finalize();

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
		/// シーン切り替え
		/// </summary>
		/// <param name="sceneName"> : 次シーン名</param>
		/// <param name="transitionName"> : 遷移名</param>
		void Transition(const std::string& sceneName, const std::string& transitionName);

	public:

		/// <summary>
		/// シーンファクトリー設定
		/// </summary>
		/// <param name="sceneFactory"> : シーンファクトリー</param>
		void SetSceneFactory(ISceneFactory* sceneFactory);

		/// <summary>
		/// シーン遷移挿入
		/// </summary>
		/// <param name="transitionName"> : 遷移の名前</param>
		/// <param name="transition"> : トランジション (動的インスタンス)</param>
		void InsertTransition(const std::string& transitionName, BaseTransition* transition);

		/// <summary>
		/// デスクリプタヒープポインタ設定
		/// </summary>
		/// <param name="sceneFactory"> : デスクリプタヒープポインタ</param>
		void SetDescriptorHeapPointer(YDX::DescriptorHeap* pDescHeap);

		/// <summary>
		/// 終了フラグ設定
		/// </summary>
		/// <param name="isEnd"> : 終了フラグ</param>
		void SetEnd(const bool isEnd) { isEnd_ = isEnd; }

		/// <summary>
		/// 終了フラグ取得
		/// </summary>
		/// <returns>終了フラグ</returns>
		bool IsEnd() const { return isEnd_; }

		/// <summary>
		/// 遷移フラグ取得
		/// </summary>
		/// <returns>遷移フラグ</returns>
		bool IsTransition() const { return isTransition_; }

	private:

		SceneManager() = default;
		~SceneManager() = default;
		SceneManager(const SceneManager&) = delete;
		const SceneManager& operator=(const SceneManager&) = delete;

	private:

		// 遷移更新
		void UpdateTransition();

		// シーン切り替え
		void Change();

	private:

		// シーン
		std::unique_ptr<BaseScene> scene_;

		// シーンファクトリー
		std::unique_ptr<ISceneFactory> sceneFactory_;

		// トランジション
		std::unordered_map<std::string, std::unique_ptr<BaseTransition>> transitions_;

		// デスクリプタヒープポインタ
		YDX::DescriptorHeap* pDescHeap_ = nullptr;


		// シーン遷移フラグ
		bool isTransition_ = false;

		// シーン名
		std::string nextSceneName_ = {};

		// トランジション名
		std::string transitionName_ = {};


		// 終了フラグ
		bool isEnd_ = false;

	};
}