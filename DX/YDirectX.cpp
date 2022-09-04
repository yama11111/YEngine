#include "YDirectX.h"
#include "Adapter.h"
#include "Utility/Result.h"
#include "Def.h"

using DX::YDirectX;
using DX::Utility::Result;

YDirectX* YDirectX::GetInstance()
{
	static YDirectX instance;
	return &instance;
}

bool YDirectX::Initialize(const HWND& hwnd)
{
	// �f�o�b�O���C���[��L����
	debugLayer.Enable(true);

	// DXGI�t�@�N�g���[����
	Result::Check(CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory)));

	Adapter* adpt = Adapter::GetInstance();
	adpt->Selection(dxgiFactory.Get());

	// �f�o�C�X����
	dev = Device::GetInstance();
	if (!dev->Create())
	{
		Result::Assert(false);
		return false;
	}

	// �G���[���~�܂�悤��
	debugLayer.Severity();

	// �R�}���h���X�g����
	cmdList.Create();

	// �R�}���h�L���[����
	cmdQue.Create();

	// �X���b�v�`�F�[������
	swpChain.Initialize();
	swpChain.Create(dxgiFactory.Get(), cmdQue.Get(), hwnd);

	// �����_�[�^�[�Q�b�g�r���[����
	rtv.Create(swpChain.Get(), swpChain.Desc());

	dsv.Create();

	// �t�F���X����
	fence.Create();

	rscBarrier.Initialize(cmdList.Get());

	return true;
}

void YDirectX::PreDraw()
{
	// �o�b�N�o�b�t�@�̔ԍ����擾(2�Ȃ̂�0�Ԃ�1��)
	UINT bbIndex = swpChain.Get()->GetCurrentBackBufferIndex();
	// 1.���\�[�X�o���A�ŏ������݉\�ɕύX
	rscBarrier.SetCurrentBackBuffer(rtv.BackBaffer(bbIndex)); // �o�b�N�o�b�t�@���w��
	rscBarrier.ChangeState(rscBarrier.RenderTarget); // �`���Ԃ�

	// 2.�`���̕ύX
	// �����_�[�^�[�Q�b�g�r���[�̃n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtv.Get().Get()->GetCPUDescriptorHandleForHeapStart();
	rtvHandle.ptr += (SIZE_T)bbIndex * dev->Get()->GetDescriptorHandleIncrementSize(rtv.Get().desc.Type);
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = dsv.Get().Get()->GetCPUDescriptorHandleForHeapStart();
	cmdList.Get()->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

	// 3.��ʃN���A {R, G, B, A}
	FLOAT clearColor[] = { CLEAR_COLOR.r, CLEAR_COLOR.g, CLEAR_COLOR.b, CLEAR_COLOR.a };
	cmdList.Get()->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr); // ���ۂ��F
	cmdList.Get()->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void YDirectX::PostDraw()
{
	// 5.���\�[�X�o���A��߂�
	rscBarrier.ChangeState(rscBarrier.Present); // �\����Ԃ�

	// ���߂̃N���[�Y
	Result::Check(cmdList.Get()->Close());

	// �R�}���h���X�g���s
	ID3D12CommandList* commandLists[] = { cmdList.Get() };
	cmdQue.Get()->ExecuteCommandLists(1, commandLists);

	// ��ʂɕ\������o�b�t�@���t���b�v(���\�̓��ւ�)
	Result::Check(swpChain.Get()->Present(1, 0));

	// �R�}���h�̎��s������҂�
	fence.ConfirmCommandComplate(cmdQue.Get());

	// �L���[���N���A + �ĂуR�}���h���X�g�𒙂߂鏀��
	cmdList.Reset();
}

ID3D12GraphicsCommandList* YDirectX::GetCommandList()
{
	return cmdList.Get();
}
