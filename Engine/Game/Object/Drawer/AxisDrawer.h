#pragma once
#include "BaseDrawer.h"

namespace YGame
{
	class AxisDrawer final :
		public BaseDrawer
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="init"> : 初期化セット</param>
		/// <returns>プレイヤー描画クラスポインタ (動的インスタンス)</returns>
		static std::unique_ptr<AxisDrawer> Create(const DrawerInitSet& init);

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void LoadResource();

		/// <summary>
		/// 名前取得
		/// </summary>
		/// <returns>名前</returns>
		static std::string Name();

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="init"> : 初期化セット</param>
		void Initialize(const DrawerInitSet& init) override;

	public:

		AxisDrawer() = default;

		~AxisDrawer() = default;

	private:

		// 色定数バッファ
		std::array<std::unique_ptr<ConstBufferObject<CBColor>>, 3> cbColors_;

	private:

		/// <summary>
		/// オブジェクト初期化
		/// </summary>
		void InitializeObjects() override;
	};
}
