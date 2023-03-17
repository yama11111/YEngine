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
	static std::array<std::unique_ptr<YGame::Model>, PartsNum_> models_;
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
	// �I�u�W�F�N�g (�e)
	std::unique_ptr <YGame::ObjectModel> obj_;
	// ���f���p�I�u�W�F�N�g (�q)
	std::array<std::unique_ptr<YGame::ObjectModel>, PartsNum_> modelObjs_;
	// �����|�C���^
	YMath::Vector3* pDirection_ = nullptr;
	// �������[�V�����p�^�C�}�[
	YMath::Timer idelTim_;
public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pParent"> : �e�s��|�C���^ (���̍s��ɒǏ]����)</param>
	void Initialize(YMath::Matrix4* pParent, YMath::Vector3* pDirection);
	// ���Z�b�g (���g����������)
	void Reset();
	// �X�V
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="vp"> : �r���[�v���W�F�N�V���� (const �Q��)</param>
	/// <param name="lightGroup"> : ���C�g�O���[�v (�|�C���^)</param>
	void Draw(const YGame::ViewProjection& vp, YGame::LightGroup* lightGroup);
public:
	// �������[�V����
	void IdleAnimation();
	// ���n���[�V����
	void LandingAnimation();
	// �W�����v���[�V����
	void JumpAnimation();
	// �F�ւ��A�j���[�V����
	//void ChangeColor(const );
};

