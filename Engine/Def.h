#pragma once
#include "Vector2.h"
#include "Vector4.h"
#include <cstring>

// ウィンドウタイトル 
static const wchar_t WindowTitle[20] = L"BeDash";

// ウィンドウサイズ 
static const YMath::Vector2 WinSize = { 1280, 720 }; // (横, 縦)

// クリアカラー
static const YMath::Vector4 ClearColor = { 0.1f, 0.25f, 0.5f, 0.0f }; // (RGBA)

// 固定時FPS
static const float FixFPS = 60.0f;

// π
static const float kPI = 3.141592f;
