#include "CBTexConfig.h"

#pragma region 名前空間

using YGame::CBTexConfig;
using YMath::Vector2;

#pragma endregion

CBTexConfig* CBTexConfig::Create(const Vector2& tiling, const Vector2& offset, const bool isMutable)
{
	// インスタンス生成 (動的)
	CBTexConfig* instance = new CBTexConfig();

	// 定数バッファ生成
	instance->cBuff_.Create(isMutable);

	// 初期化
	instance->Initialize(tiling, offset);

	// インスタンスを返す
	return instance;
}

void CBTexConfig::Initialize(const Vector2& tiling, const Vector2& offset)
{
	SetTiling(tiling);
	SetOffset(offset);
}

void CBTexConfig::SetDrawCommand(const UINT rootParamIndex)
{
	// 定数バッファに設定
	cBuff_.map_->tiling_ = tiling_;
	cBuff_.map_->offset_ = offset_;

	// シェーダーに送る
	cBuff_.SetDrawCommand(rootParamIndex);
}
