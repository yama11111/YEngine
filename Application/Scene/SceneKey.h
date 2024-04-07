/**
 * @file SceneKey.h
 * @brief シーンキー
 * @author Yamanaka Rui
 * @date 2024/02/17
 */

#pragma once
#include <string>
#include <vector>

namespace YGame
{
	// シーンキー
	enum class SceneKey : size_t
	{
		eTitleKey,	 // タイトル
		eSelectKey,	 // セレクト
		ePlayKey, // プレイ
		eResultKey,	 // リザルト
		eTestKey,	 // テスト
		eKeyNum,
	};

	// キーの数
	static const size_t kSceneKeyNum = static_cast<size_t>(SceneKey::eKeyNum);

	/// <summary>
	/// キー(string型)取得
	/// </summary>
	/// <param name="key"> : キー</param>
	/// <returns>キー(string型)</returns>
	std::string SceneKeyStr(const SceneKey key);

	/// <summary>
	/// キー(string型)取得
	/// </summary>
	/// <param name="keyIdx"> : キー番号</param>
	/// <returns>キー(string型)</returns>
	std::string SceneKeyStr(const size_t keyIdx);

	/// <summary>
	/// キー配列(string型)取得
	/// </summary>
	/// <returns>キー配列(string型)</returns>
	std::vector<std::string> SceneKeyStrs();
}
