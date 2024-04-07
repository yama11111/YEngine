#pragma once
#include "Camera.h"

namespace YGame
{
	class GameCamera final
	{

	public:

		enum class Type
		{
			eNormal,
			ePass,
		};

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// デバッグ描画
		/// </summary>
		void DrawDebugText();

	public:

		/// <summary>
		/// タイプ変更
		/// </summary>
		/// <param name="type"> : タイプ</param>
		void ChangeType(const Type type);

		/// <summary>
		/// カメラシェイク
		/// </summary>
		/// <param name="swing"></param>
		/// <param name="dekey"></param>
		/// <param name="place"></param>
		void Shaking(const float swing, const float dekey, const float place);
	
	public:

		/// <summary>
		/// プレイヤー位置ポインタ設定
		/// </summary>
		/// <param name="pFollowPoint"> : プレイヤー位置ポインタ</param>
		void SetPlayerPosPtr(YMath::Vector3* pPlayerPos);
	
	public:
		
		/// <summary>
		/// 位置取得
		/// </summary>
		/// <returns></returns>
		YMath::Vector3 Pos() const;

		/// <summary>
		/// ビュープロジェクション取得
		/// </summary>
		/// <returns></returns>
		ViewProjection GetViewProjection() const;

	private:

		// カメラ
		Camera camera_;
		
		// 注視点
		YMath::Vector3 target_;

		// 位置の種類
		Type type_ = Type::eNormal;

		// プレイヤー位置ポインタ
		YMath::Vector3* pPlayerPos_ = nullptr;

	private:
	
		/// <summary>
		/// 位置更新
		/// </summary>
		void UpdatePos();

		/// <summary>
		/// 注視点更新
		/// </summary>
		void UpdateTarget();
	};
}
