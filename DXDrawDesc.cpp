#include "DXDrawDesc.h"
#include "Def.h"

void DXDrawDesc::Set()
{
	viewport.Set({ WIN_SIZE });
	scissorRect.Set({ { 0, 0 }, WIN_SIZE });
}

void DXDrawDesc::SetCommand()
{
	// �r���[�|�[�g�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
	viewport.Stack();
	// �V�U�[��`�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
	scissorRect.Stack();
}
