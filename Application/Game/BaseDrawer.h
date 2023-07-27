#pragma once
#include "Model.h"
#include "DrawObjectForModel.h"
#include "ConstBufferObject.h"
#include "ViewProjection.h"
#include "DebugTextAttacher.h"

#include "CBModelTransform.h"
#include "CBColor.h"
#include "CBMaterial.h"
#include "CBLightGroup.h"
#include "CBTexConfig.h"

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
		/// <param name="drawPriority"> : �`��D��x</param>
		virtual void Initialize(Transform* pParent, const uint16_t drawPriority);

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void Update();

		/// <summary>
		/// �`��
		/// </summary>
		virtual void Draw();

		/// <summary>
		/// �f�o�b�O�e�L�X�g�{��
		/// </summary>
		virtual void DrawDebugTextContent() override;

		/// <summary>
		/// �A�j���[�V�����Đ�
		/// </summary>
		/// <param name="index"> : �A�j���[�V�����ԍ�</param>
		/// <param name="frame"> : �Đ��t���[��</param>
		virtual void PlayAnimation(const uint16_t index, const uint32_t frame) = 0;

	public:

		/// <summary>
		/// �g�����X�t�H�[���|�C���^�擾
		/// </summary>
		/// <returns>�g�����X�t�H�[���|�C���^</returns>
		Transform* TransformPtr() const { return &obj_->transform_; }
	
	public:
		
		/// <summary>
		/// �e�g�����X�t�H�[���ݒ�
		/// </summary>
		/// <param name="pParent"> : �e�g�����X�t�H�[���|�C���^</param>
		void SetParent(Transform* pParent);
		
		/// <summary>
		/// �`��ʒu�ݒ�
		/// </summary>
		/// <param name="drawPriority"> : �`��D��x</param>
		void SetDrawPriority(const uint16_t drawPriority) { drawPriority_ = drawPriority; }

		/// <summary>
		/// �`�悷�邩�X�V���邩
		/// </summary>
		/// <param name="isVisibleUpdate"> : �`�悷�邩�X�V���邩</param>
		void SetIsVisibleUpdate(const bool isVisibleUpdate) { isVisibleUpdate_ = isVisibleUpdate; }

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
		/// <param name="drawPriority"> : �`��D��x</param>
		BaseDrawer(const uint16_t drawPriority);

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="pParent"> : �e�|�C���^</param>
		/// <param name="drawPriority"> : �`��D��x</param>
		BaseDrawer(Transform* pParent, const uint16_t drawPriority);

		virtual ~BaseDrawer() = default;

	protected:

		// �e�g�����X�t�H�[���|�C���^
		Transform* pParent_ = nullptr;
		
		// �I�u�W�F�N�g
		std::unique_ptr<DrawObjectForModel> obj_;
		
		// �F�萔�o�b�t�@
		std::unique_ptr<ConstBufferObject<CBColor>> cbColor_;

		// �}�e���A���萔�o�b�t�@
		std::unique_ptr<ConstBufferObject<CBMaterial>> cbMaterial_;

		// �e�N�X�`���ݒ�萔�o�b�t�@
		std::unique_ptr<ConstBufferObject<CBLightGroup>> cbLightGroup_;
		
		// �e�N�X�`���ݒ�萔�o�b�t�@
		std::unique_ptr<ConstBufferObject<CBTexConfig>> cbTexConfig_;

		// �`��ʒu
		uint16_t drawPriority_ = 0;

		// �V�F�[�_�[
		std::string shaderKey_ = "ModelDefault";

		// �`��t���O
		bool isVisible_ = true;
		
		// �`�悷�邩�X�V�t���O
		bool isVisibleUpdate_ = true;

		// �A�j���[�V�����r�b�g�t���O
		uint16_t animationBitFlag_ = 0;

		// �A�j���[�V�����ϓ��l
		Transform::Status animeStatus_;

	protected:

		// �r���[�v���W�F�N�V�����|�C���^
		static ViewProjection* spVP_;

	protected:

		/// <summary>
		/// �`�悷�邩�X�V
		/// </summary>
		void VisibleUpdate();
	};
}
