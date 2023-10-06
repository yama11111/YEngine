#pragma once
#pragma once
#include "BaseConstBuffer.h"
#include <unordered_map>

namespace YGame
{
	// 定数バッファポインタセットクラス
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
		/// <param name="cbTag"> : 定数バッファタグ</param>
		void InsertDefault(const std::string& tag);

		/// <summary>
		/// 描画コマンド
		/// </summary>
		/// <param name="tag"> : タグ</param>
		/// <param name="rpIndex"> : ルートパラメータ番号</param>
		void SetDrawCommand(const std::string& tag, const uint32_t rpIndex);

	private:

		// マップ
		std::unordered_map<std::string, BaseConstBuffer*> cbPtrMap_;
	};
}
