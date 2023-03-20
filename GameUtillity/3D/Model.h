#pragma once
#include "ModelCommon.h"
#include "BaseObject.h"
#include "ViewProjection.h"
#include "LightGroup.h"

namespace YGame
{
	// ���f���p�I�u�W�F�N�g
	class ObjectModel : public BaseObject
	{
	public:
		// �萔�o�b�t�@
		YDX::ConstBuffer<ModelCommon::CBData> cBuff_;
	public:
		/// <summary>
		/// ���� + ������
		/// </summary>
		/// <param name="state"> : �ݒ�p�X�e�[�^�X</param>
		/// <param name="(Vector3) state.pos_"> : �ʒu</param>
		/// <param name="(Vector3) state.rota_"> : ��]</param>
		/// <param name="(Vector3) state.scale_"> : �傫��</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static ObjectModel* Create(const Status& state);
	private:
		ObjectModel() = default;
	public:
		~ObjectModel() override = default;
	};

	// ���f���N���X
	class Model : private ModelCommon
	{
	private:
		// ���b�V���z��
		std::vector<Mesh> meshes_;
		// �F
		std::unique_ptr<Color> defColor_;
		
		// ��\��
		bool isInvisible_ = false;
	public:
		// �ǂݍ��ݐݒ�\����
		struct LoadStatus
		{
			std::string directoryPath_;  // �f�B���N�g���p�X
			std::string modelFileName_;  // ���f����
			bool isSmoothing_ = false;   // �X���[�V���O���邩
			bool isInverseU_ = false;    // U���]�ݒ�
			bool isInverseV_ = true;     // V���]�ݒ�
			bool isNormalized_ = false;  // �@���v�Z���邩
			std::string extension_ = ""; // �g���q
		};
	public:
		// ����(������)
		static Model* Create();
		/// <summary>
		/// ���f���ǂݍ���
		/// </summary>
		/// <param name="modelFileName"> : ���f���̃t�H���_�� (obj�Ɠ������O�̎��̂�) </param>
		/// <param name="isSmoothing"> : �X���[�V���O���邩</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static Model* LoadObj(const std::string& modelFileName, const bool isSmoothing);
		/// <summary>
		/// ���f���ǂݍ���(assimp)
		/// </summary>
		/// <param name="state"> �ǂݍ��ݐݒ�</param>
		/// <param name="(string) state.directoryPath_"> : �t�@�C���܂ł̃p�X��</param>
		/// <param name="(string) state.modelFileName_">  :���f���t�@�C����</param>
		/// <param name="(bool) state.isSmoothing_"> : �X���[�V���O���邩</param>
		/// <param name="(bool) state.isInverseU_"> : U���]�ݒ�</param>
		/// <param name="(bool) state.isInverseV_"> : V���]�ݒ�</param>
		/// <param name="(bool) state.isNormalized_"> : �@�����v�Z���邩</param>
		/// <param name="(string) state.extension_"> : �g���q</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static Model* Load(const LoadStatus& state);
	public:
		/// <summary>
		/// �`�� (�e�N�X�`�� + �F �L)
		/// </summary>
		/// <param name="pObj"> : �I�u�W�F�N�g�|�C���^</param>
		/// <param name="vp"> : �r���[�v���W�F�N�V����</param>
		/// <param name="pLightGroup"> : �����O���[�v�|�C���^</param>
		/// <param name="pColor"> : �F�|�C���^</param>
		/// <param name="tex"> : �e�N�X�`���C���f�b�N�X</param>
		void Draw(ObjectModel* pObj, const ViewProjection& vp, LightGroup* pLightGroup, Color* pColor, const UINT tex);
		/// <summary>
		/// �`�� (�e�N�X�`�� �L)
		/// </summary>
		/// <param name="pObj"> : �I�u�W�F�N�g�|�C���^</param>
		/// <param name="vp"> : �r���[�v���W�F�N�V����</param>
		/// <param name="pLightGroup"> : �����O���[�v�|�C���^</param>
		/// <param name="tex"> : �e�N�X�`���C���f�b�N�X</param>
		void Draw(ObjectModel* pObj, const ViewProjection& vp, LightGroup* pLightGroup, const UINT tex);
		/// <summary>
		/// �`�� (�F �L)
		/// </summary>
		/// <param name="pObj"> : �I�u�W�F�N�g�|�C���^</param>
		/// <param name="vp"> : �r���[�v���W�F�N�V����</param>
		/// <param name="pLightGroup"> : �����O���[�v�|�C���^</param>
		/// <param name="pColor"> : �F�|�C���^</param>
		void Draw(ObjectModel* pObj, const ViewProjection& vp, LightGroup* pLightGroup, Color* pColor);
		/// <summary>
		/// �`�� (�f�t�H���g)
		/// </summary>
		/// <param name="pObj"> : �I�u�W�F�N�g�|�C���^</param>
		/// <param name="vp"> : �r���[�v���W�F�N�V����</param>
		/// <param name="pLightGroup"> : �����O���[�v�|�C���^</param>
		void Draw(ObjectModel* pObj, const ViewProjection& vp, LightGroup* pLightGroup);
	public:
		// ��\���ݒ�
		void SetInvisible(const bool isInvisible) { isInvisible_ = isInvisible; }
	private:
		Model() = default;
	public:
		~Model() = default;
	};
}
