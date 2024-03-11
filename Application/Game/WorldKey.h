/**
 * @file WorldKey.h
 * @brief 世界のキー
 * @author Yamanaka Rui
 * @date 2024/02/17
 */

#pragma once
#include <string>
#include <vector>

// 世界のキー
enum class WorldKey : size_t
{
	eStartKey,	 // スタート
	eWorldKey,	 // プレイ世界
	eJourneyKey, // ゲートの中
	eFeverKey,	 // フィーバー世界
	eGoalKey,	 // ゴール
	eKeyNum,
};

// キーの数
static const size_t kWorldKeyNum = static_cast<size_t>(WorldKey::eKeyNum);

/// <summary>
/// キー(string型)取得
/// </summary>
/// <param name="key"> : キー</param>
/// <returns>キー(string型)</returns>
std::string WorldKeyStr(const WorldKey key);

/// <summary>
/// キー(string型)取得
/// </summary>
/// <param name="keyIdx"> : キー番号</param>
/// <returns>キー(string型)</returns>
std::string WorldKeyStr(const size_t keyIdx);

/// <summary>
/// キー配列(string型)取得
/// </summary>
/// <returns>キー配列(string型)</returns>
std::vector<WorldKey> WorldKeys();

/// <summary>
/// キー配列(string型)取得
/// </summary>
/// <returns>キー配列(string型)</returns>
std::vector<std::string> WorldKeyStrs();
