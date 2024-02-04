#include "ResourceLoader.h"

#include "BlackoutTransition.h"
#include "WindBlocks.h"
#include "WaveTransition.h"

#include "UILetterBox.h"
#include "UIDigit.h"

#include "UIDrawer.h"
#include "InstructionsDrawer.h"
#include "StatusDrawer.h"
#include "HPGaugeDrawer.h"
#include "SpeedLevelDrawer.h"
#include "ScoreDrawer.h"
#include "CoinCountDrawer.h"
#include "PauseDrawer.h"

#include "DefaultDrawer.h"
#include "PlayerDrawer.h"
#include "SlimeDrawer.h"
#include "CoinDrawer.h"
#include "LifeDrawer.h"
#include "MagnetDrawer.h"
#include "BlockDrawer.h"
#include "GateDrawer.h"
#include "GoalDrawer.h"
#include "CloudDrawer.h"
#include "SkydomeDrawer.h"
#include "AxisDrawer.h"
#include "CollisionDrawer.h"

#include "TitleDrawer.h"
#include "SelectDrawer.h"
#include "StageDrawer.h"
#include "StageStatusDrawer.h"
#include "BeginingDrawer.h"
#include <imgui.h>

using YGame::ResourceLoader;

void ResourceLoader::Load()
{
	// Transition
	{
		BlackoutTransition::LoadResource();
		WindBlocks::LoadResource();
		WaveTransition::LoadResource();
	}

	// DefaultUI
	{
		UILetterBox::LoadResource();
		UIDigit::LoadResource();
	}

	// UI
	{
		UIDrawer::LoadResource();
		PauseDrawer::LoadResource();
		InstructionsDrawer::LoadResource();
		StatusDrawer::LoadResource();
		HPGaugeDrawer::LoadResource();
		SpeedLevelDrawer::LoadResource();
		ScoreDrawer::LoadResource();
		CoinCountDrawer::LoadResource();
	}

	// Game
	{
		DefaultDrawer::LoadResource();
		PlayerDrawer::LoadResource();
		SlimeDrawer::LoadResource();
		CoinDrawer::LoadResource();
		LifeDrawer::LoadResource();
		MagnetDrawer::LoadResource();
		BlockDrawer::LoadResource();
		GateDrawer::LoadResource();
		GoalDrawer::LoadResource();
		SkydomeDrawer::LoadResource();
		CloudDrawer::LoadResource();
		AxisDrawer::LoadResource();
		CollisionDrawer::LoadResource();
	}

	// Scene
	{
		TitleDrawer::LoadResource();
		StageDrawer::LoadResource();
		StageStatusDrawer::LoadResource();
		SelectDrawer::LoadResource();
		BeginingDrawer::LoadResource();
	}
}

void ResourceLoader::RenderDebug()
{
	ImGui::Begin("Resource");
	
	if (ImGui::Button("Load")) 
	{
		Load(); 
	}

	ImGui::End();
}
