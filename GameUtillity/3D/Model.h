#pragma once
#include "ModelCommon.h"
#include "Object.h"
#include "ViewProjection.h"

namespace YGame
{
	// モデル用オブジェクト
	typedef Object<ModelCommon::CBData> ObjectModel;

	// モデルクラス
	class Model : private ModelCommon
	{
	private:
		// メッシュ配列
		std::vector<Mesh> meshes_;
		// 色
		Color defColor_{};
	public:
		// 読み込み設定構造体
		struct LoadStatus
		{
			std::string directoryPath_;
			std::string modelFileName_;
			bool isInverseU_ = false;
			bool isInverseV_ = true;
			bool isNormalized_ = false;
			std::string extension_ = "";
		};
	public:
		// 生成(立方体)
		static Model* Create();
		// モデル読み込み
		static Model* Load(const std::string& modelFileName);
		// モデル読み込み(assimp)
		static Model* Load(const LoadStatus& state);
	public:
		// 描画 (テクスチャ + 色 有)
		void Draw(ObjectModel& obj, const ViewProjection& vp, Color& color, const UINT tex);
		// 描画 (テクスチャ 有)
		void Draw(ObjectModel& obj, const ViewProjection& vp, const UINT tex);
		// 描画 (色 有)
		void Draw(ObjectModel& obj, const ViewProjection& vp, Color& color);
		// 描画 (デフォルト)
		void Draw(ObjectModel& obj, const ViewProjection& vp);
	private:
		// コンストラクタ
		Model() = default;
	};
}
