#pragma once
#include "Vector2.h"
#include "Vector4.h"
#include <cstring>

// ウィンドウタイトル 
const wchar_t WindowTitle[20] = L"Game";

// ウィンドウサイズ 
const YMath::Vector2 WinSize = { 1280, 720 }; // (横, 縦)

// クリアカラー
const YMath::Vector4 ClearColor = { 0.1f, 0.25f, 0.5f, 0.0f }; // (RGBA)

// 固定時FPS
const float FixFPS = 60.0f;

// π
const float PI = 3.141592f;
