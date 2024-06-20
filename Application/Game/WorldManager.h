/**
 * @file WorldManager.h
 * @brief 世界管理クラス
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include "Vector3.h"
#include <string>
#include <array>
#include <unordered_map>

#include "WorldKey.h"
#include "DrawObjectForPostEffect.h"
#include "CBDiscardColor.h"
#include "GameCamera.h"

namespace YGame
{
	class WorldManager
	{
	
	public:

		/// <summary>
		/// シングルトン
		/// </summary>
		/// <returns></returns>
		static WorldManager* GetInstance();
	
	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="key"> : キー</param>
		void Initialize(const WorldKey& key);

		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="isControlUpdate"> : 操作更新フラグ</param>
		void Update(const bool isControlUpdate);

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();

		/// <summary>
		/// デバッグ描画
		/// </summary>
		void DrawDebug();
	
	public:

		/// <summary>
		/// 世界を移動する
		/// </summary>
		/// <returns>ゲート位置</returns>
		YMath::Vector3 Pass();

		/// <summary>
		/// ゲームオーバー
		/// </summary>
		void GameOver();

		/// <summary>
		/// ステージクリア
		/// </summary>
		void ClearStage();
		
	public:

		/// <summary>
		/// キー設定
		/// </summary>
		/// <param name="key"> : キー</param>
		void SetWorldKey(const WorldKey& key);
		
		/// <summary>
		/// 基底行列設定
		/// </summary>
		/// <param name="key"> : キー</param>
		/// <param name="mat"> ; 行列</param>
		void SetBaseMat(const WorldKey& key, const YMath::Matrix4& mat);

		/// <summary>
		/// ゲート位置設定
		/// </summary>
		/// <param name="key"> : キー</param>
		/// <param name="pos"> : 位置</param>
		void SetGatePos(const WorldKey& key, const YMath::Vector3& pos);

		/// <summary>
		/// ゲート位置設定
		/// </summary>
		/// <param name="key"> : キー</param>
		/// <param name="pos"> : 位置</param>
		void SetGatePos(const std::string& key, const YMath::Vector3& pos);

	public:
		
		/// <summary>
		/// 現在のキー取得
		/// </summary>
		/// <returns>現在のキー</returns>
		WorldKey CurrentWorldKey() const;
		
		/// <summary>
		/// 基準の行列のポインタ取得
		/// </summary>
		/// <param name="key"> : キー</param>
		/// <returns>基準の行列のポインタ</returns>
		YMath::Matrix4 BasePosMat(const WorldKey& key);

		/// <summary>
		/// 基準の行列のポインタ取得
		/// </summary>
		/// <param name="key"> : キー</param>
		/// <returns>基準の行列のポインタ</returns>
		YMath::Matrix4* BasePosMatPointer(const WorldKey& key);

		void SetIsPlayerLanding(const bool isLanding) { isPlayerLanding_ = isLanding; }
		bool IsPlayerLanding()const { return isPlayerLanding_; }
	
	private:

		// ポストエフェクトセット
		struct PostEffectSet
		{
			// ポストエフェクト
			PostEffect* pPE = nullptr;
			
			// オブジェクト
			std::unique_ptr<DrawObjectForPostEffect> obj;
			
			// 定数バッファ
			std::unique_ptr<ConstBufferObject<CBDiscardColor>> cbDiscardColor;
			
			// 優先度
			size_t priority = 0;

			// 描画フラグ
			bool isDraw = true;
		};

		struct CameraSet
		{
			// カメラ
			GameCamera camera;

			// 転送用
			ViewProjection transferVP;
		};

	private:

		// 現在世界キー
		WorldKey currentWorldKey_{};
		
		// 過去世界キー
		WorldKey elderWorldKey_{};

		// 基準の行列
		std::unordered_map<WorldKey, YMath::Matrix4> basePosMatMap_;

		// カメラ位置
		CameraSet cameraSet_;

		// ゲート位置
		std::array<YMath::Vector3, kWorldKeyNum> gatePoss_{};

		// ポストエフェクトセット
		std::unordered_map<WorldKey, PostEffectSet> postEffects_{};

		// 描画キー
		std::vector<WorldKey> drawKeys_;

		// フィーバーパーティクル用タイマー
		YMath::Timer feverEmitTimer_;

		bool isPlayerLanding_ = false;

	private:

		/// <summary>
		/// フィーバー更新
		/// </summary>
		void UpdateFever();
	
	private:

		WorldManager() = default;
		~WorldManager() = default;
		WorldManager(const WorldManager&) = delete;
		const WorldManager& operator=(const WorldManager&) = delete;
	
	};
}
