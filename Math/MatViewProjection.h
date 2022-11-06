#pragma once
#include "MatView.h"
#include "MatProjection.h"

namespace Math
{
	class MatViewProjection
	{
	public:
		// �r���[
		MatView view_;
		// �v���W�F�N�V����
		MatProjection pro_;
	public:
		// �R���X�g���N�^
		MatViewProjection();
		// �R���X�g���N�^ (�����L)
		MatViewProjection(const MatView::InitStatus& init);
		// ������
		void Initialize(const MatView::InitStatus& init);
		// �r���[�s��v�Z
		void Update();
	};
}
