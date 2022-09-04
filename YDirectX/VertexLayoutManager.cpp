#include "VertexLayoutManager.h"

using DX::VertexLayoutManager;

VertexLayoutManager* VertexLayoutManager::GetInstance()
{
	static VertexLayoutManager instance;
	return &instance;
}

VertexLayoutManager::VertexLayoutManager() :
	spriteIL(), modelIL()
{
	//{
	//	 �Z�}���e�B�b�N��,
	//	 ���������Z�}���e�B�b�N��������ꍇ�Ɏg���C���f�b�N�X (0 �ł���),
	//	 �v�f���ƃr�b�g����Ԃ� (float XYZ(3��) -> R32G32B32_FLOAT),
	//	 *���̓X���b�g�C���f�b�N�X (0 �ł���),
	//	 �f�[�^�̃I�t�Z�b�g�l (D3D12_APPEND_ALIGNED_ELEMENT ���Ǝ���),
	//	 *���̓f�[�^��� (�W���� D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA),
	//	 *��x�ɕ`�悷��C���X�^���X�� (0 �ł���)
	//}

	D3D12_INPUT_ELEMENT_DESC layout[3] =
	{
		{
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
		},
		{
			"NORMAL",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
		},
		{
			"TEXCOORD",
			0,
			DXGI_FORMAT_R32G32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
		}
	};

	// ----- sprite ----- //
	spriteIL.push_back(layout[0]);
	spriteIL.push_back(layout[2]);

	// ----- model -----//
	modelIL.push_back(layout[0]);
	modelIL.push_back(layout[1]);
	modelIL.push_back(layout[2]);
}
