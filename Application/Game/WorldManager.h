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

#include "DrawObjectForPostEffect.h"
#include "CBDiscardColor.h"
#include "GameCamera.h"

namespace YGame
{
	class WorldManager
	{

	public:

		// キー
		enum class Key : size_t
		{
			eStartKey, eWorldKey, eFeverKey, eGoalKey, eKeyNum,
		};
	
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
		void Initialize(const Key& key);

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
		/// キー設定
		/// </summary>
		/// <param name="key"> : キー</param>
		void SetWorldKey(const Key& key);

		/// <summary>
		/// ゲート位置設定
		/// </summary>
		/// <param name="key"> : キー</param>
		/// <param name="pos"> : 位置</param>
		void SetGatePos(const Key& key, const YMath::Vector3& pos);

	public:

		/// <summary>
		/// キー(string型)取得
		/// </summary>
		/// <param name="key"> : キー</param>
		/// <returns>キー(string型)</returns>
		std::string WorldKeyStr(const Key& key) const;
		
		/// <summary>
		/// 現在のキー取得
		/// </summary>
		/// <returns>現在のキー</returns>
		Key CurrentWorldKey() const;

		/// <summary>
		/// 現在のキー取得
		/// </summary>
		/// <returns>現在のキー</returns>
		std::string CurrentWorldKeyStr() const;
	
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
		Key currentWorldKey_{};

		// キーの数
		static const size_t kKeyNum = static_cast<size_t>(Key::eKeyNum);

		// カメラ
		std::array<CameraSet, kKeyNum> cameraSets_;
		
		// ゲート位置
		std::array<YMath::Vector3, kKeyNum> gatePoss_{};

		// ポストエフェクトセット
		std::array<PostEffectSet, kKeyNum> postEffects_{};

	private:

		WorldManager() = default;
		~WorldManager() = default;
		WorldManager(const WorldManager&) = delete;
		const WorldManager& operator=(const WorldManager&) = delete;
	
	};
}
