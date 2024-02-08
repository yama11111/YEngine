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
		/// <param name="init"> : 初期化セット</param>
		/// <param name="isBackground"> : 背景フラグ</param>
		/// <returns>プレイヤー描画クラスポインタ (動的インスタンス)</returns>
		static std::unique_ptr<BlockDrawer> Create(const DrawerInitSet& init, const bool isBackground);

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void LoadResource();

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="init"> : 初期化セット</param>
		void Initialize(const DrawerInitSet& init) override;

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
