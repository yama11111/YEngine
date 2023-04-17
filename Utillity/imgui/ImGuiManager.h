#pragma once
#include "DescriptorHeap.h"
#include <windows.h>
#include <dxgi1_6.h>

#pragma comment(lib, "dxgi.lib")

class ImGuiManager
{
private:
	// �R�}���h���X�g�|�C���^
	ID3D12GraphicsCommandList* pCmdList_ = nullptr;
	// �f�X�N���v�^�[�q�[�v
	YDX::DescriptorHeap* pDescHeap_ = nullptr;
public:
	struct InitStatus 
	{
		HWND hwnd_; // �E�B���h�E�n���h��
		ID3D12Device* pDevice_; // �f�o�C�X
		ID3D12GraphicsCommandList* pCmdList_; // �R�}���h���X�g
		YDX::DescriptorHeap* pDescHeap_; // �f�X�N���v�^�[�q�[�v
		size_t backBufferCount_; // �o�b�N�o�b�t�@�̐�
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

