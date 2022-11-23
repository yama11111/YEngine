#include "SceneManager.h"

void SceneManager::Initialize(const SceneChanger::InitStatus& state)
{
	sc_.Initialize(state);
	Reset();
}

void SceneManager::Reset()
{
	scene_ = Scene::TITLE;
	next_ = Scene::MOVIE;
	isChange_ = false;
	sc_.Reset();
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

	sc_.Activate();
}

void SceneManager::UpdateChange()
{
	if (scene_ == next_ || isChange_ == false) { return; }
	if (next_ == Scene::PAUSE) {}

	if (sc_.IsChangeMoment())
	{
		scene_ = next_;
		isChange_ = false;
	}
}

void SceneManager::Update()
{
	sc_.Update();
	UpdateChange();
}

void SceneManager::Draw()
{
	sc_.Draw();
}
