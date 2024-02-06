#pragma once
#include "BaseDrawer.h"
#include "CBOutline.h"

namespace YGame
{
    class BlockDrawer final :
		public BaseDrawer
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="pParentWorldPos"> : 親ワールド座標ポインタ</param>
		/// <param name="isBackground"> : 背景フラグ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		/// <returns>プレイヤー描画クラスポインタ (動的インスタンス)</returns>
		static std::unique_ptr<BlockDrawer> Create(
			Transform* pParent,
			YMath::Vector3* pParentWorldPos,
			const bool isBackground,
			const size_t drawPriority);

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void LoadResource();

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="pParentWorldPos"> : 親ワールド座標ポインタ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		void Initialize(
			Transform* pParent,
			YMath::Vector3* pParentWorldPos,
			const size_t drawPriority) override;

	public:

		BlockDrawer() = default;

		~BlockDrawer() = default;

	private:
		
		std::unique_ptr<ConstBufferObject<CBOutline>> cbOutline_;

	private:

		/// <summary>
		/// オブジェクト初期化
		/// </summary>
		void InitializeObjects() override;
    };
}
