/**
 * @file ConstBufferPtrSet.h
 * @brief 定数バッファポインタセットクラス
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include "BaseConstBuffer.h"
#include <unordered_map>

namespace YGame
{
	// 定数バッファポインタセット
	class ConstBufferPtrSet final
	{

	public:

		/// <summary>
		/// クリア
		/// </summary>
		void Clear();

		/// <summary>
		/// 定数バッファポインタ挿入 
		/// (同じ種類の定数バッファが来たら入れ替える)
		/// </summary>
		/// <param name="pCBuff"> : 定数バッファポインタ</param>
		void Insert(BaseConstBuffer* pCB);
		
		/// <summary>
		/// 定数バッファポインタ挿入 (デフォルト)
		/// (同じ種類の定数バッファが来たら入れ替える)
		/// </summary>
		/// <param name="cbTag"> : タグ</param>
		void InsertDefault(const std::string& tag);

		/// <summary>
		/// 描画コマンド
		/// </summary>
		/// <param name="tag"> : タグ</param>
		/// <param name="rpIndex"> : ルートパラメータ番号</param>
		void SetDrawCommand(const std::string& tag, const uint32_t rpIndex);

	public:

		ConstBufferPtrSet() = default;
		
		~ConstBufferPtrSet() = default;
	
	private:

		// マップ
		std::unordered_map<std::string, BaseConstBuffer*> cbPtrMap_;
	};
}
