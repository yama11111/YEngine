#pragma once
#include "Model.h"
#include "SlimeActor.h"
#include <array>
#include <memory>

// �Q�[�g�`��p�R�����N���X
class GateDrawerCommon
{
protected:
	// �p�[�c�̖��O
	enum class Parts
	{
		Frame, // �g
	};
protected:
	// �p�[�c�̑���
	static const size_t PartsNum_ = 2;
protected:
	// ���f�� (�p�[�c�̐�����)
	static std::array<std::unique_ptr<YGame::Model>, PartsNum_> sModels_;
public:
	// �ÓI������
	static void StaticInitialize();
};

// �Q�[�g�`��p�N���X
class GateDrawer :
	private GateDrawerCommon,
	private YGame::SlimeActor
{
private:
	// �g�����X�t�H�[�� 
	std::unique_ptr<YGame::Transform> transform_;
	// ���f���p�I�u�W�F�N�g (�q)
	std::array<std::unique_ptr<YGame::ModelObject>, PartsNum_> modelObjs_;
	// �������[�V�����p�^�C�}�[
	YMath::Timer idelTim_;
public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pParent"> : �e�s��|�C���^ (���̍s��ɒǏ]����)</param>
	void Initialize(YMath::Matrix4* pParent);
	// ���Z�b�g (���g����������)
	void Reset();
	// �X�V
	void Update();
	// �`��
	void Draw();
public:
	// �������[�V����
	void IdleAnimation();
	// �F�ւ��A�j���[�V����
	//void ChangeColor(const );
};

