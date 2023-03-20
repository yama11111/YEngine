#pragma once
#include <windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

class ImGuiManager
{
private:
	// �f�X�N���v�^�[�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap_ = nullptr;
	// �R�}���h���X�g�|�C���^
	ID3D12GraphicsCommandList* pCommandList_ = nullptr;
public:
	struct InitStatus 
	{
		HWND* hwnd_; // �E�B���h�E�n���h��
		ID3D12Device* pDevice_; // �f�o�C�X
		size_t backBufferCount_; // �o�b�N�o�b�t�@�̐�
		ID3D12GraphicsCommandList* pCommandList_; // �R�}���h���X�g
	};
public:
	// ������
	void Initialize(const InitStatus& state);
	// �I������
	void Finalize();
	// ��t�J�n
	void Begin();
	// ��t�I��
	void End();
	// �`��
	void Draw();
};

