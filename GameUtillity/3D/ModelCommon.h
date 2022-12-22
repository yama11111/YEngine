#pragma once
#include "PipelineSet.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

struct aiMesh;
struct aiMaterial;

namespace YGame
{
	class ModelCommon
	{
	public:
		// 頂点データ構造体
		struct VData
		{
			YMath::Vec3 pos_;	  // xyz座標
			YMath::Vec3 normal_;  // 法線ベクトル
			YMath::Vec2 uv_;	  // uv座標
			YMath::Vec3 tangent_; // 接空間
			YMath::Vec4 color_;	  // 頂点色
		};
	protected:
		// パイプライン設定
		static YDX::PipelineSet pplnSet_;
	public:
		// 静的初期化ステータス
		struct StaticInitStatus
		{
			// ルートパラメータポインタ
			std::vector<D3D12_ROOT_PARAMETER>* rootParams_;
		};
	public:
		// 静的初期化
		static void StaticInitialize(const StaticInitStatus& state);
		// 静的描画コマンド
		static void StaticSetDrawCommand();
	};
}

