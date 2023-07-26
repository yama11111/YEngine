#pragma once
#include "Model.h"
#include "Object.h"
#include "ConstBuffer.h"
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
		virtual void Initialize(Transform* pParent, const uint32_t drawPriority);

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
		Transform* TransformPtr() const { return transform_.get(); }
	
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
		void SetDrawPriority(const uint32_t drawPriority) { drawPriority_ = drawPriority; }

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
		BaseDrawer(const uint32_t drawPriority);

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="pParent"> : �e�|�C���^</param>
		/// <param name="drawPriority"> : �`��D��x</param>
		BaseDrawer(Transform* pParent, const uint32_t drawPriority);

		virtual ~BaseDrawer() = default;

	protected:

		// �e�g�����X�t�H�[���|�C���^
		Transform* pParent_ = nullptr;

		// �g�����X�t�H�[��
		std::unique_ptr<Transform> transform_;
		
		// �I�u�W�F�N�g
		std::unique_ptr<Object> obj_;

		// ���f���p�g�����X�t�H�[���萔�o�b�t�@
		std::unique_ptr<ConstBuffer<CBModelTransform>> cbTransform_;
		
		// �F�萔�o�b�t�@
		std::unique_ptr<ConstBuffer<CBColor>> cbColor_;

		// �}�e���A���萔�o�b�t�@
		std::unique_ptr<ConstBuffer<CBMaterial>> cbMaterial_;

		// �e�N�X�`���ݒ�萔�o�b�t�@
		std::unique_ptr<ConstBuffer<CBLightGroup>> cbLightGroup_;
		
		// �e�N�X�`���ݒ�萔�o�b�t�@
		std::unique_ptr<ConstBuffer<CBTexConfig>> cbTexConfig_;

		// �`��ʒu
		uint32_t drawPriority_ = 0;

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
