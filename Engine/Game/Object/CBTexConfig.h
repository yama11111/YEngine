#pragma once
#include "ConstBuffer.h"
#include "Vector2.h"

namespace YGame
{
	class CBTexConfig
	{

	public:

		// 定数バッファデータ構造体 (テクスチャ設定)
		struct CBData
		{
			YMath::Vector2 tiling_; // タイリング値
			float pad1_;
			float pad2_;
			YMath::Vector2 offset_; // オフセット値
			float pad3_;
			float pad4_;
		};

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="tiling"> : タイリング</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isMutable"> : シーン遷移時に開放するか</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static CBTexConfig* Create(
			const YMath::Vector2& tiling = { 1.0f,1.0f },
			const YMath::Vector2& offset = { 0.0f,0.0f },
			const bool isMutable = true);

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="tiling"> : タイリング</param>
		/// <param name="offset"> : オフセット</param>
		void Initialize(
			const YMath::Vector2& tiling = { 1.0f,1.0f },
			const YMath::Vector2& offset = { 0.0f,0.0f });

		/// <summary>
		/// 描画前コマンド
		/// </summary>
		/// <param name="rootParamIndex"> : ルートパラメータ番号</param>
		void SetDrawCommand(const UINT rootParamIndex);

	public:

		/// <summary>
		/// タイリング値取得
		/// </summary>
		/// <returns>タイリング値</returns>
		YMath::Vector2 GetTiling() const { return tiling_; }


		/// <summary>
		/// タイリング値設定
		/// </summary>
		/// <param name="tiling">タイリング値</param>
		void SetTiling(const YMath::Vector2& tiling) { tiling_ = tiling; }

	public:

		/// <summary>
		/// オフセット値取得
		/// </summary>
		/// <returns>オフセット値</returns>
		YMath::Vector2 GetOffset() const { return offset_; }


		/// <summary>
		/// オフセット値設定
		/// </summary>
		/// <param name="tiling">オフセット値</param>
		void SetOffset(const YMath::Vector2& offset) { offset_ = offset; }

	private:

		CBTexConfig() = default;

	public:

		~CBTexConfig() = default;

	private:

		// 定数バッファ(色)
		YDX::ConstBuffer<CBData> cBuff_;

		// タイリング
		YMath::Vector2 tiling_ = { 1.0f,1.0f };
		
		// オフセット
		YMath::Vector2 offset_ = { 0.0f,0.0f };

	};
}

