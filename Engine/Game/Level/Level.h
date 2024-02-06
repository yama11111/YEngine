#pragma once
#include "GameObject.h"
#include "Camera.h"
#include <json.hpp>

namespace YGame
{
	class Level
	{

	public:

		/// <summary>
		/// レベルデータ読み込み (.json)
		/// </summary>
		/// <param name="fileName"> : ファイル名 (.json)</param>
		/// <param name="key"> : キー</param>
		/// <returns>レベルデータポインタ</returns>
		static Level* LoadJson(const std::string& fileName, const std::string& key);

		/// <summary>
		/// 全データクリア
		/// </summary>
		static void ClearAllData();

	public:

		Level() = default;
		~Level() = default;
		Level(const Level&) = delete;
		const Level& operator=(const Level&) = delete;

	private:
		
		/// <summary>
		/// データ読み込み
		/// </summary>
		/// <param name="object"> : オブジェクト(json)</param>
		/// <param name="pParent"> : 親オブジェクトポインタ</param>
		void LoadData(const std::string& key, nlohmann::json& object, GameObject* pParent = nullptr);
	
	private:

		// ファイルパス
		std::string fileName_;

	private:

		// 静的レベルデータ格納用list
		static std::list<std::unique_ptr<Level>> sLevelDatas_;

	};
}
