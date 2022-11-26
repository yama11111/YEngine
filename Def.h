#pragma once
#include "Vec2.h"
#include "Vec4.h"

// ウィンドウタイトル
const wchar_t* Title = L"YEngine";

// ウィンドウサイズ 
const Math::Vec2 WinSize = { 1280, 720 }; // (横, 縦)

// クリアカラー
const Math::Vec4 ClearColor = { 0.1f, 0.25f, 0.5f, 0.0f }; // (RGBA)

// 固定時FPS
const float FixFPS = 60.0f;