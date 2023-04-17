#pragma once
#include "Vector2.h"
#include "Vector4.h"
#include <cstring>

// �E�B���h�E�^�C�g�� 
const wchar_t WindowTitle[20] = L"Game";

// �E�B���h�E�T�C�Y 
const YMath::Vector2 WinSize = { 1280, 720 }; // (��, �c)

// �N���A�J���[
const YMath::Vector4 ClearColor = { 0.1f, 0.25f, 0.5f, 0.0f }; // (RGBA)

// �Œ莞FPS
const float FixFPS = 60.0f;

// ��
const float PI = 3.141592f;

//���a
const float harfScale = 1.0f;