#pragma once
#include "BaseScene.h"

namespace YScene
{
	// ゲームシーン
	class PlayScene : public BaseScene
	{

	public:

#pragma region リソース

		YGame::Model* pModel_ = nullptr;



#pragma endregion

#pragma region ゲームオブジェクト

		std::unique_ptr<YGame::Model::Object> modelObj_;


		// 転送用ビュープロジェクション
		YGame::ViewProjection transferVP_;

#pragma endregion

	public:

		/// <summary>
		/// 読み込み
		/// </summary>
		void Load() override;

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize() override;

		/// <summary>
		/// 終了処理
		/// </summary>
		void Finalize() override;

		/// <summary>
		/// 更新
		/// </summary>
		void Update() override;

		/// <summary>
		/// 描画
		/// </summary>
		void Draw() override;

	public:

		// コンストラクタ
		PlayScene() = default;

		// デストラクタ
		~PlayScene() = default;

	};
}
