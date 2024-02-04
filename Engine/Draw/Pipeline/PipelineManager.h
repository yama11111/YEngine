/**
 * @file PipelineManager.h
 * @brief パイプライン管理クラス
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include "Pipeline.h"
#include "PostEffect.h"

namespace YGame
{
	class PipelineManager
	{

	public:
		
		/// <summary>
		/// シングルトンインスタンスポインタ取得
		/// </summary>
		/// <returns>インスタンスポインタ</returns>
		static PipelineManager* GetInstance();
	
	public:

		/// <summary>
		/// クリア
		/// </summary>
		void Clear();

		/// <summary>
		/// 挿入
		/// </summary>
		/// <param name="key"> : キー</param>
		/// <param name="pipeline"> : パイプライン (動的インスタンス)</param>
		void Insert(const std::string& key, Pipeline* pipeline);

		/// <summary>
		/// パイプラインの描画順
		/// </summary>
		/// <param name="pipelineKeys">パイプラインキーvector配列</param>
		void SetDrawOrder(const std::vector<std::string>& pipelineKeys);

		/// <summary>
		/// 描画情報をキューに積む
		/// </summary>
		/// <param name="key"> : キー (パイプライン名)</param>
		/// <param name="priority"> : 優先度</param>
		/// <param name="drawSet"> : 描画セット</param>
		/// <param name="-----------------------------------------"></param>
		/// <param name="(ConstBufferPtrSet*) pCBPtrSet"> : 定数バッファポインタセットポインタ</param>
		/// <param name="(BaseGraphic*) pGraphic"> : グラフィックポインタ</param>
		void EnqueueDrawSet(const std::string& key, const size_t priority, const Pipeline::DrawSet& drawSet);
		
		/// <summary>
		/// ポストエフェクトに書き込む
		/// </summary>
		/// <param name="pPostEffect"> : ポストエフェクトポインタvector配列</param>
		void RenderToPostEffect(std::vector<PostEffect*>& pPostEffects);
		
		/// <summary>
		/// 描画
		/// </summary>
		void Draw();

	private:

		// パイプライン格納配列
		std::unordered_map<
			std::string,
			std::unique_ptr<Pipeline>> pipelines_;

		// 描画順
		std::vector<std::string> drawOrder_;

	private:

		PipelineManager() = default;
		~PipelineManager() = default;
		PipelineManager(const PipelineManager&) = delete;
		const PipelineManager& operator=(const PipelineManager&) = delete;

	};
}

