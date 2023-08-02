#include "ImGuiManager.h"
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx12.h>
#include "YAssert.h"

using YDX::DescriptorHeap;

void ImGuiManager::Initialize(const InitStatus& state)
{
	// nullチェック
	assert(state.hwnd_);
	assert(state.pDevice_);
	assert(state.pCmdList_);
	assert(state.pDescHeap_);
	// 代入
	pCmdList_= state.pCmdList_;
	pDescHeap_ = state.pDescHeap_;

	// SRV用ハンドル
	DescriptorHeap::Handle descHeapHandle{};
	
	// SRVを追加
	descHeapHandle = state.pDescHeap_->AddSRV(false);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(state.hwnd_);
	ImGui_ImplDX12_Init(state.pDevice_, static_cast<int>(state.backBufferCount_),
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, state.pDescHeap_->Get(),
		descHeapHandle.cpu_,
		descHeapHandle.gpu_);

	// Load Fonts
	io.Fonts->AddFontDefault();
}

void ImGuiManager::Finalize()
{
	// Cleanup
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
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
	// SRVヒープの設定コマンド
	ID3D12DescriptorHeap* ppHeaps[] = { pDescHeap_->Get() };
	pCmdList_->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

	// Render Dear ImGui graphics
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), pCmdList_);
}