#pragma once
#include "BaseGraphic.h"
#include "Vertices.h"
#include "Texture.h"
#include "PipelineSetting.h"
#include "Vector3.h"

namespace YGame
{
	// スプライト3D (ビルボード)
	class Sprite3D :
		public BaseGraphic
	{

	public:

		// 頂点データ
		struct VData
		{
			YMath::Vector3 pos_; // xyz座標
		};

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="pTexs"> : テクスチャポインタ配列</param>
		/// <returns>スプライトポインタ</returns>
		static Sprite3D* Create(const std::unordered_map<std::string, Texture*>& pTexs);

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

	public:

		Sprite3D() = default;

		~Sprite3D() = default;

	private:

		// テクスチャ
		std::unordered_map<std::string, Texture*> pTexs_{};

	private:

		// 頂点データ
		static YDX::Vertices<VData> vt_;

		// 初期化フラグ
		static bool isInitVertices_;

		// 静的スプライト3D格納用vector配列
		static std::vector<std::unique_ptr<Sprite3D>> sSprites_;
	};
}

