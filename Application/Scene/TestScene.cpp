#include "TestScene.h"
#include "SceneManager.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#pragma region 名前空間宣言

using YGame::TestScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;

#pragma endregion 

#pragma region Static関連
namespace
{
	Sprite2D* pCircleSpr = nullptr;
	Sprite2D* pBoxSpr = nullptr;
	Sprite2D* pTriangleSpr = nullptr;
}
#pragma endregion 


#pragma region 読み込み
void TestScene::Load()
{
	pCircleSpr = Sprite2D::Create({ { "Texture0", Texture::Load("converted/circle.dds") } });
	pBoxSpr = Sprite2D::Create({ { "Texture0", Texture::Load("converted/box.dds") } });
	pTriangleSpr = Sprite2D::Create({ { "Texture0", Texture::Load("converted/triangle.dds") } });
}
#pragma endregion


#pragma region 初期化
void TestScene::Initialize()
{
	circle_.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), pCircleSpr));
	box_.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), pBoxSpr));
	triangle_.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), pTriangleSpr));

	circle_->transform_.pos_	 = Vector3(+96.0f, WinSize.y_ / 2.0f, 0.0f);
	box_->transform_.pos_		 = Vector3(WinSize.x_ / 2.0f, WinSize.y_ / 2.0f, 0.0f);
	triangle_->transform_.pos_	 = Vector3(WinSize.x_ - 96.0f, WinSize.y_ / 2.0f, 0.0f);
}
#pragma endregion


#pragma region 終了処理
void TestScene::Finalize()
{
}
#pragma endregion


#pragma region 更新
void TestScene::Update()
{
	circle_->Update();
	box_->Update();
	triangle_->Update();
}
#pragma endregion


#pragma region 描画
void TestScene::Draw()
{
	circle_->Draw("Sprite2DDefault", 1);
	box_->Draw("Sprite2DDefault", 1);
	triangle_->Draw("Sprite2DDefault", 1);
}
#pragma endregion