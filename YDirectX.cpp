#include "YDirectX.h"
#include "DXAdapter.h"
#include "Result.h"

int YDirectX::Init(const HWND& hwnd)
{
	// �f�o�b�O���C���[��L����
	debugLayer.Enable(true);

	// DXGI�t�@�N�g���[����
	Result::Check(CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory)));

	DXAdapter* adpt = DXAdapter::GetInstance();
	adpt->Selection(dxgiFactory);

	// �f�o�C�X����
	dev = DXDevice::GetInstance();
	if (!dev->Create()) return -1;
	Result::Assert(dev->Device() != nullptr);

	// �G���[���~�܂�悤��
	debugLayer.Severity();

	// �R�}���h���X�g����
	cmdList = DXCommandList::GetInstance();
	cmdList->Create();

	// �R�}���h�L���[����
	cmdQue.Create();

	// �X���b�v�`�F�[������
	swpChain.Init();
	swpChain.Create(dxgiFactory, cmdQue.Queue(), hwnd);

	// �����_�[�^�[�Q�b�g�r���[����
	rtv.Create(swpChain.SwapChain(), swpChain.Desc());

	// �t�F���X����
	fence.Create();

	return 0;
}

int YDirectX::PreDraw()
{
	// �o�b�N�o�b�t�@�̔ԍ����擾(2�Ȃ̂�0�Ԃ�1��)
	UINT bbIndex = swpChain.SwapChain()->GetCurrentBackBufferIndex();
	// 1.���\�[�X�o���A�ŏ������݉\�ɕύX
	rscBarrier.SetCurrentBackBuffer(rtv.BackBaffer(bbIndex)); // �o�b�N�o�b�t�@���w��
	rscBarrier.ChangeState(rscBarrier.RenderTarget); // �`���Ԃ�

	// 2.�`���̕ύX
	DXDescriptorHeap _rtv = rtv.RenderTargetView();
	// �����_�[�^�[�Q�b�g�r���[�̃n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = _rtv.heap->GetCPUDescriptorHandleForHeapStart();
	rtvHandle.ptr += bbIndex * dev->Device()->GetDescriptorHandleIncrementSize(_rtv.hDesc.Type);
	cmdList->List()->OMSetRenderTargets(1, &rtvHandle, false, nullptr);

	// 3.��ʃN���A {R, G, B, A}
	cmdList->CrearRTV(rtvHandle); // ���ۂ��F

	return 0;
}

int YDirectX::PostDraw()
{
	// 5.���\�[�X�o���A��߂�
	rscBarrier.ChangeState(rscBarrier.Present); // �\����Ԃ�

	// ���߂̃N���[�Y
	Result::Check(cmdList->List()->Close());

	// �R�}���h���X�g���s
	ID3D12CommandList* commandLists[] = { cmdList->List() };
	cmdQue.Queue()->ExecuteCommandLists(1, commandLists);

	// ��ʂɕ\������o�b�t�@���t���b�v(���\�̓��ւ�)
	Result::Check(swpChain.SwapChain()->Present(1, 0));

	// �R�}���h�̎��s������҂�
	fence.ConfirmCommandComplate(cmdQue.Queue());

	// �L���[���N���A + �ĂуR�}���h���X�g�𒙂߂鏀��
	cmdList->ClearAndPrepare();

	return 0;
}

YDirectX* YDirectX::GetInstance()
{
	static YDirectX instance;
	return &instance;
}

