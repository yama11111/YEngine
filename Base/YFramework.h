#pragma once
#include "SceneManager.h"

namespace YBase
{
	class YFramework
	{
	protected:
		// 終了フラグ
		bool isEnd_ = false;
	public:
		// 初期化
		virtual bool Initialize();
		// 終了処理
		virtual void Finalize();
		// 更新
		virtual void Update();
		// 描画
		virtual void Draw() = 0;
		// 終了フラグ取得
		virtual bool IsEnd() { return isEnd_; }
	public:
		// 実行
		void Run();
	public:
		YFramework() = default;
		virtual ~YFramework() = default;
	protected:
		// シーンマネージャー
		static YScene::SceneManager* sceneMan_;
	public:
		struct StaticInitStatus 
		{
			YScene::SceneManager* sceneMan_;
		};
	public:
		// 静的初期化
		static void StaticInitialize(const StaticInitStatus& state);
	};
}
