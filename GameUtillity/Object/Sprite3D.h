#pragma once
#include "Sprite3DCommon.h"
#include "Transform.h"

namespace YGame
{
	// スプライト3D用オブジェクトクラス
	class Sprite3DObject :
		public Transform, 
		private Sprite3DObjectCommon
	{
	private:
		// 定数バッファ (行列)
		YDX::ConstBuffer<Sprite3DObjectCommon::CBData> cBuff_;
		// ビュープロジェクションポインタ
		ViewProjection* pVP_ = nullptr;
		// 色ポインタ
		Color* pColor_ = nullptr;

		// X軸ビルボード
		bool isXAxisBillboard_ = false;
		// Y軸ビルボード
		bool isYAxisBillboard_ = false;
	public:
		/// <summary>
		/// 生成 + 初期化 (デフォルト初期化)
		/// </summary>
		/// <param name="status"> : 設定用ステータス</param>
		/// <param name="(Vector3) status.pos_"> : 位置</param>
		/// <param name="(Vector3) status.rota_"> : 回転</param>
		/// <param name="(Vector3) status.scale_"> : 大きさ</param>
		/// <param name="-------------------------------------"></param>
		/// <param name="isXAxisBillboard"> : X軸ビルボードか</param>
		/// <param name="isYAxisBillboard"> : Y軸ビルボードか</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static Sprite3DObject* Create(const Status& status, bool isXAxisBillboard, bool isYAxisBillboard);
		/// <summary>
		/// 生成 + 初期化 (Transform以外は nullの時 デフォルトで初期化)
		/// </summary>
		/// <param name="status"> : 設定用ステータス</param>
		/// <param name="(Vector3) status.pos_"> : 位置</param>
		/// <param name="(Vector3) status.rota_"> : 回転</param>
		/// <param name="(Vector3) status.scale_"> : 大きさ</param>
		/// <param name="-------------------------------------"></param>
		/// <param name="isXAxisBillboard"> : X軸ビルボードか</param>
		/// <param name="isYAxisBillboard"> : Y軸ビルボードか</param>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		/// <param name="pColor"> : 色ポインタ</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static Sprite3DObject* Create(const Status& status, bool isXAxisBillboard, bool isYAxisBillboard, 
			ViewProjection* pVP, Color* pColor);
	public:
		// ビルボード設定
		void SetIsBillboard(bool isXAxisBillboard, bool isYAxisBillboard);
		// ビュープロジェクション設定 (null = Default)
		void SetViewProjection(ViewProjection* pVP);
		// 色設定 (null = Default)
		void SetColor(Color* pColor);
	public:
		// 描画前コマンド
		void SetDrawCommand();
	private:
		// ビルボード行列計算
		YMath::Matrix4 BillboardMatrix();
	private:
		Sprite3DObject() = default;
	public:
		~Sprite3DObject() = default;
	};

	// スプライト3Dクラス
	class Sprite3D : private Sprite3DCommon
	{
	private:
		// 頂点データ
		YDX::Vertices<VData> vt_;

		// テクスチャ
		UINT tex_ = UINT32_MAX;

		// 非表示
		bool isInvisible_ = false;
	public:
		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="texIndex"> : テクスチャインデックス</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static Sprite3D* Create(const UINT texIndex);
	public:
		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="pObj"> : オブジェクトポインタ</param>
		void Draw(Sprite3DObject* pObj);
	private:
		Sprite3D() = default;
	public:
		~Sprite3D() = default;
	};
}
