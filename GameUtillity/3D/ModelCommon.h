#pragma once
#include "ShaderCommon.h"
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
	private:
		// シェーダーセット
		class ShaderSet : public YDX::ShaderCommon
		{
		public:
			// 頂点シェーダオブジェクト
			Microsoft::WRL::ComPtr<ID3DBlob> vsBlob_ = nullptr;
			// ピクセルシェーダオブジェクト
			Microsoft::WRL::ComPtr<ID3DBlob> psBlob_ = nullptr;
		public:
			// シェーダーファイル読み込み
			void Load(ID3DBlob* errorBlob);
		};
		// パイプライン設定構造体
		struct PipelineSetStatus : public YDX::PipelineSet::IStatus
		{
			void Initialize(ID3DBlob* errorBlob_) override;
		};
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

