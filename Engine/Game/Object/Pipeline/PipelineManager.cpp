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
}

void PipelineManager::Insert(const std::string& key, Pipeline* pipeline)
{
	assert(pipeline);

	std::unique_ptr<Pipeline> newPipeline;

	newPipeline.reset(pipeline);

	pipelines_.insert({ key, std::move(newPipeline) });
}

void PipelineManager::EnqueueDrawSet(const std::string& pipelineName, const uint32_t priority, Object* pObj)
{
	auto pipeline = pipelines_.find(pipelineName);
	
	// パイプラインが無かったら弾く
	if (pipeline == pipelines_.end()) { return; }

	pipeline->second->EnqueueDrawSet(priority, pObj);
}

void PipelineManager::Draw(const std::string& key)
{
	auto pipeline = pipelines_.find(key);

	// パイプラインが無かったら弾く
	if (pipeline == pipelines_.end()) { return; }

	pipeline->second->Draw();
}
