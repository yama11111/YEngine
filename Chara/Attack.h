//#pragma once
//#include "Collider.h"
//#include "Timer.h"
//
//class Attack : public YGame::Collider 
//{
//private:
//	// �ʒu
//	YMath::Vector3 pos_;
//	// �@�\�^�C�}�[
//	YMath::Timer actTimer_;
//	// �����Ă��邩
//	bool isAct_ = false;
//public:
//	// �������X�e�[�^�X
//	struct InitStatus 
//	{
//		YMath::Vector3 pos_; // �ʒu
//		float rad_; // ���a
//		uint32_t attribute_; // ���� (����)
//		uint32_t mask_; // �}�X�N (����)
//		uint32_t actFrame_; // ����
//	};
//public:
//	// ������
//	void Initialize(const InitStatus& state);
//	// �X�V
//	void Update();
//public:
//	// �ʒu�擾
//	YMath::Vector3 Pos() const override { return pos_; }
//	// �����Ă��邩
//	bool IsAct() const { return isAct_; }
//};
//
