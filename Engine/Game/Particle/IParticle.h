#pragma once
#include "Model.h"
#include "Sprite3D.h"
#include "Lerp.h"
#include "Timer.h"
#include "Power.h"

namespace YGame
{
	// パーティクル基底クラス
	class IParticle
	{
	
	public:

		// 生存フラグ
		bool isAlive_ = false;
	
	protected:
		
		// 生存タイマー
		YMath::Timer aliveTim_;
		
		// 描画場所
		DrawLocation location_;

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="aliveTime"> : 生存時間</param>
		/// <param name="locaiton"> : 描画場所</param>
		void Initialize(const uint32_t aliveTime, const DrawLocation& location);

		/// <summary>
		/// 生命更新
		/// </summary>
		/// <returns> : 生きているか</returns>
		bool UpdateLife();

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update() = 0;

		/// <summary>
		/// 描画
		/// </summary>
		virtual void Draw() = 0;
	
	public:

		virtual ~IParticle() = default;

	};

	// モデル用パーティクル基底クラス
	class IParticleModel : public IParticle
	{
	
	protected:
		
		// オブジェクト
		std::unique_ptr<Model::Object> obj_;

		// 色
		std::unique_ptr<CBColor> color_;


		// モデルポインタ
		Model* pModel_ = nullptr;

	public:

		/// <summary>
		/// オブジェクト生成
		/// </summary>
		void CreateObject();

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update() override = 0;

		/// <summary>
		/// 描画
		/// </summary>
		virtual void Draw() override = 0;
	
	protected:
		
		// ビュープロジェクションポインタ
		static YGame::ViewProjection* spVP_;
	
	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		static void StaticInitialize(YGame::ViewProjection* pVP);
	
	public:

		virtual ~IParticleModel() = default;
	
	};

	// パーティクル基底クラス
	class IParticleSprite3D : public IParticle
	{

	public:

		// 生存フラグ
		bool isAlive_ = false;

	protected:

		// オブジェクト
		std::unique_ptr<Sprite3D::Object> obj_;

		// 色
		std::unique_ptr<CBColor> color_;


		// スプライト3Dポインタ
		Sprite3D* pSprite3D_ = nullptr;
	
	public:

		/// <summary>
		/// オブジェクト生成
		/// </summary>
		/// <param name="isXAxisBillboard"> : X軸ビルボード</param>
		/// <param name="isYAxisBillboard"> : Y軸ビルボード</param>
		void CreateObject(const bool isXAxisBillboard, const bool isYAxisBillboard);

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update() override = 0;

		/// <summary>
		/// 描画
		/// </summary>
		virtual void Draw() override = 0;

	protected:

		// ビュープロジェクションポインタ
		static YGame::ViewProjection* spVP_;

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		static void StaticInitialize(YGame::ViewProjection* pVP);

	public:

		virtual ~IParticleSprite3D() = default;

	};
}
