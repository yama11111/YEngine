#pragma once
#include "Lerp.h"
#include "Power.h"
#include "Sprite.h"

class SceneChanger
{
private:
	enum class Step
	{
		BlackOut,
		Load,
		BrightTurn,
	};
private:
	Game::Transform curten_;
	Step step_ = Step::BlackOut;
	bool isAct_ = false;
	bool isChangeMoment_ = false;
	int count = 0;

	Math::Ease<float> blendE_;
	Math::Power blendP_;

	UINT plainT_;
	Game::Sprite* curtenS_ = nullptr;
public:
	struct InitStatus
	{
		Game::Sprite* curtenS_;
		UINT plainTex_;
	};
public:
	void Initialize(const InitStatus& state);
	void Reset();
	void Activate();
	void Update();
	void Draw();
public:
	void ChangeUpdate();
	void BlendUpdate();
	bool IsChangeMoment() { return isChangeMoment_; }
};
