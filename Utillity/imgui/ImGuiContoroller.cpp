#include "ImGuiContoroller.h"
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx12.h>
#include "YAssert.h"

void ImGuiContoroller::Initialize(const InitStatus& state)
{
	assert(state.hwnd_);
	assert(state.pDevice_);
	assert(state.pCommandList_);

	pCommandList_= state.pCommandList_;

	// デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE; // シェーダーから見えるように
	heapDesc.NumDescriptors = 1;

	// 設定をもとにデスクリプタヒープ(SRV,UAV,CBV用)を生成
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

void ImGuiContoroller::Begin()
{
	// Start the Dear ImGui frame
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGuiContoroller::End()
{
	// Rendering
	ImGui::Render();
}

void ImGuiContoroller::Draw()
{
	// SRVヒープの設定コマンド
	ID3D12DescriptorHeap* ppHeaps[] = { srvHeap_.Get() };
	pCommandList_->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

	// Render Dear ImGui graphics
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), pCommandList_);
}

void ImGuiContoroller::Finalize()
{
	// Cleanup
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	// デスクリプターヒープを開放
	srvHeap_.Reset();
}