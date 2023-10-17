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

		/// <summary>
		/// 種類タグ取得
		/// </summary>
		/// <returns>種類タグ</returns>
		const std::string TypeTag() const { return typeTag_; }

	public:

		BaseGraphic() = delete;
		
		BaseGraphic(const std::string& typeTag);
		
		virtual ~BaseGraphic() = default;
	
	public:
		
		/// <summary>
		/// 派生クラスを比較
		/// </summary>
		/// <param name="other"> : 相手のクラス</param>
		/// <returns>同じクラスなら true</returns>
		bool operator==(const BaseGraphic& other) const;

	protected:

		// ファイルパス
		std::string fileName_;
		
		// 種類タグ
		std::string typeTag_;

		// 表示するか
		bool isVisible_ = true;
	
	};
}
