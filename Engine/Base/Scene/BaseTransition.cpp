#include "BaseTransition.h"

using YGame::BaseTransition;

void BaseTransition::Reset()
{
	// リセット
	step_ = Step::Close;

	isAct_ = false;
	isFalling_ = false;
	isChangeMoment_ = false;
	isRising_ = false;
	isEnd_ = false;

	loadTim_.Reset(false);
}
