#include "SceneManager.h"

void SceneManager::Initialize()
{
	Reset();
}

void SceneManager::Reset()
{
	scene_ = Scene::TITLE;
	next_ = Scene::TUTORIAL;
	isChange_ = false;
	bo_.Initialize();
}

void SceneManager::Change(const Scene& scene)
{
	next_ = scene;
	isChange_ = true;
	Activate();
}

void SceneManager::Activate()
{
	if (next_ == Scene::PAUSE) {}

	bo_.Activate();
}

void SceneManager::UpdateChange()
{
	if (scene_ == next_ || isChange_ == false) { return; }
	if (next_ == Scene::PAUSE) {}

	if (bo_.IsChangeMoment())
	{
		scene_ = next_;
		isChange_ = false;
	}
}

void SceneManager::Update()
{
	bo_.Update();
	UpdateChange();
}

void SceneManager::Draw()
{
	bo_.Draw();
}
