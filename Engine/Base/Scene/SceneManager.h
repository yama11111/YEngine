#pragma once
#include "ISceneFactory.h"

namespace YScene
{
	class SceneManager
	{
	
	private:
		
		// シーン
		std::unique_ptr<BaseScene> scene_;

		// 現在シーン名
		std::string sceneName_ = {};

		// シーンファクトリー
		static std::unique_ptr<ISceneFactory> sceneFactory_;

		// デスクリプタヒープポインタ
		YDX::DescriptorHeap* pDescHeap_ = nullptr;

		// 終了フラグ
		bool isEnd_ = false;
	
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
		/// 次シーン予約
		/// </summary>
		/// <param name="sceneName"> : 次シーン名</param>
		void Change(const std::string& sceneName);
	
	public:

		/// <summary>
		/// シーンファクトリー設定
		/// </summary>
		/// <param name="sceneFactory"> : シーンファクトリー</param>
		static void SetSceneFactory(ISceneFactory* sceneFactory);
	
		/// <summary>
		/// デスクリプタヒープポインタ設定
		/// </summary>
		/// <param name="sceneFactory"> : デスクリプタヒープポインタ</param>
		void SetDescriptorHeapPointer(YDX::DescriptorHeap* pDescHeap);

		/// <summary>
		/// 現在のシーン名取得
		/// </summary>
		/// <returns>現在のシーン名</returns>
		std::string CurrentSceneName() const { return sceneName_; }

		/// <summary>
		/// 終了フラグ取得
		/// </summary>
		/// <returns>終了フラグ</returns>
		bool IsEnd() const { return isEnd_; }

		/// <summary>
		/// 終了フラグ設定
		/// </summary>
		/// <param name="isEnd"> : 終了フラグ</param>
		void SetEnd(const bool isEnd) { isEnd_ = isEnd; }

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
