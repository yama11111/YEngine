#pragma once
#include "Vec2.h"
#include "Vec3.h"

class MapChipCollider
{
private:
	Math::Vec3 scale_; // �傫��
	bool isLanding_ = false; // �n��ɂ��邩
public:
	struct InitStatus
	{
		Math::Vec3 scale_; // �傫��
		bool isLanding_ = false; // �n��ɂ��邩
	};
public:
	// �}�b�v�Փːݒ菉����
	void InitializeMapCollisionStatus(const InitStatus& state);
public:
	// �ʒu�擾 (�Q��)
	virtual Math::Vec3& PosRef() = 0;
	// �傫���擾
	Math::Vec3 Scale() const { return scale_; }
	// �X�s�[�h�擾 (�Q��)
	virtual Math::Vec3& SpeedRef() = 0;
	// �n��ɂ��邩
	bool IsLanding() const { return isLanding_; }
	// �n��t���O�ݒ�
	void SetIsLanding(const bool isLanding) { isLanding_ = isLanding; };
};

