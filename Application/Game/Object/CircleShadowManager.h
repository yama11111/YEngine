/**
 * @file CircleShadowManager.h
 * @brief 丸影管理クラス
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include "ConstBufferObject.h"
#include "CBShadowGroup.h"
#include <memory>

namespace YGame
{
	class CircleShadowManager
	{
	
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
		/// <param name="index"> : 番号</param>
		/// <param name="pos"> : 位置</param>
		void ActivateCircleShadow(const size_t index, const YMath::Vector3& pos);

		/// <summary>
		/// 定数バッファポインタ取得
		/// </summary>
		/// <param name="index"> : 番号</param>
		/// <returns>定数バッファポインタ</returns>
		BaseConstBuffer* CBPtr(const size_t index);

	public:

		/// <summary>
		/// シングルトンインスタンス取得
		/// </summary>
		/// <returns>シングルトンインスタンス</returns>
		static CircleShadowManager* GetInstance();

	private:

		// 影グループの数
		static const size_t kShadowNum_ = 3;

		// 影定数バッファ
		std::array<std::unique_ptr<ConstBufferObject<CBShadowGroup>>, kShadowNum_> cbShadow_;
	
	private:

		CircleShadowManager() = default;
		~CircleShadowManager() = default;
		CircleShadowManager(const CircleShadowManager&) = delete;
		const CircleShadowManager& operator=(const CircleShadowManager&) = delete;
		
	};
}
