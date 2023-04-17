#include "BaseScene.h"
#include <cassert>

#pragma region 名前空間宣言

using YScene::BaseScene;
using YInput::Keys;
using YInput::Mouse;
using YInput::Pad;
using YGame::Texture;
using YGame::Audio;
using YGame::WorldRuler;
using YGame::ViewProjection;
using YGame::LightGroup;
using YGame::Sprite2DObject;
using YGame::Sprite3DObject;
using YGame::ModelObject;

#pragma endregion 

#pragma region Static

Keys* BaseScene::sKeys_ = nullptr;
Mouse* BaseScene::sMouse_ = nullptr;
Pad* BaseScene::sPad_ = nullptr;
WorldRuler* BaseScene::spWorldRuler_ = nullptr;

void BaseScene::StaticInitialize(YGame::WorldRuler* pWorldRuler)
{
	// nullチェック
	assert(pWorldRuler);

	// シングルトン初期化
	sKeys_ = Keys::GetInstance();
	sMouse_ = Mouse::GetInstance();
	sPad_ = Pad::GetInstance();
	
	// ポインタ代入
	spWorldRuler_ = pWorldRuler;
}

#pragma endregion 