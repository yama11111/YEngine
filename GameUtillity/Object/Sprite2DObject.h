#pragma once
#include "Transform.h"
#include "Color.h"
#include <memory>

namespace YGame
{
	// スプライト2D用オブジェクトクラス
	class Sprite2DObject : public Transform
	{
	private:
		
		// 定数バッファデータ構造体
		struct CBData
		{
			YMath::Matrix4 matWorld_; // 3D変換行列
		};

	private:
		
		// 定数バッファ (行列)
		YDX::ConstBuffer<CBData> cBuff_;
		
		// 色ポインタ
		Color* pColor_ = nullptr;
	
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
		static Sprite2DObject* Create(const Status& status, const bool isMutable = true);
		
		/// <summary>
		/// 生成 + 初期化 (Transform以外は nullの時 デフォルトで初期化)
		/// </summary>
		/// <param name="status"> : 設定用ステータス</param>
		/// <param name="(Vector3) status.pos_"> : 位置</param>
		/// <param name="(Vector3) status.rota_"> : 回転</param>
		/// <param name="(Vector3) status.scale_"> : 大きさ</param>
		/// <param name="-------------------------------------"></param>
		/// <param name="pColor"> : 色ポインタ</param>
		/// <param name="isMutable"> : シーン遷移時に開放するか</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static Sprite2DObject* Create(const Status& status, Color* pColor, const bool isMutable = true);
	
	public:
		
		/// <summary>
		/// 描画前コマンド
		/// </summary>
		/// <param name="transformRPIndex"></param>
		/// <param name="colorRPIndex"></param>
		void SetDrawCommand(const UINT transformRPIndex, const UINT colorRPIndex);
		
		
		/// <summary>
		/// 色設定 (null = Default)
		/// </summary>
		/// <param name="pColor"> : 色ポインタ</param>
		void SetColor(Color* pColor);
	
#pragma region Common

	public:

		// コモンクラス
		class Common
		{
		public:

			// 静的射影変換行列(平行投影)
			static YMath::Matrix4 sProjection_;

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
		
		Sprite2DObject() = default;
	
	public:
		
		~Sprite2DObject() = default;
	
	};
}
