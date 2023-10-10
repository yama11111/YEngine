#pragma once
#include "Vector2.h"
#include "MathUtil.h"
#include <cstring>

// ウィンドウタイトル 
static const wchar_t WindowTitle[20] = L"BE DASH";

// ウィンドウサイズ 
static const YMath::Vector2 WinSize = { 1280, 720 }; // (横, 縦)

// クリアカラー
static const YMath::Vector4 ClearColor = YMath::GetColor(192, 252, 229, 255); // (RGBA)

// 固定時FPS
static const float FixFPS = 60.0f;

// π
static const float kPI = 3.141592f;
