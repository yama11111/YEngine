#pragma once
#include "ViewProjection.h"
#include <unordered_map>
#include <string>

namespace YGame
{
	class ViewProjectionManager
	{

	public:

		/// <summary>
		/// シングルトン
		/// </summary>
		/// <returns></returns>
		static ViewProjectionManager* GetInstance();
	
	public:

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();
		
		/// <summary>
		/// クリア
		/// </summary>
		void Clear();

		/// <summary>
		/// ビュープロジェクションポインタ消去
		/// </summary>
		/// <param name="key"> : キー</param>
		void Erase(const std::string& key);

		/// <summary>
		/// ビュープロジェクションポインタ挿入
		/// </summary>
		/// <param name="key"> : キー</param>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		void Insert(const std::string& key, ViewProjection* pVP);

		/// <summary>
		/// ビュープロジェクションポインタ取得
		/// </summary>
		/// <param name="key"> : キー</param>
		ViewProjection* ViewProjectionPtr(const std::string& key);

	private:

		// ビュープロジェクション
		std::unordered_map<std::string, ViewProjection*> pVPs_;

		// デフォルトカメラ
		ViewProjection defaultVP_;
	
	private:

		ViewProjectionManager() = default;
		~ViewProjectionManager() = default;
		ViewProjectionManager(const ViewProjectionManager&) = delete;
		const ViewProjectionManager& operator=(const ViewProjectionManager&) = delete;

	};
}
