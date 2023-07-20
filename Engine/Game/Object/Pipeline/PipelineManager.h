#pragma once
#include "Pipeline.h"

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
		/// 描画情報をキューに積む
		/// </summary>
		/// <param name="key"> : キー (パイプライン名)</param>
		/// <param name="priority"> : 優先度</param>
		/// <param name="pObj"> : オブジェクトポインタ</param>
		void EnqueueDrawSet(const std::string& key, const uint32_t priority, Object* pObj);

		/// <summary>
		/// 指定したパイプラインを描画
		/// </summary>
		/// <param name="key"> : キー</param>
		void Draw(const std::string& key);

	private:

		// パイプライン格納配列
		std::unordered_map<
			std::string,
			std::unique_ptr<Pipeline>> pipelines_;

	private:

		PipelineManager() = default;

		~PipelineManager() = default;

		PipelineManager(const PipelineManager&) = delete;

		const PipelineManager& operator=(const PipelineManager&) = delete;

	};
}

