#pragma once
#include "Transform.h"
#include "ViewProjection.h"
#include "LightGroup.h"
#include "Color.h"
#include <memory>

namespace YGame
{
	// モデル用オブジェクトクラス
	class ModelObject : public Transform
	{
	private:

		// 定数バッファデータ構造体
		struct CBData
		{
			YMath::Matrix4 matWorld_;	 // ワールド行列
			YMath::Matrix4 matViewProj_; // ビュープロジェクション行列
			YMath::Vector3 cameraPos_;	 // カメラ座標
		};

	private:
		
		// 定数バッファ
		YDX::ConstBuffer<CBData> cBuff_;
		
		// ビュープロジェクションポインタ
		ViewProjection* pVP_ = nullptr;
		
		// 色ポインタ
		Color* pColor_ = nullptr;
		
		// 光源ポインタ
		LightGroup* pLightGroup_ = nullptr;
	
	public:
		
		/// <summary>
		/// 生成 + 初期化 (デフォルト初期化)
		/// </summary>
		/// <param name="status"> : 設定用ステータス</param>
		/// <param name="(Vector3) status.pos_"> : 位置</param>
		/// <param name="(Vector3) status.rota_"> : 回転</param>
		/// <param name="(Vector3) status.scale_"> : 大きさ</param>
		/// <param name="isMutable"> : シーン遷移時に開放するか</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static ModelObject* Create(const Status& status, const bool isMutable = true);
		
		/// <summary>
		/// 生成 + 初期化 (Transform以外は nullの時 デフォルトで初期化)
		/// </summary>
		/// <param name="status"> : 設定用ステータス</param>
		/// <param name="(Vector3) status.pos_"> : 位置</param>
		/// <param name="(Vector3) status.rota_"> : 回転</param>
		/// <param name="(Vector3) status.scale_"> : 大きさ</param>
		/// <param name="-------------------------------------"></param>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		/// <param name="pColor"> : 色ポインタ</param>
		/// <param name="pLightGroup"> : 光源ポインタ</param>
		/// <param name="isMutable"> : シーン遷移時に開放するか</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static ModelObject* Create(const Status& status, ViewProjection* pVP, Color* pColor, LightGroup* pLightGroup, 
			const bool isMutable = true);
	
	public:
		
		/// <summary>
		/// 描画前コマンド
		/// </summary>
		/// <param name="transformRPIndex"></param>
		/// <param name="colorRPIndex"></param>
		/// <param name="lightRPIndex"></param>
		void SetDrawCommand(const UINT transformRPIndex, const UINT colorRPIndex, const UINT lightRPIndex);
		

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
		/// 光源設定 (null = Default)
		/// </summary>
		/// <param name="pLightGroup"> : 光源ポインタ</param>
		void SetLightGroup(LightGroup* pLightGroup);
	
#pragma region Common

	public:

		// コモンクラス
		class Common
		{
		public:

			// ビュープロジェクションポインタ (デフォルト)
			static std::unique_ptr<ViewProjection> sDefVP_;
			
			// 光源ポインタ (デフォルト)
			static std::unique_ptr<LightGroup> sDefLightGroup_;
			
			// 色 (デフォルト)
			static std::unique_ptr<Color> sDefColor_;

		public:

			/// <summary>
			/// 静的初期化
			/// </summary>
			static void StaticInitialize();

		};

	private:

		// コモン
		static Common common_;

#pragma endregion

	private:
	
		ModelObject() = default;

	public:
		
		~ModelObject() = default;
	
	};
}

