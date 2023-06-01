#pragma once
#include "Sprite2D.h"
#include <array>

namespace YGame
{
	class LetterBoxDrawerCommon
	{
	
	protected:
	
		// �ÓI�X�v���C�g
		static Sprite2D* spSpr_;
	
	public:
		
		
		/// <summary>
		/// �ÓI������
		/// </summary>
		static void StaticInitialize();
	
	public:
		
		virtual ~LetterBoxDrawerCommon() = default;
	
	};

	class LetterBoxDrawer : private LetterBoxDrawerCommon
	{
	
	private:
		
		// �X�v���C�g�I�u�W�F�N�g
		std::array<std::unique_ptr<Sprite2D::Object>, 2> sprObjs_;
		
		// �F
		std::unique_ptr<CBColor> color_;

		
		// ���� (��)
		float topHeight_ = 0.0f;
		
		// ���� (��)
		float bottomHeight_ = 0.0f;
	
	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="topHeight"> : �㑤�̍���</param>
		/// <param name="bottoomHeight"> : �����̍���</param>
		void Initialize(const float topHeight, const float bottomHeight);
		
		/// <summary> 
		/// ���Z�b�g (���g����������)
		/// </summary>
		void Reset();
		
		/// <summary> 
		/// �X�V
		/// </summary>
		void Update();
		
		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="locaiton"> : �`��ꏊ</param>	
		void Draw(const DrawLocation& location);
	
	public:
		
		~LetterBoxDrawer() = default;
	
	};
}