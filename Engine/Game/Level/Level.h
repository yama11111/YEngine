#pragma once
#include "Model.h"

namespace YGame
{
	class Level
	{

	public:

		// オブジェクトセット
		struct ObjectSet
		{
			// モデルポインタ
			Model* pModel_ = nullptr;
			// オブジェクトポインタ
			std::unique_ptr<Model::Object> pObjs_;
			// オブジェクトファイル名
			std::string objFileName_;
			// 子
			std::unique_ptr<ObjectSet> child_;
		};

	public:

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

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();
	
	public:

		/// <summary>
		/// 更新
		/// </summary>
		void UpdateObjSet(ObjectSet* obj);
		
		/// <summary>
		/// 描画
		/// </summary>
		void DrawObjSet(ObjectSet* obj);

	public:

		Level() = default;

		~Level() = default;

		Level(const Level&) = delete;

		const Level& operator=(const Level&) = delete;

	private:

		// 全オブジェクト
		std::list<std::unique_ptr<ObjectSet>> objSets_;

		// ファイルパス
		std::string fileName_;

	private:

		// 静的レベルデータ格納用list
		static std::list<std::unique_ptr<Level>> sLevelDatas_;


	};
}
