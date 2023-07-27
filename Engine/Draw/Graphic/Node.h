#pragma once
#include "Transform.h"
#include <string>

namespace YGame
{
	// ノード
	struct Node
	{
	
	public:
	
		// 名前
		std::string name_;


		// ローカルトランスフォーム
		Transform local_;

		// グローバル変形行列
		YMath::Matrix4 globalMat_{};


		// 親ノード
		Node* parent_ = nullptr;

	public:

		Node() = default;
		
		~Node() = default;

	};
}