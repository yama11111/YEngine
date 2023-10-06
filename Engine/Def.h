#pragma once
#include "Vector2.h"
#include "Vector4.h"
#include <cstring>

// �E�B���h�E�^�C�g�� 
static const wchar_t WindowTitle[20] = L"BeDash";

// �E�B���h�E�T�C�Y 
static const YMath::Vector2 WinSize = { 1280, 720 }; // (��, �c)

// �N���A�J���[
static const YMath::Vector4 ClearColor = { 0.1f, 0.25f, 0.5f, 0.0f }; // (RGBA)

// �Œ莞FPS
static const float FixFPS = 60.0f;

// ��
static const float kPI = 3.141592f;
