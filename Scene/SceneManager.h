#pragma once
#include "Blackout.h"

enum class Scene
{
	TITLE,
	TUTORIAL,
	PLAY,
	PAUSE,
	CLEAR,
	OVER,
};

class SceneManager
{
private:
	Scene scene_ = Scene::TITLE;
	Scene next_ = Scene::TUTORIAL;
	bool isChange_ = false;
	Transition::Blackout bo_;
public:
	void Initialize();
	void Reset();
	void Update();
	void Draw();
public:
	void Change(const Scene& scene);
	Scene GetScene() { return scene_; }
	bool IsChange() { return isChange_; }
	bool IsChangeMoment() { return bo_.IsChangeMoment(); }
private:
	void Activate();
	void UpdateChange();
};

