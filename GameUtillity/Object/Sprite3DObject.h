#pragma once
#include "Transform.h"
#include "ViewProjection.h"
#include "Color.h"
#include <memory>

namespace YGame
{
	// スプライト3D用オブジェクトクラス
	class Sprite3DObject : public Transform
	{

	private:

		// 定数バッファデータ構造体
		struct CBData
		{
			YMath::Matrix4 matWorld_; // 3D変換行列
			YMath::Matrix4 matBill_; // ビルボード行列
		};

	private:
		
		// 定数バッファ (行列)
		YDX::ConstBuffer<CBData> cBuff_;
		
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
		/// <param name="isMutable"> : シーン遷移時に開放するか</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static Sprite3DObject* Create(
			const Status& status,
			bool isXAxisBillboard, bool isYAxisBillboard,
			const bool isMutable = true);

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
		/// <param name="isMutable"> : シーン遷移時に開放するか</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static Sprite3DObject* Create(
			const Status& status,
			bool isXAxisBillboard, bool isYAxisBillboard,
			ViewProjection* pVP,
			Color* pColor,
			const bool isMutable = true);
	
	public:
		
		/// <summary>
		/// 描画前コマンド
		/// </summary>
		/// <param name="transformRPIndex"></param>
		/// <param name="colorRPIndex"></param>
		void SetDrawCommand(const UINT transformRPIndex, const UINT colorRPIndex);

		
		/// <summary>
		/// ビュープロジェクション設定 (null = Default)
		/// </summary>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		void SetViewProjection(ViewProjection* pVP);
		
		/// <summary>
		/// 色設定 (null = Default)
		/// </summary>
		/// <param name="pColor"> : 色ポインタ</param>
		void SetColor(Color* pColor);

		/// <summary>
		/// ビルボード設定
		/// </summary>
		/// <param name="isXAxisBillboard"> : X軸ビルボードか</param>
		/// <param name="isYAxisBillboard"> : Y軸ビルボードか</param>
		void SetIsBillboard(bool isXAxisBillboard, bool isYAxisBillboard);
	
	private:
		
		/// <summary>
		/// ビルボード行列計算
		/// </summary>
		/// <returns>ビルボード行列</returns>
		YMath::Matrix4 BillboardMatrix();
	
#pragma region Default

	public:

		// 既定値クラス
		class Default
		{

		public:

			// ビュープロジェクションポインタ (デフォルト)
			static std::unique_ptr<ViewProjection> sVP_;
			
			// 色 (デフォルト)
			static std::unique_ptr<Color> sColor_;

		public:

			/// <summary>
			/// 静的初期化
			/// </summary>
			static void StaticInitialize();

		};

#pragma endregion

	private:
		
		Sprite3DObject() = default;
	
	public:
		
		~Sprite3DObject() = default;
	};
}

