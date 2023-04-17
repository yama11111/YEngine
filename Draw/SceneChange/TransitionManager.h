#pragma once
#include "ITransition.h"
#include <memory>

namespace YGame
{
	// シーン遷移マネージャー
	class TransitionManager
	{
	public:
		// 種類
		enum class Type
		{
			Blackout, // 暗転
			InfectionBlocks, // 浸食ブロック
			End, // リサイズ用 (使わない)
		};
	private:
		// トランジション配列
		std::vector<std::unique_ptr<ITransition>> tras_;
	public:
		// 初期化
		void Initialize();
		// リセット(中身だけ初期化)
		void Reset();
		// 更新
		void Update();
		// 描画
		void Draw();
	public:
		/// <summary>
		/// 遷移
		/// </summary>
		/// <param name="type"> : 遷移の仕方</param>
		/// <param name="-------------------------------"></param>
		/// <param name="Type::Blackout"> : 暗転</param>
		/// <param name="Type::InfectionBlocks"> : 浸食ブロック(画面全体が埋め尽くされる)</param>
		/// <param name="Type::End"> : リサイズ用 (使わない)</param>
		void Activate(const Type& type);
	public:
		// 切り替わっている途中か
		bool IsPreChange() const;
		// 切り替わりの瞬間か
		bool IsChangeMoment() const;
		// 終了しているか
		bool IsEnd() const;
	public:
		// 静的初期化
		static void StaticInitialize();
	public:
		// シングルトン
		static TransitionManager* GetInstance();
	private:
		TransitionManager() = default;
		~TransitionManager() = default;
		TransitionManager(const TransitionManager&) = delete;
		const TransitionManager& operator=(const TransitionManager&) = delete;
	};

	// シーン遷移の種類
	using TransitionType = TransitionManager::Type;
}

