#pragma once
#include <cstdint>
#include <string>

namespace YGame
{
	class BaseConstBuffer
	{

	public:
		
		/// <summary>
		/// 定数バッファの生成 + マッピング
		/// </summary>
		/// <param name="pCBData"> : 定数バッファデータポインタ</param>
		/// <param name="isMutable"> : リセットするか</param>
		template<typename CBData>
		static BaseConstBuffer* Create(CBData* pCBData, const bool isMutable = true);

	public:

		/// <summary>
		/// 描画前コマンド
		/// </summary>
		/// <param name="rootParamIndex"> : ルートパラメータ番号</param>
		virtual void SetDrawCommand(const uint32_t rootParamIndex) = 0;
		
		/// <summary>
		/// キーの名前取得
		/// </summary>
		/// <returns>キーの名前</returns>
		virtual const std::string KeyName() const = 0;
	
	public:
	
		virtual ~BaseConstBuffer() = default;
	
	protected:

		/// <summary>
		/// コンストラクタ (通常の宣言を禁止する)
		/// </summary>
		BaseConstBuffer() = default;

	};
}
