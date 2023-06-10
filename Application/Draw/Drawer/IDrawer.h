#pragma once
#include "Model.h"

namespace YGame
{
	class IDrawer
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		virtual void Initialize(Transform* pParent);

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update() = 0;

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="location"> : 場所</param>
		virtual void Draw(const DrawLocation location) = 0;

	public:

		/// <summary>
		/// アニメーション再生
		/// </summary>
		/// <param name="index"> : アニメーション番号</param>
		/// <param name="frame"> : 再生フレーム</param>
		virtual void PlayAnimation(const uint16_t index, const uint16_t frame) = 0;

	public:

		IDrawer() = default;

		virtual ~IDrawer() = default;

	protected:

		// 3D用オブジェクト
		std::unique_ptr<Model::Object> obj_;

		// モデルポインタ
		Model* pModel_ = nullptr;
	};
}
