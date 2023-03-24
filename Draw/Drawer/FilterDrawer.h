#pragma once
#include "Model.h"
#include "SlimeActor.h"
#include <array>
#include <memory>

// �t�B���^�[�`��p�R�����N���X
class FilterDrawerCommon
{
protected:
	// �p�[�c�̖��O
	enum class Parts
	{
		Monitor, // ���j�^�[
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

// �t�B���^�[�`��p�N���X
class FilterDrawer :
	private FilterDrawerCommon,
	private YGame::SlimeActor
{
private:
	// �I�u�W�F�N�g (�e)
	std::unique_ptr <YGame::ObjectModel> obj_;
	// ���f���p�I�u�W�F�N�g (�q)
	std::array<std::unique_ptr<YGame::ObjectModel>, PartsNum_> modelObjs_;
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
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="vp"> : �r���[�v���W�F�N�V���� (const �Q��)</param>
	/// <param name="lightGroup"> : ���C�g�O���[�v (�|�C���^)</param>
	void Draw(const YGame::ViewProjection& vp, YGame::LightGroup* lightGroup);
public:
	// �������[�V����
	void IdleAnimation();
	// �F�ւ��A�j���[�V����
	//void ChangeColor(const );
};


