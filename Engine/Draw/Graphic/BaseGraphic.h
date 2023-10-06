#pragma once
#include <unordered_map>
#include <cstdint>
#include <memory>
#include <string>

namespace YGame
{
	// グラフィックス基底クラス
	class BaseGraphic
	{

	public:
		
		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="rpIndices"> : ルートパラメータ情報 + 番号</param>
		virtual void SetDrawCommand(std::unordered_map<std::string, uint32_t>& rpIndices) = 0;

		/// <summary>
		/// 表示するか設定
		/// </summary>
		/// <param name="isVisible"> : 表示するか</param>
		void SetIsVisible(const bool isVisible) { isVisible_ = isVisible; }
	
	public:

		BaseGraphic() = default;
		
		virtual ~BaseGraphic() = default;

	protected:

		// ファイルパス
		std::string fileName_;

		// 表示するか
		bool isVisible_ = true;
	
	};
}
