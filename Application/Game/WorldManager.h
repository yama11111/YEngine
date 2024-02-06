/**
 * @file WorldManager.h
 * @brief 世界管理クラス
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include "Vector3.h"
#include <string>
#include <array>

namespace YGame
{
	class WorldManager
	{

	public:

		// キー
		enum class Key : size_t
		{
			eStartKey, eWorldKey, eFeverKey, eGoalKey, eNum,
		};
	
	public:

		/// <summary>
		/// シングルトン
		/// </summary>
		/// <returns></returns>
		static WorldManager* GetInstance();
	
	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="key"> : キー</param>
		void Initialize(const Key& key);

		/// <summary>
		/// 走行距離をリセットする
		/// </summary>
		/// <param name="key"> : キー</param>
		void ResetMileage(const Key& key);
	
	public:
		
		/// <summary>
		/// キー設定
		/// </summary>
		/// <param name="key"> : キー</param>
		void SetWorldKey(const Key& key);

		/// <summary>
		/// 走行距離をセットする
		/// </summary>
		/// <param name="key"> : キー</param>
		/// <param name="mileage"> : 走行距離</param>
		void SetMileage(const Key& key, const YMath::Vector3 mileage);

	public:

		/// <summary>
		/// キー(string型)取得
		/// </summary>
		/// <param name="key"> : キー</param>
		/// <returns>キー(string型)</returns>
		std::string WorldKeyStr(const Key& key) const;
		
		/// <summary>
		/// 現在のキー取得
		/// </summary>
		/// <returns>現在のキー</returns>
		Key CurrentWorldKey() const;

		/// <summary>
		/// 現在のキー取得
		/// </summary>
		/// <returns>現在のキー</returns>
		std::string CurrentWorldKeyStr() const;

		/// <summary>
		/// 走行距離取得
		/// </summary>
		/// <param name="key"> : キー</param>
		YMath::Vector3 Mileage(const Key& key) const;

		/// <summary>
		/// 現在の走行距離取得
		/// </summary>
		/// <returns>現在の走行距離</returns>
		YMath::Vector3 CurrentMileage() const;
	
	private:

		// 現在世界キー
		Key currentWorldKey_{};

		// キーの数
		static const size_t kKeyNum = static_cast<size_t>(Key::eNum);
		
		// 世界ごとの走行距離
		std::array<YMath::Vector3, kKeyNum> mileages_{};

	private:

		WorldManager() = default;
		~WorldManager() = default;
		WorldManager(const WorldManager&) = delete;
		const WorldManager& operator=(const WorldManager&) = delete;
	
	};
}
