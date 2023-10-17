#pragma once
#include "CharacterManager.h"
#include "DrawObjectForModel.h"
#include "MapChipManager.h"
#include "Camera.h"
#include <json.hpp>

namespace YGame
{
	class Level
	{

	public:

		static void LoadAsset();

		/// <summary>
		/// レベルデータ読み込み (.json)
		/// </summary>
		/// <param name="fileName"> : ファイル名 (.json)</param>
		/// <returns>レベルデータポインタ</returns>
		static Level* LoadJson(const std::string& fileName);

		/// <summary>
		/// 全データクリア
		/// </summary>
		static void ClearAllData();

	public:
		
		void Initialize();

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();

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
		void LoadData(nlohmann::json& object, GameObject* pParent = nullptr);
	
	private:

		// 全オブジェクト
		std::list<std::unique_ptr<GameObject>> objs_;

		// ファイルパス
		std::string fileName_;

	private:

		// 静的レベルデータ格納用list
		static std::list<std::unique_ptr<Level>> sLevelDatas_;

	};
}
