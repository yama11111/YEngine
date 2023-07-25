#include "PipelineManager.h"
#include <cassert>

using YGame::PipelineManager;

PipelineManager* PipelineManager::GetInstance()
{
    static PipelineManager instance;

    return &instance;
}

void PipelineManager::Clear()
{
	pipelines_.clear();
	drawOrder_.clear();
}

void PipelineManager::Insert(const std::string& key, Pipeline* pipeline)
{
	assert(pipeline);

	std::unique_ptr<Pipeline> newPipeline;

	newPipeline.reset(pipeline);

	pipelines_.insert({ key, std::move(newPipeline) });

	// 標準では挿入順に描画されるように
	drawOrder_.push_back(key);
}

void PipelineManager::SetDrawOrder(const std::vector<std::string> pipelineKeys)
{
	drawOrder_ = pipelineKeys;
}

void PipelineManager::EnqueueDrawSet(const std::string& pipelineName, const uint32_t priority, Object* pObj)
{
	auto pipeline = pipelines_.find(pipelineName);
	
	// パイプラインが無かったら弾く
	if (pipeline == pipelines_.end()) { return; }

	pipeline->second->EnqueueDrawSet(priority, pObj);
}

void PipelineManager::RenderToPostEffect(std::vector<PostEffect*> pPostEffects)
{
	for (size_t i = 0; i < pPostEffects.size(); i++)
	{
		pPostEffects[i]->StartRender();
	}
	
	Draw();
	
	for (size_t i = 0; i < pPostEffects.size(); i++)
	{
		pPostEffects[i]->EndRender();
	}
}

void PipelineManager::Draw()
{
	for (size_t i = 0; i < drawOrder_.size(); i++)
	{
		auto pipeline = pipelines_.find(drawOrder_[i]);

		// パイプラインが無かったら次
		if (pipeline == pipelines_.end()) { continue; }

		pipeline->second->Draw();
	}
}