#pragma once
#include "Vector3.h"
#include "Matrix4.h"
#include "BaseConstBuffer.h"

namespace YGame
{
	class UIDigit
	{

	public:

		/// <summary>
		/// 動的インスタンス生成
		/// </summary>
		/// <param name="num"> : 数</param>
		/// <param name="pParent"> : 親行列ポインタ</param>
		/// <param name="offset"> : オフセット値</param>
		/// <param name="isClearWhenTransition"> : 遷移時クリアするか</param>
		/// <returns>動的インスタンス</returns>
		static UIDigit* Create(
			const uint32_t num, 
			YMath::Matrix4* pParent, 
			const YMath::Vector3& offset ={},
			const bool isClearWhenTransition = true);

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="num"> : 数</param>
		/// <param name="pParent"> : 親行列ポインタ</param>
		/// <param name="offset"> : オフセット値</param>
		/// <param name="isClearWhenTransition"> : 遷移時クリアするか</param>
		virtual void Initialize(
			const uint32_t num, 
			YMath::Matrix4* pParent, 
			const YMath::Vector3& offset = {},
			const bool isClearWhenTransition = true) = 0;

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update() = 0;

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="shaderTag"> : シェーダータグ</param>
		/// <param name="priority"> : 描画優先度</param>
		virtual void Draw(const std::string& shaderTag, const uint16_t priority) = 0;

		/// <summary>
		/// 定数バッファポインタ挿入 
		/// (同じ種類の定数バッファが来たら入れ替える)
		/// </summary>
		/// <param name="pCBuff"> : 定数バッファポインタ</param>
		virtual void InsertConstBuffer(BaseConstBuffer* pCB) = 0;

		/// <summary>
		/// 数字設定
		/// </summary>
		/// <param name="num"> : 数字</param>
		virtual void SetNumber(const uint32_t num) = 0;

		/// <summary>
		/// オフセット設定
		/// </summary>
		/// <param name="offset"> : オフセット値</param>
		virtual void SetOffset(const YMath::Vector3& offset) = 0;

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void StaticInitialize();
		
		/// <summary>
		/// 数字の幅取得
		/// </summary>
		/// <returns>数字の幅</returns>
		static const float StaticDigitWidth();
	
	public:

		UIDigit() = default;

		virtual ~UIDigit() = default;

	};
}
