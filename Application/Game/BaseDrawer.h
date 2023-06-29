#pragma once
#include "Model.h"
#include "DebugTextAttacher.h"

namespace YGame
{
	class BaseDrawer : 
		public DebugTextAttacher
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="pParent"> : �e�|�C���^</param>
		/// <param name="location"> : �`��ʒu</param>
		virtual void Initialize(Transform* pParent, const DrawLocation location);

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void Update() = 0;

		/// <summary>
		/// �`��
		/// </summary>
		virtual void Draw() = 0;

		/// <summary>
		/// �A�j���[�V�����Đ�
		/// </summary>
		/// <param name="index"> : �A�j���[�V�����ԍ�</param>
		/// <param name="frame"> : �Đ��t���[��</param>
		virtual void PlayAnimation(const uint16_t index, const uint16_t frame) = 0;

		/// <summary>
		/// �e�g�����X�t�H�[���ݒ�
		/// </summary>
		/// <param name="pParent"> : �e�g�����X�t�H�[���|�C���^</param>
		void SetParent(Transform* pParent);
		
		/// <summary>
		/// �`��ʒu�ݒ�
		/// </summary>
		/// <param name="location"> : �`��ʒu</param>
		inline void SetDrawLocation(const DrawLocation location) { location_ = location; }

	public:

		/// <summary>
		/// �f�o�b�O�e�L�X�g�{��
		/// </summary>
		virtual void DrawDebugTextContent() override;

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
		static void StaticInitialize(ViewProjection* pVP);
	
	public:

		BaseDrawer() = default;
		
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="location"> : �`��ʒu</param>
		BaseDrawer(const DrawLocation location);

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="pParent"> : �e�|�C���^</param>
		/// <param name="location"> : �`��ʒu</param>
		BaseDrawer(Transform* pParent, const DrawLocation location);

		virtual ~BaseDrawer() = default;

	protected:

		// �e�g�����X�t�H�[���|�C���^
		Transform* pParent_ = nullptr;

		// 3D�p�I�u�W�F�N�g
		std::unique_ptr<Model::Object> obj_;

		// �F
		std::unique_ptr<CBColor> color_;

		// �}�e���A��
		std::unique_ptr<CBMaterial> material_;

		// �e�N�X�`���ݒ�
		std::unique_ptr<CBTexConfig> texConfig_;

		// ���f���|�C���^
		Model* pModel_ = nullptr;

		// �`��ʒu
		DrawLocation location_;

	protected:

		// �r���[�v���W�F�N�V�����|�C���^
		static ViewProjection* spVP_;
	};
}
