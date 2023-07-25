#pragma once
#include "BaseGraphic.h"
#include "Vertices.h"
#include "Texture.h"
#include "PipelineSetting.h"
#include "Vector3.h"
#include <list>
#include <array>

namespace YGame
{
	// スプライト3D (ビルボード)
	class Sprite3D :
		public BaseGraphic
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="pTex"> : テクスチャポインタ</param>
		/// <returns>スプライトポインタ</returns>
		static Sprite3D* Create(Texture* pTex);

		/// <summary>
		/// 全削除
		/// </summary>
		static void AllClear();

		/// <summary>
		/// モデル用のパイプライン設定取得
		/// </summary>
		/// <returns>パイプライン設定</returns>
		static PipelineSetting GetPipelineSetting();

	public:

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="rpIndices"> : ルートパラメータ情報 + 番号</param>
		void SetDrawCommand(std::unordered_map<std::string, uint32_t>& rpIndices) override;

		/// <summary>
		/// 表示するか設定
		/// </summary>
		/// <param name="isVisible"> : 表示するか</param>
		void SetIsVisible(const bool isVisible);

	public:

		Sprite3D() = default;

		~Sprite3D() = default;

	public:

		// 頂点データ
		struct VData
		{
			YMath::Vector3 pos_; // xyz座標
		};

	private:

		// テクスチャ
		Texture* pTex_ = nullptr;

		// 表示するか
		bool isVisible_ = true;

	private:

		// 頂点データ
		static YDX::Vertices<VData> vt_;

		// 初期化フラグ
		static bool isInitVertices_;

		// 静的スプライト3D格納用vector配列
		static std::vector<std::unique_ptr<Sprite3D>> sSprites_;
	};
}

