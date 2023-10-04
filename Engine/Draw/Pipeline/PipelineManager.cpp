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
	if (pipelines_.empty()) { return; }
	pipelines_.clear();
	
	if (drawOrder_.empty()) { return; }
	drawOrder_.clear();
}

void PipelineManager::Insert(const std::string& key, Pipeline* pipeline)
{
	assert(pipeline);
	assert(pipelines_.contains(key) == false);

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

void PipelineManager::EnqueueDrawSet(const std::string& key, const size_t priority, const Pipeline::DrawSet& drawSet)
{
	assert(pipelines_.contains(key));

	pipelines_[key]->EnqueueDrawSet(priority, drawSet);
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
		// パイプラインが無かったら次
		if (pipelines_.contains(drawOrder_[i]) == false) { continue; }

		pipelines_[drawOrder_[i]]->Draw();
	}
}