#pragma once
#include "ITransitionFactory.h"

namespace YScene
{
	class TransitionManager
	{
	
	private:
		
		// トランジション
		std::unique_ptr<BaseTransition> transition_;

		// トランジションシーン名
		std::string transitionName_ = {};

		// トランジションファクトリー
		static std::unique_ptr<ITransitionFactory> transitionFactory_;
		
	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="transitionName"> : 遷移名</param>
		void Initialize(const std::string& transitionName);

		/// <summary>
		/// リセット (中身だけ初期化)
		/// </summary>
		void Reset();

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
		/// シーン遷移開始
		/// </summary>
		/// <param name="loadFrame"> : 読み込む時間</param>
		/// <param name="leftTop"> : 1番左上のブロックの位置</param>
		virtual void Activate(const uint32_t changeFrame, const uint32_t loadFrame);

	public:
		
		/// <summary>
		/// 遷移ファクトリー設定
		/// </summary>
		/// <param name="transitionFactory"> : 遷移ファクトリー</param>
		static void SetTransitionFactory(ITransitionFactory* transitionFactory);
		
		/// <summary>
		/// シーン遷移設定
		/// </summary>
		/// <param name="transitionName"> : 遷移の名前</param>
		void SetTransition(const std::string& transitionName);

		/// <summary>
		/// 現在のトランジション名取得
		/// </summary>
		/// <returns>現在のトランジション名</returns>
		std::string CurrentTransitionName() const { return transitionName_; }

		/// <summary>
		/// 動作中か取得
		/// </summary>
		/// <returns>動作中か</returns>
		bool IsAct() const;

		/// <summary>
		/// 幕切れ中か
		/// </summary>
		/// <returns></returns>
		bool IsFalling() const;

		/// <summary> 
		/// 切り替わりの瞬間か取得
		/// </summary>
		/// <returns>切り替わりの瞬間か</returns>
		bool IsChangeMoment() const;

		/// <summary>
		/// 幕開け中か
		/// </summary>
		/// <returns>切り替わっている途中か</returns>
		bool IsRising() const;

		/// <summary>
		/// 終了しているか取得
		/// </summary>
		/// <returns>終了しているか</returns>
		bool IsEnd() const;
	
	public:

		// シングルトン
		static TransitionManager* GetInstance();

	private:

		TransitionManager() = default;

		~TransitionManager() = default;

		TransitionManager(const TransitionManager&) = delete;

		const TransitionManager& operator=(const TransitionManager&) = delete;
	
	public:
		
		// 静的初期化
		static void StaticInitialize();
	
	};
}

