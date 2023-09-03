#pragma once
#include "Model.h"
#include "DrawObjectForModel.h"
#include "ConstBufferObject.h"
#include "ViewProjection.h"
#include "DebugTextAttacher.h"
#include "Timer.h"

#include "CBModelTransform.h"
#include "CBColor.h"
#include "CBMaterial.h"
#include "CBLightGroup.h"
#include "CBTexConfig.h"

namespace YGame
{
	class BaseDrawer : 
		public DebugTextAttacher
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		virtual void Initialize(Transform* pParent, const uint16_t drawPriority);

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update();

		/// <summary>
		/// アニメーション再生
		/// </summary>
		/// <param name="index"> : アニメーション番号</param>
		/// <param name="frame"> : 再生フレーム</param>
		/// <param name="isRoop"> : ループするか</param>
		void PlayAnimation(const uint16_t index, const uint32_t frame, const bool isRoop = false);

		/// <summary>
		/// アニメーションをやめる
		/// </summary>
		/// <param name="index"> : アニメーション番号</param>
		void AbortAnimation(const uint16_t index);

		/// <summary>
		/// 描画
		/// </summary>
		virtual void Draw();

		/// <summary>
		/// デバッグテキスト本文
		/// </summary>
		virtual void DrawDebugTextContent() override;

	public:

		/// <summary>
		/// トランスフォームポインタ取得
		/// </summary>
		/// <returns>トランスフォームポインタ</returns>
		Transform* TransformPtr() const { return &obj_->transform_; }
		
		/// <summary>
		/// 親トランスフォーム設定
		/// </summary>
		/// <param name="pParent"> : 親トランスフォームポインタ</param>
		virtual void SetParent(Transform* pParent);

		/// <summary>
		/// オフセット設定
		/// </summary>
		/// <param name="offset"> : オフセット</param>
		void SetOffset(const YMath::Vector3& offset) { offset_ = offset; }
		
		/// <summary>
		/// 描画位置設定
		/// </summary>
		/// <param name="drawPriority"> : 描画優先度</param>
		void SetDrawPriority(const uint16_t drawPriority) { drawPriority_ = drawPriority; }

		/// <summary>
		/// 描画するか
		/// </summary>
		/// <param name="isVisible"> : 描画するか</param>
		void SetIsVisible(const bool isVisible) { isVisible_ = isVisible; }

		/// <summary>
		/// 描画更新するか
		/// </summary>
		/// <param name="isVisibleUpdate"> : 描画更新するか</param>
		void SetIsVisibleUpdate(const bool isVisibleUpdate) { isVisibleUpdate_ = isVisibleUpdate; }
	
	public:

		BaseDrawer() = default;

		virtual ~BaseDrawer() = default;

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		static void StaticInitialize(ViewProjection* pVP);

	protected:

		// アニメーション用タイマー
		struct AnimationTimer
		{
			// タイマー
			YMath::Timer timer;

			// ループするか
			bool isRoop = false;
		};
	
	protected:

		// 親トランスフォームポインタ
		Transform* pParent_ = nullptr;

		// オフセット
		YMath::Vector3 offset_;
		
		// オブジェクト
		std::unique_ptr<DrawObjectForModel> obj_;
		
		// 色定数バッファ
		std::unique_ptr<ConstBufferObject<CBColor>> cbColor_;

		// マテリアル定数バッファ
		std::unique_ptr<ConstBufferObject<CBMaterial>> cbMaterial_;

		// 描画位置
		uint16_t drawPriority_ = 0;

		// シェーダー
		std::string shaderKey_ = "ModelDefault";

		// 描画フラグ
		bool isVisible_ = true;
		
		// 描画更新フラグ
		bool isVisibleUpdate_ = true;

		// アニメーションビットフラグ
		uint16_t animationBitFlag_ = 0;

		// アニメーションタイマーマップ
		std::unordered_map<uint16_t, AnimationTimer> animationTimers_;

		// アニメーション変動値
		Transform::Status animeStatus_;

	protected:

		// ビュープロジェクションポインタ
		static ViewProjection* spVP_;

	protected:

		/// <summary>
		/// アニメーションタイマー挿入
		/// </summary>
		virtual void InsertAnimationTimers() = 0;

		/// <summary>
		/// サブアニメーション再生
		/// </summary>
		/// <param name="index"> : アニメーション番号</param>
		/// <param name="frame"> : 再生フレーム</param>
		virtual void PlaySubAnimation(const uint16_t index, const uint32_t frame) = 0;

		/// <summary>
		/// アニメーションタイマー更新
		/// </summary>
		void UpdateAnimationTimer();

		/// <summary>
		/// アニメーション更新
		/// </summary>
		virtual void UpdateAnimtion() = 0;

		/// <summary>
		/// 描画するか更新
		/// </summary>
		void VisibleUpdate();

	};
}
