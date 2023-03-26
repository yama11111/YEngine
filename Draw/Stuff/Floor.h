#pragma once
#include "Model.h"
#include <vector>

namespace YGame
{
	class Floor
	{
	private:
		// オブジェクト
		std::vector<std::vector<std::unique_ptr<ModelObject>>> objs_;
		// モデルポインタ
		YGame::Model* pModel_ = nullptr;
	public:
		// 初期化ステータス
		struct InitStatus
		{
			size_t xNum_; // X軸 枚数
			size_t yNum_; // Y軸 枚数
			YMath::Vector3 pos_; // 場所 (中心)
			YMath::Vector3 scale_; // 大きさ (1枚)
			Model* pModel_; // モデルポインタ
		};
	public:
		// 初期化
		void Initialize(const InitStatus& status);
		// 更新
		void Update();
		// 描画
		void Draw();
	};
}
