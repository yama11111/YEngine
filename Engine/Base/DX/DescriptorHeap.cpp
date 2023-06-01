#include "DescriptorHeap.h"
#include "YAssert.h"
#include <imgui.h>

using YDX::DescriptorHeap;

ID3D12Device* DescriptorHeap::spDevice_ = nullptr;
ID3D12GraphicsCommandList* DescriptorHeap::spCmdList_ = nullptr;

void DescriptorHeap::StaticInitialize(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCmdList)
{
	assert(pDevice);
	assert(pCmdList);

	spDevice_  = pDevice;
	spCmdList_ = pCmdList;
}

void DescriptorHeap::Initialize()
{

	// �f�X�N���v�^�q�[�v�ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE; // �V�F�[�_�[���猩����悤��
	heapDesc.NumDescriptors = MaxSRVCount_ + MaxUAVCount_ + MaxCBVCount_;

	// �ݒ�����ƂɃf�X�N���v�^�q�[�v(SRV,UAV,CBV�p)�𐶐�
	Result(spDevice_->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&descriptorHeap_)));


	// �C���N�������g�T�C�Y�擾
	incSize_ = spDevice_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);


	// �J�E���g������
	immutableCounter_.ResetCount();
	mutableCounter_.ResetCount();


	// CPU �̐擪�n���h�����擾
	immutableCounter_.startHandle_.cpu_ = mutableCounter_.startHandle_.cpu_ = descriptorHeap_->GetCPUDescriptorHandleForHeapStart();

	// GPU �̐擪�n���h�����擾
	immutableCounter_.startHandle_.gpu_ = mutableCounter_.startHandle_.gpu_ = descriptorHeap_->GetGPUDescriptorHandleForHeapStart();


	// �S�s�ϋ��e�J�E���g
	UINT AllImmutableCount = ImmutableSRVCount_ + ImmutableUAVCount_ + ImmutableCBVCount_;

	// �s�ϋ��e�J�E���g�������n���h����i�߂�
	mutableCounter_.startHandle_.cpu_.ptr += static_cast<SIZE_T>(incSize_ * AllImmutableCount);
	mutableCounter_.startHandle_.gpu_.ptr += static_cast<SIZE_T>(incSize_ * AllImmutableCount);

}


DescriptorHeap::Handle DescriptorHeap::CreateSRV(
	ID3D12Resource* buff, const D3D12_SHADER_RESOURCE_VIEW_DESC& srvDesc, const bool isMutable)
{
	// SRV�ǉ�
	Handle handle = AddSRV(isMutable);

	// �n���h���̎w���ʒu��SRV�쐬
	spDevice_->CreateShaderResourceView(buff, &srvDesc, handle.cpu_);

	// �n���h����Ԃ�
	return handle;
}

DescriptorHeap::Handle DescriptorHeap::CreateUAV(
	ID3D12Resource* buff, const D3D12_UNORDERED_ACCESS_VIEW_DESC& uavDesc, const bool isMutable)
{
	// UAV�ǉ�
	Handle handle = AddUAV(isMutable);

	// �n���h���̎w���ʒu��UAV�쐬
	spDevice_->CreateUnorderedAccessView(buff, nullptr, &uavDesc, handle.cpu_);

	// �n���h����Ԃ�
	return handle;
}

DescriptorHeap::Handle DescriptorHeap::CreateCBV(
	const D3D12_CONSTANT_BUFFER_VIEW_DESC& cbvDesc, const bool isMutable)
{
	// CBV�ǉ�
	Handle handle = AddCBV(isMutable);

	// �n���h���̎w���ʒu��CBV�쐬
	spDevice_->CreateConstantBufferView(&cbvDesc, handle.cpu_);

	// �n���h����Ԃ�
	return handle;
}

DescriptorHeap::Handle DescriptorHeap::AddSRV(const bool isMutable)
{
	// �s�σJ�E���g�����e�l�𒴂�����e��
	assert(immutableCounter_.srvCount_ < ImmutableSRVCount_);
	// �J�E���g���ő�l�𒴂�����e��
	assert(immutableCounter_.srvCount_ + mutableCounter_.srvCount_ < MaxSRVCount_);


	// �߂�l�p
	Handle handle{};

	// SRV�J�E���g
	UINT srvCount = 0;

	// ���Ɏg���Ă��镪
	UINT alreadyCount = 0;


	// �ςȂ�ϗp
	if (isMutable)
	{
		// �l���
		handle = mutableCounter_.startHandle_;
		srvCount = mutableCounter_.srvCount_;

		// ���e�l��
		alreadyCount = ImmutableSRVCount_;

		// �J�E���g��i�߂�
		mutableCounter_.srvCount_++;
	}
	// ����ȊO�Ȃ�s�ϗp
	else
	{
		// �l���
		handle = immutableCounter_.startHandle_;
		srvCount = immutableCounter_.srvCount_;

		// 0
		alreadyCount = 0;

		// �J�E���g��i�߂�
		immutableCounter_.srvCount_++;
	}

	// SRV�����镪�����n���h����i�߂�
	handle.cpu_.ptr += static_cast<SIZE_T>(incSize_ * (srvCount + alreadyCount));
	handle.gpu_.ptr += static_cast<SIZE_T>(incSize_ * (srvCount + alreadyCount));

	// �n���h����Ԃ�
	return handle;
}

DescriptorHeap::Handle DescriptorHeap::AddUAV(const bool isMutable)
{
	// �s�σJ�E���g�����e�l�𒴂�����e��
	assert(immutableCounter_.uavCount_ < ImmutableUAVCount_);
	// �J�E���g���ő�l�𒴂�����e��
	assert(immutableCounter_.uavCount_ + mutableCounter_.uavCount_ < MaxUAVCount_);


	// �߂�l�p
	Handle handle{};

	// UAV�J�E���g
	UINT uavCount = 0;

	// ���Ɏg���Ă��镪
	UINT alreadyCount = 0;


	// �ςȂ�ϗp
	if (isMutable)
	{
		// �l���
		handle = mutableCounter_.startHandle_;
		uavCount = mutableCounter_.uavCount_;

		// �ő�SRV + ���e�l��
		alreadyCount = MaxSRVCount_ + ImmutableUAVCount_;

		// �J�E���g��i�߂�
		mutableCounter_.uavCount_++;
	}
	// ����ȊO�Ȃ�s�ϗp
	else
	{
		// �l���
		handle = immutableCounter_.startHandle_;
		uavCount = immutableCounter_.uavCount_;

		// �ő�SRV��
		alreadyCount = MaxSRVCount_;

		// �J�E���g��i�߂�
		immutableCounter_.uavCount_++;
	}

	// UAV + �ő�SRV�����镪�����n���h����i�߂�
	handle.cpu_.ptr += static_cast<SIZE_T>(incSize_ * (uavCount + alreadyCount));
	handle.gpu_.ptr += static_cast<SIZE_T>(incSize_ * (uavCount + alreadyCount));

	// �n���h����Ԃ�
	return handle;
}

DescriptorHeap::Handle DescriptorHeap::AddCBV(const bool isMutable)
{
	// �s�σJ�E���g�����e�l�𒴂�����e��
	assert(immutableCounter_.cbvCount_ < ImmutableCBVCount_);
	// �J�E���g���ő�l�𒴂�����e��
	assert(immutableCounter_.cbvCount_ + mutableCounter_.cbvCount_ < MaxCBVCount_);


	// �߂�l�p
	Handle handle{};

	// CBV�J�E���g
	UINT cbvCount = 0;

	// ���Ɏg���Ă��镪
	UINT alreadyCount = 0;


	// �ςȂ�ϗp
	if (isMutable)
	{
		// �l���
		handle = mutableCounter_.startHandle_;
		cbvCount = mutableCounter_.cbvCount_;

		// �ő�SRV + �ő�UAV + ���e�l��
		alreadyCount = MaxSRVCount_ + MaxUAVCount_ + ImmutableCBVCount_;

		// �J�E���g��i�߂�
		mutableCounter_.cbvCount_++;
	}
	// ����ȊO�Ȃ�s�ϗp
	else
	{
		// �l���
		handle = immutableCounter_.startHandle_;
		cbvCount = immutableCounter_.cbvCount_;

		// �ő�SRV + �ő�UAV��
		alreadyCount = MaxSRVCount_ + MaxUAVCount_;

		// �J�E���g��i�߂�
		immutableCounter_.cbvCount_++;
	}

	// CBV + �ő�SRV + �ő�UAV�����镪�����n���h����i�߂�
	handle.cpu_.ptr += static_cast<SIZE_T>(incSize_ * (cbvCount + alreadyCount));
	handle.gpu_.ptr += static_cast<SIZE_T>(incSize_ * (cbvCount + alreadyCount));

	// �n���h����Ԃ�
	return handle;
}

void DescriptorHeap::SetDrawCommand()
{
	// SRV�q�[�v�̐ݒ�R�}���h
	ID3D12DescriptorHeap* ppHeaps[] = { descriptorHeap_.Get() };
	spCmdList_->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
}


void DescriptorHeap::ShowCount()
{
	ImGui::Begin("DescriptorCount");
	
	ImGui::Text("----- Immutable -----");
	{
		ImGui::Text("SRV : %u", immutableCounter_.srvCount_);
		ImGui::Text("UAV : %u", immutableCounter_.uavCount_);
		ImGui::Text("CBV : %u", immutableCounter_.cbvCount_);
	}
	ImGui::Text("----- Mutable -----");
	{
		ImGui::Text("SRV : %u", mutableCounter_.srvCount_);
		ImGui::Text("UAV : %u", mutableCounter_.uavCount_);
		ImGui::Text("CBV : %u", mutableCounter_.cbvCount_);
	}

	ImGui::End();
}