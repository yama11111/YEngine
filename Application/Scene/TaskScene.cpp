#include "TaskScene.h"
#include "SceneExecutive.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#include "MathVector.h"

#pragma region ���O��Ԑ錾

using YScene::TaskScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;

#pragma endregion 


#pragma region Static�֘A

#pragma endregion 


#pragma region �ǂݍ���
void TaskScene::Load()
{
}
#pragma endregion


#pragma region ������
void TaskScene::Initialize()
{
	smoke_.Initialize({ {},{},{20.0f,20.0f,20.0f} });

	floor_.Initialize({ {640.0f,360.0f,0.0f}, {}, {0.5f,0.5f,0.5f} });

	vp_.Initialize({ {-80, 40, -80}, {+60, -40, +60}, {0,1,0} });
}
#pragma endregion


#pragma region �I������
void TaskScene::Finalize()
{
}
#pragma endregion


#pragma region �X�V
void TaskScene::Update()
{
	if (spKeys_->IsTrigger(DIK_SPACE))
	{
		a++;
		if (a > 1)
		{
			a = 0;
		}
	}

	smoke_.Update(vp_);

	floor_.Update();
}
#pragma endregion


#pragma region �`��
void TaskScene::Draw()
{
	if (a == 0)
	{
		floor_.Draw("Sprite2DTextureBlend");
	}

	if (a == 1)
	{
		smoke_.Draw("ModelDissolveBack", 0);
		smoke_.Draw("ModelDissolveFront", 1);
	}

}
#pragma endregion
