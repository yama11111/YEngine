#pragma once
#include "BaseDrawObject.h"
#include "ConstBufferObject.h"
#include "CBPostEffectTransform.h"
#include "PostEffect.h"

namespace YGame
{
	class DrawObjectForPostEffect final:
		public BaseDrawObject
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="status"> : トランスフォームステータス</param>
		/// <param name="pPostEffect"> : ポストエフェクトポインタ</param>
		/// <param name="isClearWhenTransition"> : 遷移時クリアするか</param>
		/// <returns>オブジェクトポインタ (動的インスタンス)</returns>
		static DrawObjectForPostEffect* Create(
			const Transform::Status& status,
			PostEffect* pPostEffect,
			const bool isClearWhenTransition = true);

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="status"> : トランスフォームステータス</param>
		/// <param name="isClearWhenTransition"> : 遷移時クリアするか</param>
		void Initialize(
			const Transform::Status& status = Transform::Status::Default(), 
			const bool isClearWhenTransition = true) override;

		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="status"> : トランスフォームステータス</param>
		void Update(const Transform::Status& status = {}) override;

	public:

		/// <summary>
		/// ポストエフェクトを設定
		/// </summary>
		/// <param name="pPostEffect"> : ポストエフェクトポインタ</param>
		void SetPostEffect(PostEffect* pPostEffect);

	public:

		~DrawObjectForPostEffect() = default;

	private:

		// モデル用トランスフォーム定数バッファ
		std::unique_ptr<ConstBufferObject<CBPostEffectTransform>> cbTransform_;

	private:

		// 宣言、代入を禁止
		DrawObjectForPostEffect() = default;

		DrawObjectForPostEffect(const DrawObjectForPostEffect&) = delete;

		const DrawObjectForPostEffect& operator=(const DrawObjectForPostEffect&) = delete;
	};
}
