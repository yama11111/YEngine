#include "CBTexConfig.h"

#pragma region ���O���

using YGame::CBTexConfig;
using YMath::Vector2;

#pragma endregion

CBTexConfig* CBTexConfig::Create(const Vector2& tiling, const Vector2& offset, const bool isMutable)
{
	// �C���X�^���X���� (���I)
	CBTexConfig* instance = new CBTexConfig();

	// �萔�o�b�t�@����
	instance->cBuff_.Create(isMutable);

	// ������
	instance->Initialize(tiling, offset);

	// �C���X�^���X��Ԃ�
	return instance;
}

void CBTexConfig::Initialize(const Vector2& tiling, const Vector2& offset)
{
	SetTiling(tiling);
	SetOffset(offset);
}

void CBTexConfig::SetDrawCommand(const UINT rootParamIndex)
{
	// �萔�o�b�t�@�ɐݒ�
	cBuff_.map_->tiling_ = tiling_;
	cBuff_.map_->offset_ = offset_;

	// �V�F�[�_�[�ɑ���
	cBuff_.SetDrawCommand(rootParamIndex);
}
