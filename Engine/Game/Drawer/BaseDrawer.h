#pragma once
#include "BaseDrawObject.h"
#include "ConstBufferObject.h"
#include "ViewProjection.h"
#include "DebugTextAttacher.h"
#include "Timer.h"

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
		virtual void Initialize(Transform* pParent, const size_t drawPriority);

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update();

		/// <summary>
		/// アニメーション再生
		/// </summary>
		/// <param name="index"> : アニメーション番号</param>
		/// <param name="isTimerReset"> : タイマーを始めからやり直すか</param>
		void PlayAnimation(const uint32_t index, const bool isTimerReset = true);

		/// <summary>
		/// アニメーション停止
		/// </summary>
		/// <param name="index"> : アニメーション番号</param>
		void StopAnimation(const uint32_t index);

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
		void SetDrawPriority(const size_t drawPriority);

		/// <summary>
		/// 描画するか
		/// </summary>
		/// <param name="isVisible"> : 描画するか</param>
		void SetIsVisible(const bool isVisible);

		/// <summary>
		/// 描画更新するか
		/// </summary>
		/// <param name="isVisibleUpdate"> : 描画更新するか</param>
		void SetIsVisibleUpdate(const bool isVisibleUpdate) { isVisibleUpdate_ = isVisibleUpdate; }

	public:
	
		/// <summary>
		/// トランスフォームポインタ取得
		/// </summary>
		/// <returns>トランスフォームポインタ</returns>
		Transform* TransformPtr() { return &transform_; }

		/// <summary>
		/// タイマーが終了したか
		/// </summary>
		/// <param name="index"> : 番号</param>
		/// <returns>タイマー終了フラグ</returns>
		bool IsEndTimer(const uint32_t index);

		/// <summary>
		/// アニメーションが動作しているか
		/// </summary>
		/// <param name="index"> : 番号</param>
		/// <returns>アニメーション動作フラグ</returns>
		bool IsActAnimation(const uint32_t index);
	
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

		// トランスフォーム
		Transform transform_;

		// オフセット
		YMath::Vector3 offset_;
		
		// オブジェクトマップ
		std::unordered_map<std::string, std::unique_ptr<BaseDrawObject>> objs_;
		
		// 色定数バッファ
		std::unique_ptr<ConstBufferObject<CBColor>> cbColor_;

		// マテリアル定数バッファ
		std::unique_ptr<ConstBufferObject<CBMaterial>> cbMaterial_;
		
		// 描画更新フラグ
		bool isVisibleUpdate_ = true;


		// アニメーションビットフラグ
		uint32_t animationBitFlag_ = 0;

		// アニメーションタイマーマップ
		std::unordered_map<uint32_t, AnimationTimer> animationTimers_;

		// アニメーション変動値
		Transform::Status animeStatus_;

	protected:

		// ビュープロジェクションポインタ
		static ViewProjection* spVP_;

	protected:

		/// <summary>
		/// オブジェクト初期化
		/// </summary>
		virtual void InitializeObjects() = 0;
		
		/// <summary>
		/// タイマー初期化
		/// </summary>
		virtual void InitializeTimers();

		/// <summary>
		/// アニメーション準備
		/// </summary>
		/// <param name="index"> : アニメーション番号</param>
		virtual void GetReadyForAnimation(const uint32_t index);

		/// <summary>
		/// アニメーションタイマー更新
		/// </summary>
		void UpdateAnimationTimer();

		/// <summary>
		/// アニメーション更新
		/// </summary>
		virtual void UpdateAnimation();

		/// <summary>
		/// 描画するか更新
		/// </summary>
		void VisibleUpdate();
	
	protected:

		/// <summary>
		/// オブジェクト挿入
		/// </summary>
		/// <param name="objTag"> : オブジェクトタグ</param>
		/// <param name="pObj"> : オブジェクトポインタ</param>
		void InsertObject(const std::string& objTag, BaseDrawObject* pObj);

		/// <summary>
		/// 定数バッファ挿入
		/// </summary>
		/// <param name="pCB"> : 定数バッファポインタ</param>
		void InsertConstBuffer(BaseConstBuffer* pCB);

		/// <summary>
		/// 定数バッファ挿入
		/// </summary>
		/// <param name="objTag"> : オブジェクトタグ</param>
		/// <param name="pCB"> : 定数バッファポインタ</param>
		void InsertConstBuffer(const std::string& objTag, BaseConstBuffer* pCB);

		/// <summary>
		/// シェーダータグ設定
		/// </summary>
		/// <param name="shaderTag"> : シェーダータグ</param>
		void SetShaderTag(const std::string& shaderTag);

		/// <summary>
		/// シェーダータグ設定
		/// </summary>
		/// <param name="objTag"> : オブジェクトタグ</param>
		/// <param name="shaderTag"> : シェーダータグ</param>
		void SetShaderTag(const std::string& objTag, const std::string& shaderTag);

		/// <summary>
		/// アニメーションタイマー挿入
		/// </summary>
		void InsertAnimationTimer(const uint32_t index, const AnimationTimer& timer);

	};
}
