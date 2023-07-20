#pragma once
#include "Transform.h"
#include <string>

namespace YGame
{
	// �m�[�h
	struct Node
	{
	
	public:
	
		// ���O
		std::string name_;


		// ���[�J���g�����X�t�H�[��
		Transform local_;

		// �O���[�o���ό`�s��
		YMath::Matrix4 globalMat_{};


		// �e�m�[�h
		Node* parent_ = nullptr;

	public:

		Node() = default;
		
		~Node() = default;

	};
}