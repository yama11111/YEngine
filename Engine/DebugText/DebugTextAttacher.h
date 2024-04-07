/**
 * @file DebugTextAttacher.h
 * @brief デバッグ描画補助クラス
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include <string>

class DebugTextAttacher
{

public:

	/// <summary>
	/// デバッグ描画
	/// </summary>
	/// <param name="isWindow"> : ウィンドウにするか</param>
	void DrawDebugText(const bool isWindow);

	/// <summary>
	/// 名前取得
	/// </summary>
	/// <returns>名前</returns>
	std::string Name() const { return name_; }

	/// <summary>
	/// 名前変更
	/// </summary>
	/// <param name="name"> : 名前</param>
	void SetName(const std::string& name);

protected:

	/// <summary>
	/// デバッグテキスト本文
	/// </summary>
	virtual void DrawDebugTextContent() = 0;

protected:

	// 識別名
	std::string name_;

};

