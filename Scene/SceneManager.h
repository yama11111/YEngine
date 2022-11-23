#pragma once
#include "SceneChanger.h"

enum class Scene
{
	TITLE,
	MOVIE,
	PLAY,
	PAUSE,
	CLEAR,
	OVER,
};

class SceneManager
{
private:
	Scene scene_ = Scene::TITLE;
	Scene next_ = Scene::MOVIE;
	bool isChange_ = false;
	SceneChanger sc_;
public:
	void Initialize(const SceneChanger::InitStatus& state);
	void Reset();
	void Update();
	void Draw();
public:
	void Change(const Scene& scene);
	Scene GetScene() { return scene_; }
	bool IsChange() { return isChange_; }
	bool IsChangeMoment() { return sc_.IsChangeMoment(); }
private:
	void Activate();
	void UpdateChange();
};

