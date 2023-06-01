#pragma once
#include "IParticle.h"
#include <list>

namespace YGame
{
	// パーティクルマネージャー
	class ParticleManager
	{
	
	private:
		
		// パーティクルリスト
		std::list<std::unique_ptr<IParticle>> particles_;
	
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
		/// 描画
		/// </summary>
		void Draw();
	
	public:
		
		/// <summary>
		/// 煙発生
		/// </summary>
		/// <param name="emitNum"> : 数</param>
		/// <param name="aliveTime"> : 生存時間</param>
		/// <param name="center"> : 中心</param>
		/// <param name="range"> : 範囲</param>
		/// <param name="minScale"> : 最小スケール</param>
		/// <param name="maxScale"> : 最大スケール</param>
		/// <param name="minMoveSpeed"> : 最小移動スピード</param>
		/// <param name="maxMoveSpeed"> : 最大移動スピード</param>
		/// <param name="minRotaSpeed"> : 最小回転スピード</param>
		/// <param name="maxRotaSpeed"> : 最大回転スピード</param>
		/// <param name="color"> : 色</param>
		/// <param name="place"> : 小数点をどの位まで扱うか</param>
		/// <param name="locaiton"> : 描画場所</param>
		void EmitSmoke(
			const size_t& emitNum,
			const uint32_t& aliveTime,
			const YMath::Vector3& center, const YMath::Vector3& range,
			const float& minScale, const float& maxScale,
			const YMath::Vector3& minMoveSpeed, const YMath::Vector3& maxMoveSpeed,
			const YMath::Vector3& minRotaSpeed, const YMath::Vector3& maxRotaSpeed,
			const YMath::Vector3& color,
			const float& place, 
			const DrawLocation& location);

		/// <summary>
		/// リレー虫発生
		/// </summary>
		/// <param name="emitNum"> : 数</param>
		/// <param name="startToRelayFrame"> : 開始地点 から 中継地点 までの時間</param>
		/// <param name="relayToEndFrame"> : 中継地点 から 終了地点 までの時間</param>
		/// <param name="start"> : 開始地点</param>
		/// <param name="end"> : 終了地点</param>
		/// <param name="relayRange"> : 中継地点範囲</param>
		/// <param name="rota"> : 回転</param>
		/// <param name="scale"> : 大きさ</param>
		/// <param name="color"> : 色</param>
		/// <param name="place"> : 小数点をどの位まで扱うか</param>
		/// <param name="locaiton"> : 描画場所</param>		
		void EmitRelayBug(
			const size_t& emitNum,
			const uint32_t& startToRelayFrame, const uint32_t& relayToEndFrame,
			const YMath::Vector3& start, const YMath::Vector3& end,
			const YMath::Vector3& relayRange,
			const YMath::Vector3& minRota, const YMath::Vector3& maxRota,
			const float& minScale, const float& maxScale,
			const YMath::Vector3& color,
			const float& place, 
			const DrawLocation& location);

		/// <summary>
		/// 泡文字発生
		/// </summary>
		/// <param name="emitNum"> : 発生数</param>
		/// <param name="aliveFrame"> : 生存時間</param>
		/// <param name="center"> : 中心</param>
		/// <param name="range"> : 範囲</param>
		/// <param name="minScale"> : 最小スケール</param>
		/// <param name="maxScale"> : 最大スケール</param>
		/// <param name="minMoveSpeed"> : 最小移動スピード</param>
		/// <param name="maxMoveSpeed"> : 最大移動スピード</param>
		/// <param name="minRotaSpeed"> : 最小回転スピード</param>
		/// <param name="maxRotaSpeed"> : 最大回転スピード</param>
		/// <param name="color"> : 色</param>
		/// <param name="place"> : 小数点をどの位まで扱うか</param>
		/// <param name="locaiton"> : 描画場所</param>		
		void EmitBubbleCharacter(
			const size_t& emitNum,
			const uint32_t& aliveFrame,
			const YMath::Vector3& center, const YMath::Vector3& range,
			const float& minScale, const float& maxScale,
			const YMath::Vector3& minMoveSpeed, const YMath::Vector3& maxMoveSpeed,
			const YMath::Vector3& minRotaSpeed, const YMath::Vector3& maxRotaSpeed,
			const YMath::Vector3& color,
			const float& place, 
			const DrawLocation& location);

	private:

		// 静的グリッドモデル
		static Model* spGridModel_;
		
		// 静的文字スプライト3D
		static Sprite3D* spCharacterSprite3D_;
	
	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		static void StaticInitialize(ViewProjection* pVP);
	
	public:
		
		~ParticleManager() = default;
	};
}

