#include "ImGuiManager.h"
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx12.h>
#include "YAssert.h"

void ImGuiManager::Initialize(const InitStatus& state)
{
	assert(state.hwnd_);
	assert(state.pDevice_);
	assert(state.pCommandList_);

	pCommandList_= state.pCommandList_;

	// �f�X�N���v�^�q�[�v�ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE; // �V�F�[�_�[���猩����悤��
	heapDesc.NumDescriptors = 1;

	// �ݒ�����ƂɃf�X�N���v�^�q�[�v(SRV,UAV,CBV�p)�𐶐�
	YDX::Result(state.pDevice_->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&srvHeap_)));

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(state.hwnd_);
	ImGui_ImplDX12_Init(state.pDevice_, static_cast<int>(state.backBufferCount_),
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, srvHeap_.Get(),
		srvHeap_->GetCPUDescriptorHandleForHeapStart(),
		srvHeap_->GetGPUDescriptorHandleForHeapStart());

	// Load Fonts
	io.Fonts->AddFontDefault();
}

void ImGuiManager::Finalize()
{
	// Cleanup
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	// �f�X�N���v�^�[�q�[�v���J��
	srvHeap_.Reset();
}

void ImGuiManager::Begin()
{
	// Start the Dear ImGui frame
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGuiManager::End()
{
	// Rendering
	ImGui::Render();
}

void ImGuiManager::Draw()
{
	// SRV�q�[�v�̐ݒ�R�}���h
	ID3D12DescriptorHeap* ppHeaps[] = { srvHeap_.Get() };
	pCommandList_->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

	// Render Dear ImGui graphics
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), pCommandList_);
}