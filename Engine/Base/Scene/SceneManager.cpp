#include "SceneManager.h"
#include <cassert>

using YGame::SceneManager;
using YGame::ISceneFactory;

void SceneManager::Initialize(const std::string& sceneName)
{
	assert(sceneFactory_);

	scene_.reset(sceneFactory_->CreateScene(sceneName));
	assert(scene_);

	scene_->Load();
	scene_->Initialize();

	for (auto itr = transitions_.begin(); itr != transitions_.end(); itr++)
	{
		itr->second->Initialize();
	}

	isTransition_ = false;
	nextSceneName_ = "";
	transitionName_ = "";

	isEnd_ = false;
}

void SceneManager::Finalize()
{
	if (scene_) { scene_->Finalize(); }

	sceneFactory_.reset();

	for (auto itr = transitions_.begin(); itr != transitions_.end(); itr++)
	{
		itr->second->Initialize();
	}
}

void SceneManager::Transition(const std::string& sceneName, const std::string& transitionName)
{
	if (isTransition_) { return; }

	assert(sceneFactory_);
	assert(pDescHeap_);

	isTransition_ = true;
	nextSceneName_ = sceneName;
	transitionName_ = transitionName;

	if (transitions_.contains(transitionName))
	{
		//  J ڊJ n
		transitions_[transitionName]->Reset();
		transitions_[transitionName]->Activate(60, 5);
	}
}

void SceneManager::UpdateTransition()
{
	if (isTransition_)
	{
		//  J ڂ          炷   V [   ؂ ւ 
		if (transitions_.contains(transitionName_) == false)
		{
			Change();
			return;
		}

		transitions_[transitionName_]->Update();

		//  r   Ȃ e  
		if (transitions_[transitionName_]->IsFalling()) { return; }

		if (transitions_[transitionName_]->IsChangeMoment())
		{
			Change();
		}

		if (transitions_[transitionName_]->IsEnd())
		{
			isTransition_ = false;
			nextSceneName_ = "";
			transitionName_ = "";
		}
	}
}

void SceneManager::Update()
{
	UpdateTransition();

	scene_->Update();
}

void SceneManager::Change()
{
	scene_->Finalize();
	scene_.reset();

	pDescHeap_->ClearMutableCount();

	scene_.reset(sceneFactory_->CreateScene(nextSceneName_));
	assert(scene_);

	scene_->Load();
	scene_->Initialize();
}

void SceneManager::Draw()
{
	scene_->Draw();

	if (transitions_.contains(transitionName_)) 
	{
		transitions_[transitionName_]->Draw(); 
	}
}

void SceneManager::SetSceneFactory(ISceneFactory* sceneFactory)
{
	assert(sceneFactory);
	sceneFactory_.reset(sceneFactory);
}

void SceneManager::InsertTransition(const std::string& transitionName, BaseTransition* transition)
{
	assert(transition);
	assert(transitions_.contains(transitionName) == false);

	//  X } [ g | C   ^ ɕύX
	std::unique_ptr<BaseTransition> newTransition;
	newTransition.reset(transition);

	transitions_.insert({ transitionName, std::move(newTransition) });
}

void SceneManager::SetDescriptorHeapPointer(YDX::DescriptorHeap* pDescHeap)
{
	assert(pDescHeap);
	pDescHeap_ = pDescHeap;
}

SceneManager* SceneManager::GetInstance()
{
	static SceneManager instance;
	return &instance;
}
