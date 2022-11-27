#pragma once
#include "Vec2.h"
#include "Vec4.h"
#include <cstring>

// �E�B���h�E�^�C�g�� 
const wchar_t WindowTitle[20] = L"Game";

// �E�B���h�E�T�C�Y 
const Math::Vec2 WinSize = { 1280, 720 }; // (��, �c)

// �N���A�J���[
const Math::Vec4 ClearColor = { 0.1f, 0.25f, 0.5f, 0.0f }; // (RGBA)

// �Œ莞FPS
const float FixFPS = 60.0f;