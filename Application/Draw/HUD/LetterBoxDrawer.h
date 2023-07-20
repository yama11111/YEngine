//#pragma once
//#include "Sprite2D.h"
//#include <array>
//
//namespace YGame
//{
//	class LetterBoxDrawerCommon
//	{
//	
//	protected:
//	
//		// 静的スプライト
//		static Sprite2D* spSpr_;
//	
//	public:
//		
//		
//		/// <summary>
//		/// 静的初期化
//		/// </summary>
//		static void StaticInitialize();
//	
//	public:
//		
//		virtual ~LetterBoxDrawerCommon() = default;
//	
//	};
//
//	class LetterBoxDrawer : private LetterBoxDrawerCommon
//	{
//	
//	private:
//		
//		// スプライトオブジェクト
//		std::array<std::unique_ptr<Sprite2D::Object>, 2> sprObjs_;
//		
//		// 色
//		std::unique_ptr<CBColor> color_;
//
//		
//		// 高さ (上)
//		float topHeight_ = 0.0f;
//		
//		// 高さ (下)
//		float bottomHeight_ = 0.0f;
//	
//	public:
//		
//		/// <summary>
//		/// 初期化
//		/// </summary>
//		/// <param name="topHeight"> : 上側の高さ</param>
//		/// <param name="bottoomHeight"> : 下側の高さ</param>
//		void Initialize(const float topHeight, const float bottomHeight);
//		
//		/// <summary> 
//		/// リセット (中身だけ初期化)
//		/// </summary>
//		void Reset();
//		
//		/// <summary> 
//		/// 更新
//		/// </summary>
//		void Update();
//		
//		/// <summary>
//		/// 描画
//		/// </summary>
//		/// <param name="locaiton"> : 描画場所</param>	
//		void Draw(const DrawLocation& location);
//	
//	public:
//		
//		~LetterBoxDrawer() = default;
//	
//	};
//}