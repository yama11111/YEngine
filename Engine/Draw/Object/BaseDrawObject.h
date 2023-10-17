#pragma once
#include "Transform.h"
#include "ConstBufferPtrSet.h"
#include "BaseGraphic.h"

namespace YGame
{
	// 基底描画オブジェクト
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
		void Draw();

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="shaderTag"> : シェーダータグ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		void Draw(const std::string& shaderTag, const size_t drawPriority);

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="shaderTag"> : シェーダータグ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		void Draw(const std::string& shaderTag, const size_t drawPriority, BaseGraphic* pGraphic);
	
	public:

		/// <summary>
		/// ペアレント設定
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		void SetParent(YMath::Matrix4* pParent);
		
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

		/// <summary>
		/// グラフィック設定
		/// </summary>
		/// <param name="pGraphic"> : グラフィックポインタ</param>
		virtual void SetGraphic(BaseGraphic* pGraphic) = 0;

		/// <summary>
		/// シェーダータグ設定
		/// </summary>
		/// <param name="shaderTag"> : シェーダータグ</param>
		void SetShaderTag(const std::string& shaderTag) { shaderTag_ = shaderTag; }

		/// <summary>
		/// 描画位置設定
		/// </summary>
		/// <param name="drawPriority"> : 描画優先度</param>
		void SetDrawPriority(const size_t drawPriority) { drawPriority_ = drawPriority; }

		/// <summary>
		/// 描画するか設定
		/// </summary>
		/// <param name="isVisible">描画フラグ</param>
		void SetIsVisible(const bool isVisible) { isVisible_ = isVisible; }
	
	public:
		
		BaseDrawObject() = default;

		virtual ~BaseDrawObject() = default;

	protected:

		// 定数バッファマップ
		ConstBufferPtrSet cbPtrSet_;

		// グラフィック
		BaseGraphic* pGraphic_ = nullptr;

		// シェーダータグ
		std::string shaderTag_ = "";

		// 描画位置
		size_t drawPriority_ = 0;

		// 描画するか
		bool isVisible_ = true;
	
	};
}