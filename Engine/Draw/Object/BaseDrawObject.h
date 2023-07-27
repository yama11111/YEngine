#pragma once
#include "Transform.h"
#include "ConstBufferPtrSet.h"
#include "BaseGraphic.h"

namespace YGame
{
	class BaseDrawObject
	{

	public:

		// トランスフォーム
		Transform transform_;
	
	public:
		
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="status"> : トランスフォームステータス</param>
		/// <param name="isClearWhenTransition"> : 遷移時クリアするか</param>
		virtual void Initialize(
			const Transform::Status& status = Transform::Status::Default(), 
			const bool isClearWhenTransition = true) = 0;
		
		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="status"> : トランスフォームステータス</param>
		virtual void Update(const Transform::Status& status = {}) = 0;

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="shaderTag"> : シェーダータグ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		void Draw(const std::string& shaderTag, const uint16_t drawPriority);
	
	public:

		/// <summary>
		/// ペアレント設定
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		void SetParent(Transform* pParent);
		
			/// <summary>
		/// 定数バッファポインタ挿入 
		/// (同じ種類の定数バッファが来たら入れ替える)
		/// </summary>
		/// <param name="pCBuff"> : 定数バッファポインタ</param>
		void InsertConstBuffer(BaseConstBuffer* pCBuff);

		/// <summary>
		/// 定数バッファポインタ挿入 (デフォルト)
		/// (同じ種類の定数バッファが来たら入れ替える)
		/// </summary>
		/// <param name="cbTag"> : 定数バッファタグ</param>
		void InsertDefaultConstBuffer(const std::string& cbTag);
	
	public:
		
		BaseDrawObject() = default;

		virtual ~BaseDrawObject() = default;

	protected:

		// 親
		Transform* pParent_ = nullptr;

		// 定数バッファマップ
		ConstBufferPtrSet cbPtrSet_;

		// グラフィック
		BaseGraphic* pGraphic_ = nullptr;
	
	protected:

		/// <summary>
		/// グラフィック設定
		/// </summary>
		/// <param name="pGraphic"> : グラフィックポインタ</param>
		void SetGraphic(BaseGraphic* pGraphic);
	
	};
}