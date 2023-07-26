#pragma once
#include "BaseConstBuffer.h"
#include "BaseGraphic.h"

namespace YGame
{
	class Object
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		void Clear();

	public:

		/// <summary>
		/// 定数バッファポインタ取得
		/// </summary>
		/// <returns>定数バッファポインタ</returns>
		YDX::BaseConstBuffer* ConstBufferPtr(const std::string& key);

		/// <summary>
		/// グラフィックポインタ
		/// </summary>
		/// <returns></returns>
		BaseGraphic* GraphicPtr() const;

	public:

		/// <summary>
		/// 定数バッファ挿入 
		/// (同じ種類の定数バッファが来たら入れ替える)
		/// </summary>
		/// <param name="pCBuff"> : 定数バッファポインタ</param>
		void InsertConstBuffer(YDX::BaseConstBuffer* pCBuff);

		/// <summary>
		/// グラフィック設定
		/// </summary>
		/// <param name="pGraphic"> : グラフィックポインタ</param>
		void SetGraphic(BaseGraphic* pGraphic);

	protected:

		// 定数バッファマップ
		std::unordered_map<std::string, YDX::BaseConstBuffer*> cbPtrMap_;

		// グラフィック
		BaseGraphic* pGraphic_ = nullptr;
	};
}
