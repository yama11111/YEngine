#include "YDirectX.h"
#include "YAssert.h"
#include <wrl/client.h>
#include <thread>

using DX::YDirectX;
using std::chrono::steady_clock;
using std::chrono::microseconds;

microseconds YDirectX::MinTime_ = microseconds(uint64_t(1000000.0f / 60.0f));
microseconds YDirectX::MinCheckTime_ = microseconds(uint64_t(1000000.0f / 65.0f));

void  YDirectX::SetFPS(const float fps)
{
	MinTime_ = microseconds(uint64_t(1000000.0f / fps));
	MinCheckTime_ = microseconds(uint64_t(1000000.0f / (fps + 5.0f)));
}

bool YDirectX::Initialize(const HWND& hwnd, const Math::Vec2& size)
{
	// ----- FPS�Œ�֘A ----- //
	// ���ݎ��Ԃ��L�^
	timeRef_ = steady_clock::now();

	// ----- �f�o�b�O���C���[��L���� ----- //
#ifdef _DEBUG
	ComPtr<ID3D12Debug1> debugController;
	//�f�o�b�O���C���[���I����
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
		debugController->SetEnableGPUBasedValidation(true);
	}
#endif

	// ----- DXGI�t�@�N�g���[���� ----- //
	Result(CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory_)));

	// ----- �f�o�C�X���� ----- //
	// �A�_�v�^�[�̗񋓗p
	std::vector<ComPtr<IDXGIAdapter4>> adapters;
	// �����ɓ���̖��O�����A�_�v�^�[�I�u�W�F�N�g������
	ComPtr<IDXGIAdapter4> tmpAdapter = nullptr;

	// �p�t�H�[�}���X���������̂��珇�ɁA�S�ẴA�_�v�^�[���
	for (UINT i = 0;
		dxgiFactory_->EnumAdapterByGpuPreference(
			i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
			IID_PPV_ARGS(&tmpAdapter)) != DXGI_ERROR_NOT_FOUND;
		i++)
	{
		// ���I�z��ɒǉ�
		adapters.push_back(tmpAdapter.Get());
	}

	// �Ó��ȃA�_�v�^��I��
	for (size_t i = 0; i < adapters.size(); i++)
	{
		DXGI_ADAPTER_DESC3 adapterDesc;
		// �A�_�v�^�[�̏��擾
		adapters[i]->GetDesc3(&adapterDesc);
		// �\�t�g�E�F�A�f�o�C�X�����
		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE))
		{
			// �f�o�C�X���̗p���ă��[�v�𔲂���
			tmpAdapter = adapters[i];
			break;
		}
	}

	// �A�_�v�^�[�������Ȃ�I��
	if (tmpAdapter == nullptr)
	{
		assert(false);
		return false;
	}

	// �Ή����x���̔z��
	D3D_FEATURE_LEVEL levels[4] =
	{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	D3D_FEATURE_LEVEL featureLevel{};

	for (size_t i = 0; i < _countof(levels); i++)
	{
		// �̗p�����A�_�v�^�[�Ńf�o�C�X����
		if (Result(D3D12CreateDevice(tmpAdapter.Get(), levels[i],
			IID_PPV_ARGS(&device_))))
		{
			// �f�o�C�X�𐶐��ł������_�Ń��[�v�𔲂���
			featureLevel = levels[i];
			break;
		}
	}

	// �f�o�C�X�������Ȃ�I��
	if (device_ == nullptr)
	{
		assert(false);
		return false;
	}

	// ----- �G���[���~�܂�悤�� ----- //
#ifdef _DEBUG
	Microsoft::WRL::ComPtr<ID3D12InfoQueue> infoQueue;
	if (SUCCEEDED(device_->QueryInterface(IID_PPV_ARGS(&infoQueue))))
	{
		// �~�܂�
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true); // ���o���G���[
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true); // �G���[
	}
	D3D12_MESSAGE_ID denyIds[] = {
		D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE
	};
	D3D12_MESSAGE_SEVERITY severities[] = { D3D12_MESSAGE_SEVERITY_INFO };
	D3D12_INFO_QUEUE_FILTER filter{};
	filter.DenyList.NumIDs = _countof(denyIds);
	filter.DenyList.pIDList = denyIds;
	filter.DenyList.NumSeverities = _countof(severities);
	filter.DenyList.pSeverityList = severities;
	infoQueue->PushStorageFilter(&filter);
#endif

	// ----- �R�}���h�A���P�[�^���� ----- //
	Result(device_->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(&cmdAllocator_)));

	// ----- �R�}���h���X�g���� ----- //
	Result(device_->CreateCommandList(
		0, D3D12_COMMAND_LIST_TYPE_DIRECT,
		cmdAllocator_.Get(), nullptr,
		IID_PPV_ARGS(&cmdList_)));

	// ----- �R�}���h�L���[���� ----- //
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{}; // �ݒ�
	Result(device_->CreateCommandQueue(
		&commandQueueDesc, 
		IID_PPV_ARGS(&cmdQueue_)));

	// ----- �X���b�v�`�F�[������ ----- //
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{}; // �ݒ�
	swapChainDesc.Width = (UINT)size.x_;
	swapChainDesc.Height = (UINT)size.y_;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;		  // �F���̏���
	swapChainDesc.SampleDesc.Count = 1;						  // �}���`�T���v�����Ȃ�
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;		  // �o�b�N�o�b�t�@�p
	swapChainDesc.BufferCount = 2;							  // �o�b�t�@����2�ɐݒ�
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // �t���b�v��͔j��
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	ComPtr<IDXGISwapChain1> swapChain1;

	Result(dxgiFactory_->CreateSwapChainForHwnd(
		cmdQueue_.Get(),
		hwnd,
		&swapChainDesc,
		nullptr,
		nullptr,
		&swapChain1));

	swapChain1.As(&swapChain_);

	// ----- �����_�[�^�[�Q�b�g�r���[���� ----- //
	// �f�X�N���v�^�q�[�v�ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV; // �����_�[�^�[�Q�b�g�r���[
	rtvHeapDesc.NumDescriptors = swapChainDesc.BufferCount; // ���\��2��
	// �f�X�N���v�^�q�[�v����
	Result(device_->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap_)));
	// �o�b�N�o�b�t�@����
	backBuffers_.resize(swapChainDesc.BufferCount);

	// �X���b�v�`�F�[���̑S�Ẵo�b�t�@�ɂ��ď�������
	for (size_t i = 0; i < backBuffers_.size(); i++)
	{
		// �X���b�v�`�F�[������o�b�t�@�擾
		swapChain_->GetBuffer((UINT)i, IID_PPV_ARGS(&backBuffers_[i]));
		// �f�X�N���v�^�q�[�v�̃n���h���擾
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtvHeap_->GetCPUDescriptorHandleForHeapStart();
		// �����\���ŃA�h���X�������
		rtvHandle.ptr += i * device_->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);
		// �����_�[�^�[�Q�b�g�r���[�ݒ�
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
		// �V�F�[�_�[�̌v�Z���ʂ�SRGB�ɕϊ����ď�������
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		// �����_�[�^�[�Q�b�g�r���[����
		device_->CreateRenderTargetView(backBuffers_[i].Get(), &rtvDesc, rtvHandle);
	}

	// ----- �f�v�X�X�e���V���r���[���� ----- //
	D3D12_RESOURCE_DESC dsvResDesc{}; // ���\�[�X�ݒ�
	dsvResDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	dsvResDesc.Width = (UINT16)size.x_; // �����_�[�^�[�Q�b�g�ɍ��킹��
	dsvResDesc.Height = (UINT)size.y_; // �����_�[�^�[�Q�b�g�ɍ��킹��
	dsvResDesc.DepthOrArraySize = 1;
	dsvResDesc.Format = DXGI_FORMAT_D32_FLOAT; // �[�x�l�t�H�[�}�b�g
	dsvResDesc.SampleDesc.Count = 1;
	dsvResDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL; // �f�v�X�X�e���V��

	// �[�x�l�p�q�[�v�v���p�e�B
	D3D12_HEAP_PROPERTIES dsvHeapProp = {}; // �o�b�t�@�ݒ�
	dsvHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;

	// �[�x�l�̃N���A�ݒ�
	D3D12_CLEAR_VALUE clearValue{}; // �[�x�l�̃N���A�ݒ�
	clearValue.DepthStencil.Depth = 1.0f; // �[�x�l1.0f(�ő�l)�ŃN���A
	clearValue.Format = DXGI_FORMAT_D32_FLOAT; // �[�x�l�t�H�[�}�b�g

	// ���\�[�X����
	Result(device_->CreateCommittedResource(
		&dsvHeapProp, // �q�[�v�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&dsvResDesc, // ���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&clearValue,
		IID_PPV_ARGS(&dsvBuff_)));

	// �[�x�r���[�p�f�X�N���v�^�[�q�[�v�쐬
	// �f�X�N���v�^�q�[�v�ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	dsvHeapDesc.NumDescriptors = 1; // �[�x�r���[��1��
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV; // �f�v�X�X�e���V���r���[
	Result(device_->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap_)));

	// �[�x�r���[�쐬
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT; // �[�x�l�t�H�[�}�b�g
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;

	device_->CreateDepthStencilView(
		dsvBuff_.Get(),
		&dsvDesc,
		dsvHeap_->GetCPUDescriptorHandleForHeapStart());

	// ----- �t�F���X���� ----- //
	Result(device_->CreateFence(fenceValue_, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence_)));

	return true;
}

void YDirectX::PreDraw(const Math::Vec4& clearColor)
{
	// 1.���\�[�X�o���A�ŏ������݉\�ɕύX
	UINT bbIndex = swapChain_->GetCurrentBackBufferIndex(); // �o�b�N�o�b�t�@�̔ԍ����擾(0�Ԃ�1��)
	D3D12_RESOURCE_BARRIER barrierDesc{};
	barrierDesc.Transition.pResource = backBuffers_[bbIndex].Get(); // �o�b�N�o�b�t�@���w��
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;       // �\�� ��Ԃ���
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;  // �`�� ��Ԃ�
	cmdList_->ResourceBarrier(1, &barrierDesc);

	// 2.�`���̕ύX
	// �����_�[�^�[�Q�b�g�r���[�̃n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtvHeap_->GetCPUDescriptorHandleForHeapStart();
	rtvHandle.ptr += (SIZE_T)bbIndex * device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	// �f�v�X�X�e���V���r���[�̃n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = dsvHeap_->GetCPUDescriptorHandleForHeapStart();
	cmdList_->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

	// 3.��ʃN���A {R, G, B, A}
	FLOAT clear[] = { clearColor.r_,clearColor.g_,clearColor.b_,clearColor.a_ };
	cmdList_->ClearRenderTargetView(rtvHandle, clear, 0, nullptr); // ���ۂ��F
	cmdList_->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void YDirectX::PostDraw()
{
	// 5.���\�[�X�o���A��߂�
	UINT bbIndex = swapChain_->GetCurrentBackBufferIndex(); // �o�b�N�o�b�t�@�̔ԍ����擾(0�Ԃ�1��)
	D3D12_RESOURCE_BARRIER barrierDesc{};
	barrierDesc.Transition.pResource = backBuffers_[bbIndex].Get(); // �o�b�N�o�b�t�@���w��
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET; // �`�� ��Ԃ���
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;        // �\�� ��Ԃ�
	cmdList_->ResourceBarrier(1, &barrierDesc);

	// ���߂̃N���[�Y
	Result(cmdList_->Close());

	// �R�}���h���X�g���s
	ID3D12CommandList* commandLists[] = { cmdList_.Get() };
	cmdQueue_->ExecuteCommandLists(1, commandLists);

	// ��ʂɕ\������o�b�t�@���t���b�v(���\�̓��ւ�)
	Result(swapChain_->Present(1, 0));

	// �R�}���h�̎��s������҂�
	cmdQueue_->Signal(fence_.Get(), ++fenceValue_);
	if (fence_->GetCompletedValue() != fenceValue_)
	{
		HANDLE event = CreateEvent(nullptr, false, false, nullptr);
		fence_->SetEventOnCompletion(fenceValue_, event);
		if (event == 0) 
		{
			assert(false);
			return;
		}
		WaitForSingleObject(event, INFINITE);
		CloseHandle(event);
	}

	// ���ݎ��Ԃ��擾
	steady_clock::time_point now = steady_clock::now();
	// �O�񂩂�̌o�ߎ��Ԃ��擾
	microseconds elpsed = std::chrono::duration_cast<microseconds>(now - timeRef_);

	// �����pfps���o���Ă��Ȃ��ꍇ
	if (elpsed < MinCheckTime_)
	{
		// �Œ莞fps���o�߂���܂Ŕ����ȃX���[�v���J��Ԃ�
		while (steady_clock::now() - timeRef_ < MinTime_)
		{
			// 1�}�C�N���b�X���[�v
			std::this_thread::sleep_for(microseconds(1));
		}
	}

	// ���ݎ��Ԃ��L�^
	timeRef_ = steady_clock::now();

	// �L���[���N���A
	Result(cmdAllocator_->Reset());
	// �ĂуR�}���h���X�g�𒙂߂鏀��
	Result(cmdList_->Reset(cmdAllocator_.Get(), nullptr));
}
