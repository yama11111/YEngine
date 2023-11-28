//#pragma once
//#include "IDrawerFactory.h"
//
//namespace YGame
//{
//	class YGameDrawerFactory :
//		public IDrawerFactory
//	{
//
//	public:
//
//		// プレイヤー
//		static const std::string Player_;
//
//		// ウマ
//		static const std::string Horse_;
//
//		// スライム
//		static const std::string Slime_;
//
//		// コイン
//		static const std::string Coin_;
//
//		// 磁石
//		static const std::string Magnet_;
//
//		// ライフ
//		static const std::string Life_;
//
//		// 標準
//		static const std::string Default_;
//
//	public:
//
//		/// <summary> 
//		/// 描画クラス生成
//		/// </summary>
//		/// <param name="drawerName"> : 名前</param>
//		/// <param name="pParent"> : 親ポインタ</param>
//		/// <param name="drawPriority"> : 描画優先度</param>
//		/// <returns>描画クラス</returns>
//		virtual std::unique_ptr<BaseDrawer> CreateDrawer(
//			const std::string& drawerName, Transform* pParent, const size_t drawPriority) override;
//
//	};
//}
