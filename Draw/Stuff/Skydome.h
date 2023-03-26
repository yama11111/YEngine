#pragma once
#include "Model.h"

namespace YGame
{
	class Skydome
	{
	private:
		// オブジェクト
		std::unique_ptr<ModelObject> obj_;
		// モデルポインタ
		YGame::Model* pModel_ = nullptr;
	public:
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="status"> : トランスフォーム設定用ステータス</param>
		/// <param name="status.pos_"> : 位置</param>
		/// <param name="status.rota_"> : 回転</param>
		/// <param name="status.scale_"> : 大きさ</param>
		/// <param name="-------------------------------------------"></param>
		/// <param name="pModel"> : </param>
		void Initialize(const Transform::Status status, YGame::Model* pModel);
		// 更新
		void Update();
		// 描画
		void Draw();
	};
}
