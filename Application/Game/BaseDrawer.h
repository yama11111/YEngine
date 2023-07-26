#pragma once
#include "Model.h"
#include "Object.h"
#include "ConstBuffer.h"
#include "ViewProjection.h"
#include "DebugTextAttacher.h"

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
		virtual void Initialize(Transform* pParent, const uint32_t drawPriority);

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update();

		/// <summary>
		/// 描画
		/// </summary>
		virtual void Draw();

		/// <summary>
		/// デバッグテキスト本文
		/// </summary>
		virtual void DrawDebugTextContent() override;

		/// <summary>
		/// アニメーション再生
		/// </summary>
		/// <param name="index"> : アニメーション番号</param>
		/// <param name="frame"> : 再生フレーム</param>
		virtual void PlayAnimation(const uint16_t index, const uint32_t frame) = 0;

	public:

		/// <summary>
		/// トランスフォームポインタ取得
		/// </summary>
		/// <returns>トランスフォームポインタ</returns>
		Transform* TransformPtr() const { return transform_.get(); }
	
	public:
		
		/// <summary>
		/// 親トランスフォーム設定
		/// </summary>
		/// <param name="pParent"> : 親トランスフォームポインタ</param>
		void SetParent(Transform* pParent);
		
		/// <summary>
		/// 描画位置設定
		/// </summary>
		/// <param name="drawPriority"> : 描画優先度</param>
		void SetDrawPriority(const uint32_t drawPriority) { drawPriority_ = drawPriority; }

		/// <summary>
		/// 描画するか更新するか
		/// </summary>
		/// <param name="isVisibleUpdate"> : 描画するか更新するか</param>
		void SetIsVisibleUpdate(const bool isVisibleUpdate) { isVisibleUpdate_ = isVisibleUpdate; }

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		static void StaticInitialize(ViewProjection* pVP);
	
	public:

		BaseDrawer() = default;
		
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="drawPriority"> : 描画優先度</param>
		BaseDrawer(const uint32_t drawPriority);

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		BaseDrawer(Transform* pParent, const uint32_t drawPriority);

		virtual ~BaseDrawer() = default;

	protected:

		// 親トランスフォームポインタ
		Transform* pParent_ = nullptr;

		// トランスフォーム
		std::unique_ptr<Transform> transform_;
		
		// オブジェクト
		std::unique_ptr<Object> obj_;

		// モデル用トランスフォーム定数バッファ
		std::unique_ptr<ConstBuffer<CBModelTransform>> cbTransform_;
		
		// 色定数バッファ
		std::unique_ptr<ConstBuffer<CBColor>> cbColor_;

		// マテリアル定数バッファ
		std::unique_ptr<ConstBuffer<CBMaterial>> cbMaterial_;

		// テクスチャ設定定数バッファ
		std::unique_ptr<ConstBuffer<CBLightGroup>> cbLightGroup_;
		
		// テクスチャ設定定数バッファ
		std::unique_ptr<ConstBuffer<CBTexConfig>> cbTexConfig_;

		// 描画位置
		uint32_t drawPriority_ = 0;

		// シェーダー
		std::string shaderKey_ = "ModelDefault";

		// 描画フラグ
		bool isVisible_ = true;
		
		// 描画するか更新フラグ
		bool isVisibleUpdate_ = true;

		// アニメーションビットフラグ
		uint16_t animationBitFlag_ = 0;

		// アニメーション変動値
		Transform::Status animeStatus_;

	protected:

		// ビュープロジェクションポインタ
		static ViewProjection* spVP_;

	protected:

		/// <summary>
		/// 描画するか更新
		/// </summary>
		void VisibleUpdate();
	};
}
