#pragma once
#include "Model.h"
#include "DebugTextAttacher.h"

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
		/// <param name="location"> : 描画位置</param>
		virtual void Initialize(Transform* pParent, const DrawLocation location);

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update() = 0;

		/// <summary>
		/// 描画
		/// </summary>
		virtual void Draw() = 0;

		/// <summary>
		/// アニメーション再生
		/// </summary>
		/// <param name="index"> : アニメーション番号</param>
		/// <param name="frame"> : 再生フレーム</param>
		virtual void PlayAnimation(const uint16_t index, const uint16_t frame) = 0;

		/// <summary>
		/// 親トランスフォーム設定
		/// </summary>
		/// <param name="pParent"> : 親トランスフォームポインタ</param>
		void SetParent(Transform* pParent);
		
		/// <summary>
		/// 描画位置設定
		/// </summary>
		/// <param name="location"> : 描画位置</param>
		inline void SetDrawLocation(const DrawLocation location) { location_ = location; }

	public:

		/// <summary>
		/// デバッグテキスト本文
		/// </summary>
		virtual void DrawDebugTextContent() override;

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
		/// <param name="location"> : 描画位置</param>
		BaseDrawer(const DrawLocation location);

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="location"> : 描画位置</param>
		BaseDrawer(Transform* pParent, const DrawLocation location);

		virtual ~BaseDrawer() = default;

	protected:

		// 親トランスフォームポインタ
		Transform* pParent_ = nullptr;

		// 3D用オブジェクト
		std::unique_ptr<Model::Object> obj_;

		// 色
		std::unique_ptr<CBColor> color_;

		// マテリアル
		std::unique_ptr<CBMaterial> material_;

		// テクスチャ設定
		std::unique_ptr<CBTexConfig> texConfig_;

		// モデルポインタ
		Model* pModel_ = nullptr;

		// 描画位置
		DrawLocation location_;

	protected:

		// ビュープロジェクションポインタ
		static ViewProjection* spVP_;
	};
}
