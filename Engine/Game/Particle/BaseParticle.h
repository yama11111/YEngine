//#pragma once
//#include "Model.h"
//#include "Sprite2D.h"
//#include "Sprite3D.h"
//#include "Lerp.h"
//#include "Timer.h"
//#include "Power.h"
//
//namespace YGame
//{
//	// パーティクル基底クラス
//	class BaseParticle
//	{
//	
//	public:
//
//		/// <summary>
//		/// 初期化
//		/// </summary>
//		/// <param name="aliveFrame"> : 生存時間 (F)</param>
//		/// <param name="locaiton"> : 描画場所</param>
//		void Initialize(const uint32_t aliveFrame, const DrawLocation location);
//
//		/// <summary>
//		/// 更新
//		/// </summary>
//		virtual void Update() = 0;
//
//		/// <summary>
//		/// 描画
//		/// </summary>
//		virtual void Draw() = 0;
//
//		/// <summary>
//		/// 生存フラグ取得
//		/// </summary>
//		/// <returns>生存フラグ</returns>
//		virtual bool IsAlive() const { return isAlive_; }
//	
//	public:
//
//		BaseParticle() = default;
//
//		/// <summary>
//		/// コンストラクタ
//		/// </summary>
//		/// <param name="aliveFrame"> : 生存時間 (F)</param>
//		/// <param name="locaiton"> : 描画場所</param>
//		BaseParticle(const uint32_t aliveFrame, const DrawLocation location);
//
//		virtual ~BaseParticle() = default;
//	
//	protected:
//		
//		// 生存フラグ
//		bool isAlive_ = false;
//		
//		// 生存タイマー
//		YMath::Timer aliveTimer_;
//		
//		// 描画場所
//		DrawLocation location_;
//	
//	protected:
//
//		/// <summary>
//		/// 生命更新
//		/// </summary>
//		/// <returns> : 生きているか</returns>
//		void UpdateLife();
//
//	};
//
//	// パーティクル基底クラス (Model)
//	class BaseParticleForModel : public BaseParticle
//	{
//
//	public:
//
//		/// <summary>
//		/// 初期化
//		/// </summary>
//		/// <param name="aliveFrame"> : 生存時間 (F)</param>
//		/// <param name="status"> : トランスフォーム情報</param>
//		/// <param name="pModel"> : モデルポインタ</param>
//		/// <param name="locaiton"> : 描画場所</param>
//		void Initialize(
//			const uint32_t aliveFrame,
//			const Transform::Status& status,
//			Model* pModel, const DrawLocation location);
//
//		/// <summary>
//		/// 更新
//		/// </summary>
//		virtual void Update() override = 0;
//
//		/// <summary>
//		/// 描画
//		/// </summary>
//		virtual void Draw() override = 0;
//	
//	public:
//
//		/// <summary>
//		/// 静的初期化
//		/// </summary>
//		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
//		static void StaticInitialize(ViewProjection* pVP);
//	
//	public:
//
//		BaseParticleForModel() = default;
//
//		/// <summary>
//		/// コンストラクタ
//		/// </summary>
//		/// <param name="aliveFrame"> : 生存時間 (F)</param>
//		/// <param name="status"> : トランスフォーム情報</param>
//		/// <param name="pModel"> : モデルポインタ</param>
//		/// <param name="locaiton"> : 描画場所</param>
//		BaseParticleForModel(
//			const uint32_t aliveFrame,
//			const Transform::Status& status,
//			Model* pModel, const DrawLocation location);
//
//		virtual ~BaseParticleForModel() = default;
//	
//	protected:
//		
//		// オブジェクト
//		std::unique_ptr<Model::Object> obj_;
//
//		// モデルポインタ
//		Model* pModel_ = nullptr;
//	
//	protected:
//		
//		// ビュープロジェクションポインタ
//		static ViewProjection* spVP_;
//	
//	};
//
//	// パーティクル基底クラス (Sprite2D)
//	class BaseParticleForSprite2D : public BaseParticle
//	{
//
//	protected:
//
//		// オブジェクト
//		std::unique_ptr<Sprite2D::Object> obj_;
//
//		// スプライト2Dポインタ
//		Sprite2D* pSprite2D_ = nullptr;
//
//	public:
//
//		/// <summary>
//		/// 初期化
//		/// </summary>
//		/// <param name="aliveFrame"> : 生存時間 (F)</param>
//		/// <param name="status"> : トランスフォーム情報</param>
//		/// <param name="pSprite2D"> : スプライト2Dポインタ</param>
//		/// <param name="locaiton"> : 描画場所</param>
//		void Initialize(
//			const uint32_t aliveFrame,
//			const Transform::Status& status,
//			Sprite2D* pSprite2D, const DrawLocation location);
//
//		/// <summary>
//		/// 更新
//		/// </summary>
//		virtual void Update() override = 0;
//
//		/// <summary>
//		/// 描画
//		/// </summary>
//		virtual void Draw() override = 0;
//
//	public:
//
//		/// <summary>
//		/// 静的初期化
//		/// </summary>
//		static void StaticInitialize();
//
//	public:
//
//		virtual ~BaseParticleForSprite2D() = default;
//
//	};
//
//	// パーティクル基底クラス (Sprite3D)
//	class BaseParticleForSprite3D : public BaseParticle
//	{
//
//	protected:
//
//		// オブジェクト
//		std::unique_ptr<Sprite3D::Object> obj_;
//
//		// スプライト3Dポインタ
//		Sprite3D* pSprite3D_ = nullptr;
//	
//	public:
//
//		/// <summary>
//		/// オブジェクト生成
//		/// </summary>
//		/// <param name="isXAxisBillboard"> : X軸ビルボード</param>
//		/// <param name="isYAxisBillboard"> : Y軸ビルボード</param>
//		void CreateObject(const bool isXAxisBillboard, const bool isYAxisBillboard);
//
//		/// <summary>
//		/// 更新
//		/// </summary>
//		virtual void Update() override = 0;
//
//		/// <summary>
//		/// 描画
//		/// </summary>
//		virtual void Draw() override = 0;
//
//	protected:
//
//		// ビュープロジェクションポインタ
//		static YGame::ViewProjection* spVP_;
//
//	public:
//
//		/// <summary>
//		/// 静的初期化
//		/// </summary>
//		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
//		static void StaticInitialize(YGame::ViewProjection* pVP);
//
//	public:
//
//		virtual ~BaseParticleForSprite3D() = default;
//
//	};
//}
