//#pragma once
//#include "Sprite2D.h"
//#include <array>
//
//namespace YGame
//{
//	class UIButtonDrawer
//	{
//
//	public:
//
//		/// <summary>
//		/// 初期化
//		/// </summary>
//		/// <param name="pButtonTex"> : ボタンテクスチャ</param>
//		/// <param name="pPressedTex"> : 押されたボタンテクスチャ</param>
//		/// <param name="pPressedTex"> : 死んだボタンテクスチャ</param>
//		void Initialize(Texture* pButtonTex, Texture* pPressedTex, Texture* pDeadTex = nullptr);
//
//		/// <summary>
//		/// 更新
//		/// </summary>
//		/// <param name="isPush"> : 押したか</param>
//		virtual void Update(const bool isPush);
//
//		/// <summary>
//		/// 描画
//		/// </summary>
//		/// <param name="pObject"> : オブジェクトポインタ</param>
//		virtual void Draw(Sprite2D::Object* pObject);
//
//	public:
//
//		/// <summary>
//		/// ボタンを殺すか
//		/// </summary>
//		void SetIsDead(const bool isDead);
//
//	public:
//
//		~UIButtonDrawer() = default;
//
//	protected:
//
//		// ボタンスプライト配列
//		std::array<Sprite2D*, 2> pButtonSpr_{};
//		
//		// デッドボタンスプライト
//		Sprite2D* pDeadButtonSpr_ = nullptr;
//
//		// 押したか
//		bool isPush_ = false;
//
//		// 押せないか
//		bool isDead_ = false;
//	};
//}
//
