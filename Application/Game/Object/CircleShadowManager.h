/**
 * @file CircleShadowManager.h
 * @brief 丸影管理クラス
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include "ConstBufferObject.h"
#include "CBShadowGroup.h"
#include <unordered_map>
#include <memory>

namespace YGame
{
	class CircleShadowManager
	{
	
	public:

		// キー
		enum class Key
		{
			eWorld_0,
			eWorld_1,
			eWorld_2,
			eKeyNum,
		};
	
	public:

		/// <summary>
		/// 初期化
		/// </summary>
		void Intialize();

		/// <summary>
		/// リセット
		/// </summary>
		void Reset();

		/// <summary>
		/// 丸影を適用する
		/// </summary>
		/// <param name="Key"> : キー</param>
		/// <param name="pos"> : 位置</param>
		void ActivateCircleShadow(const Key key, const YMath::Vector3& pos);

		/// <summary>
		/// 定数バッファポインタ取得
		/// </summary>
		/// <param name="key"> : キー</param>
		/// <returns>定数バッファポインタ</returns>
		BaseConstBuffer* CBPtr(const Key key);

	public:

		/// <summary>
		/// シングルトンインスタンス取得
		/// </summary>
		/// <returns>シングルトンインスタンス</returns>
		static CircleShadowManager* GetInstance();

	private:

		// 影定数バッファ
		std::unordered_map<Key, std::unique_ptr<ConstBufferObject<CBShadowGroup>>> cbShadow_;
	
	private:

		CircleShadowManager() = default;
		~CircleShadowManager() = default;
		CircleShadowManager(const CircleShadowManager&) = delete;
		const CircleShadowManager& operator=(const CircleShadowManager&) = delete;
		
	};
}
