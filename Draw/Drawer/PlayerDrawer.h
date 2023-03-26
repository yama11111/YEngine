#pragma once
#include "Model.h"
#include "SlimeActor.h"
#include <array>
#include <memory>

// �v���C���[�`��p�R�����N���X
class PlayerDrawerCommon
{
protected:
	// �p�[�c�̖��O
	enum class Parts
	{
		Body, // ��
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

// �v���C���[�`��p�N���X
class PlayerDrawer :
	private PlayerDrawerCommon,
	private YGame::SlimeActor
{
private:
	// �g�����X�t�H�[�� 
	std::unique_ptr<YGame::Transform> transform_;
	// ���f���p�I�u�W�F�N�g (�q)
	std::array<std::unique_ptr<YGame::ModelObject>, PartsNum_> modelObjs_;
	// �����|�C���^
	YMath::Vector3* pDirection_ = nullptr;
	// �������[�V�����p�^�C�}�[
	YMath::Timer idelTim_;
public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pParent"> : �e�s��|�C���^ (���̍s��ɒǏ]����)</param>
	/// <param name="pDirection"> : �����|�C���^ (���̌����Ɍ���)</param>
	void Initialize(YMath::Matrix4* pParent, YMath::Vector3* pDirection);
	// ���Z�b�g (���g����������)
	void Reset();
	// �X�V
	void Update();
	// �`��
	void Draw();
public:
	// �������[�V����
	void IdleAnimation();
	// �W�����v���[�V����
	void JumpAnimation();
	// ���n���[�V����
	void LandingAnimation();
	// �F�ւ��A�j���[�V����
	//void ChangeColor(const );
};

