#include "DXResourceBarrier.h"
#include "DXCommandList.h"

void DXResourceBarrier::SetCurrentBackBuffer(ID3D12Resource* backBuffer)
{
	barrierDesc.Transition.pResource = backBuffer; // �o�b�N�o�b�t�@���w��
}

bool DXResourceBarrier::ChangeState(const int state)
{
	switch (state)
	{
	case RenderTarget:
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;       // �\�� ��Ԃ���
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;  // �`�� ��Ԃ�
		break;
	case Present:
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET; // �`�� ��Ԃ���
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;        // �\�� ��Ԃ�
		break;
	default:
		return false;
		break;
	}

	DXCommandList* cmdList = DXCommandList::GetInstance();
	cmdList->List()->ResourceBarrier(1, &barrierDesc);

	return true;
}
