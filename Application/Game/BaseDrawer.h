#pragma once
#include "Model.h"
#include "DrawObjectForModel.h"
#include "ConstBufferObject.h"
#include "ViewProjection.h"
#include "DebugTextAttacher.h"
#include "Timer.h"

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
		/// �A�j���[�V�����Đ�
		/// </summary>
		/// <param name="index"> : �A�j���[�V�����ԍ�</param>
		/// <param name="frame"> : �Đ��t���[��</param>
		/// <param name="isRoop"> : ���[�v���邩</param>
		void PlayAnimation(const uint16_t index, const uint32_t frame, const bool isRoop = false);

		/// <summary>
		/// �A�j���[�V��������߂�
		/// </summary>
		/// <param name="index"> : �A�j���[�V�����ԍ�</param>
		void AbortAnimation(const uint16_t index);

		/// <summary>
		/// �`��
		/// </summary>
		virtual void Draw();

		/// <summary>
		/// �f�o�b�O�e�L�X�g�{��
		/// </summary>
		virtual void DrawDebugTextContent() override;

	public:

		/// <summary>
		/// �g�����X�t�H�[���|�C���^�擾
		/// </summary>
		/// <returns>�g�����X�t�H�[���|�C���^</returns>
		Transform* TransformPtr() const { return &obj_->transform_; }
		
		/// <summary>
		/// �e�g�����X�t�H�[���ݒ�
		/// </summary>
		/// <param name="pParent"> : �e�g�����X�t�H�[���|�C���^</param>
		virtual void SetParent(Transform* pParent);

		/// <summary>
		/// �I�t�Z�b�g�ݒ�
		/// </summary>
		/// <param name="offset"> : �I�t�Z�b�g</param>
		void SetOffset(const YMath::Vector3& offset) { offset_ = offset; }
		
		/// <summary>
		/// �`��ʒu�ݒ�
		/// </summary>
		/// <param name="drawPriority"> : �`��D��x</param>
		void SetDrawPriority(const uint16_t drawPriority) { drawPriority_ = drawPriority; }

		/// <summary>
		/// �`�悷�邩
		/// </summary>
		/// <param name="isVisible"> : �`�悷�邩</param>
		void SetIsVisible(const bool isVisible) { isVisible_ = isVisible; }

		/// <summary>
		/// �`��X�V���邩
		/// </summary>
		/// <param name="isVisibleUpdate"> : �`��X�V���邩</param>
		void SetIsVisibleUpdate(const bool isVisibleUpdate) { isVisibleUpdate_ = isVisibleUpdate; }
	
	public:

		BaseDrawer() = default;

		virtual ~BaseDrawer() = default;

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
		static void StaticInitialize(ViewProjection* pVP);

	protected:

		// �A�j���[�V�����p�^�C�}�[
		struct AnimationTimer
		{
			// �^�C�}�[
			YMath::Timer timer;

			// ���[�v���邩
			bool isRoop = false;
		};
	
	protected:

		// �e�g�����X�t�H�[���|�C���^
		Transform* pParent_ = nullptr;

		// �I�t�Z�b�g
		YMath::Vector3 offset_;
		
		// �I�u�W�F�N�g
		std::unique_ptr<DrawObjectForModel> obj_;
		
		// �F�萔�o�b�t�@
		std::unique_ptr<ConstBufferObject<CBColor>> cbColor_;

		// �}�e���A���萔�o�b�t�@
		std::unique_ptr<ConstBufferObject<CBMaterial>> cbMaterial_;

		// �`��ʒu
		uint16_t drawPriority_ = 0;

		// �V�F�[�_�[
		std::string shaderKey_ = "ModelDefault";

		// �`��t���O
		bool isVisible_ = true;
		
		// �`��X�V�t���O
		bool isVisibleUpdate_ = true;

		// �A�j���[�V�����r�b�g�t���O
		uint16_t animationBitFlag_ = 0;

		// �A�j���[�V�����^�C�}�[�}�b�v
		std::unordered_map<uint16_t, AnimationTimer> animationTimers_;

		// �A�j���[�V�����ϓ��l
		Transform::Status animeStatus_;

	protected:

		// �r���[�v���W�F�N�V�����|�C���^
		static ViewProjection* spVP_;

	protected:

		/// <summary>
		/// �A�j���[�V�����^�C�}�[�}��
		/// </summary>
		virtual void InsertAnimationTimers() = 0;

		/// <summary>
		/// �T�u�A�j���[�V�����Đ�
		/// </summary>
		/// <param name="index"> : �A�j���[�V�����ԍ�</param>
		/// <param name="frame"> : �Đ��t���[��</param>
		virtual void PlaySubAnimation(const uint16_t index, const uint32_t frame) = 0;

		/// <summary>
		/// �A�j���[�V�����^�C�}�[�X�V
		/// </summary>
		void UpdateAnimationTimer();

		/// <summary>
		/// �A�j���[�V�����X�V
		/// </summary>
		virtual void UpdateAnimtion() = 0;

		/// <summary>
		/// �`�悷�邩�X�V
		/// </summary>
		void VisibleUpdate();

	};
}
