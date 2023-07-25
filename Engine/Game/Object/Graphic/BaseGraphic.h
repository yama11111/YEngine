#pragma once
#include <unordered_map>
#include <cstdint>
#include <memory>
#include <string>

namespace YGame
{
	// �O���t�B�b�N�X���N���X
	class BaseGraphic
	{

	public:
		
		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="rpIndices"> : ���[�g�p�����[�^��� + �ԍ�</param>
		virtual void SetDrawCommand(std::unordered_map<std::string, uint32_t>& rpIndices) = 0;

		/// <summary>
		/// �\�����邩�ݒ�
		/// </summary>
		/// <param name="isVisible"> : �\�����邩</param>
		void SetIsVisible(const bool isVisible) { isVisible_ = isVisible; }
	
	public:

		BaseGraphic() = default;
		
		virtual ~BaseGraphic() = default;

	protected:

		// �t�@�C���p�X
		std::string fileName_;

		// �\�����邩
		bool isVisible_ = true;
	
	};
}
