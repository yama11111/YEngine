#pragma once
#include "BaseDrawer.h"

namespace YGame
{
	class AxisDrawer final :
		public BaseDrawer
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		/// <returns>プレイヤー描画クラスポインタ (動的インスタンス)</returns>
		static AxisDrawer* Create(Transform* pParent, const size_t drawPriority);

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void LoadResource();

		/// <summary>
		/// 名前取得
		/// </summary>
		/// <returns>名前</returns>
		static std::string Name();

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		void Initialize(Transform* pParent, const size_t drawPriority) override;

		/// <summary>
		/// 更新
		/// </summary>
		void Update() override;

		/// <summary>
		/// 描画
		/// </summary>
		void Draw() override;

		/// <summary>
		/// 親トランスフォーム設定
		/// </summary>
		/// <param name="pParent"> : 親トランスフォームポインタ</param>
		void SetParent(Transform* pParent) override;

	public:

		AxisDrawer() = default;

		~AxisDrawer() = default;

	private:

		// オブジェクト
		std::array<std::unique_ptr<DrawObjectForModel>, 3> objs_;

		// 色定数バッファ
		std::array<std::unique_ptr<ConstBufferObject<CBColor>>, 3> cbColors_;
	
	private:

		// モデルポインタ
		static Model* spModel_;

	private:

		/// <summary>
		/// アニメーションタイマー挿入
		/// </summary>
		void InsertAnimationTimers() override {};

		/// <summary>
		/// サブアニメーション再生
		/// </summary>
		/// <param name="index"> : アニメーション番号</param>
		/// <param name="frame"> : 再生フレーム</param>
		//void PlaySubAnimation(const uint16_t index, const uint32_t frame) override {};

		/// <summary>
		/// アニメーション更新
		/// </summary>
		void UpdateAnimation() override {};
	};
}
