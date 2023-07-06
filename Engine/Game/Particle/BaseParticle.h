//#pragma once
//#include "Model.h"
//#include "Sprite2D.h"
//#include "Sprite3D.h"
//#include "Lerp.h"
//#include "Timer.h"
//#include "Power.h"
//
//namespace YGame
//{
//	// �p�[�e�B�N�����N���X
//	class BaseParticle
//	{
//	
//	public:
//
//		/// <summary>
//		/// ������
//		/// </summary>
//		/// <param name="aliveFrame"> : �������� (F)</param>
//		/// <param name="locaiton"> : �`��ꏊ</param>
//		void Initialize(const uint32_t aliveFrame, const DrawLocation location);
//
//		/// <summary>
//		/// �X�V
//		/// </summary>
//		virtual void Update() = 0;
//
//		/// <summary>
//		/// �`��
//		/// </summary>
//		virtual void Draw() = 0;
//
//		/// <summary>
//		/// �����t���O�擾
//		/// </summary>
//		/// <returns>�����t���O</returns>
//		virtual bool IsAlive() const { return isAlive_; }
//	
//	public:
//
//		BaseParticle() = default;
//
//		/// <summary>
//		/// �R���X�g���N�^
//		/// </summary>
//		/// <param name="aliveFrame"> : �������� (F)</param>
//		/// <param name="locaiton"> : �`��ꏊ</param>
//		BaseParticle(const uint32_t aliveFrame, const DrawLocation location);
//
//		virtual ~BaseParticle() = default;
//	
//	protected:
//		
//		// �����t���O
//		bool isAlive_ = false;
//		
//		// �����^�C�}�[
//		YMath::Timer aliveTimer_;
//		
//		// �`��ꏊ
//		DrawLocation location_;
//	
//	protected:
//
//		/// <summary>
//		/// �����X�V
//		/// </summary>
//		/// <returns> : �����Ă��邩</returns>
//		void UpdateLife();
//
//	};
//
//	// �p�[�e�B�N�����N���X (Model)
//	class BaseParticleForModel : public BaseParticle
//	{
//
//	public:
//
//		/// <summary>
//		/// ������
//		/// </summary>
//		/// <param name="aliveFrame"> : �������� (F)</param>
//		/// <param name="status"> : �g�����X�t�H�[�����</param>
//		/// <param name="pModel"> : ���f���|�C���^</param>
//		/// <param name="locaiton"> : �`��ꏊ</param>
//		void Initialize(
//			const uint32_t aliveFrame,
//			const Transform::Status& status,
//			Model* pModel, const DrawLocation location);
//
//		/// <summary>
//		/// �X�V
//		/// </summary>
//		virtual void Update() override = 0;
//
//		/// <summary>
//		/// �`��
//		/// </summary>
//		virtual void Draw() override = 0;
//	
//	public:
//
//		/// <summary>
//		/// �ÓI������
//		/// </summary>
//		/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
//		static void StaticInitialize(ViewProjection* pVP);
//	
//	public:
//
//		BaseParticleForModel() = default;
//
//		/// <summary>
//		/// �R���X�g���N�^
//		/// </summary>
//		/// <param name="aliveFrame"> : �������� (F)</param>
//		/// <param name="status"> : �g�����X�t�H�[�����</param>
//		/// <param name="pModel"> : ���f���|�C���^</param>
//		/// <param name="locaiton"> : �`��ꏊ</param>
//		BaseParticleForModel(
//			const uint32_t aliveFrame,
//			const Transform::Status& status,
//			Model* pModel, const DrawLocation location);
//
//		virtual ~BaseParticleForModel() = default;
//	
//	protected:
//		
//		// �I�u�W�F�N�g
//		std::unique_ptr<Model::Object> obj_;
//
//		// ���f���|�C���^
//		Model* pModel_ = nullptr;
//	
//	protected:
//		
//		// �r���[�v���W�F�N�V�����|�C���^
//		static ViewProjection* spVP_;
//	
//	};
//
//	// �p�[�e�B�N�����N���X (Sprite2D)
//	class BaseParticleForSprite2D : public BaseParticle
//	{
//
//	protected:
//
//		// �I�u�W�F�N�g
//		std::unique_ptr<Sprite2D::Object> obj_;
//
//		// �X�v���C�g2D�|�C���^
//		Sprite2D* pSprite2D_ = nullptr;
//
//	public:
//
//		/// <summary>
//		/// ������
//		/// </summary>
//		/// <param name="aliveFrame"> : �������� (F)</param>
//		/// <param name="status"> : �g�����X�t�H�[�����</param>
//		/// <param name="pSprite2D"> : �X�v���C�g2D�|�C���^</param>
//		/// <param name="locaiton"> : �`��ꏊ</param>
//		void Initialize(
//			const uint32_t aliveFrame,
//			const Transform::Status& status,
//			Sprite2D* pSprite2D, const DrawLocation location);
//
//		/// <summary>
//		/// �X�V
//		/// </summary>
//		virtual void Update() override = 0;
//
//		/// <summary>
//		/// �`��
//		/// </summary>
//		virtual void Draw() override = 0;
//
//	public:
//
//		/// <summary>
//		/// �ÓI������
//		/// </summary>
//		static void StaticInitialize();
//
//	public:
//
//		virtual ~BaseParticleForSprite2D() = default;
//
//	};
//
//	// �p�[�e�B�N�����N���X (Sprite3D)
//	class BaseParticleForSprite3D : public BaseParticle
//	{
//
//	protected:
//
//		// �I�u�W�F�N�g
//		std::unique_ptr<Sprite3D::Object> obj_;
//
//		// �X�v���C�g3D�|�C���^
//		Sprite3D* pSprite3D_ = nullptr;
//	
//	public:
//
//		/// <summary>
//		/// �I�u�W�F�N�g����
//		/// </summary>
//		/// <param name="isXAxisBillboard"> : X���r���{�[�h</param>
//		/// <param name="isYAxisBillboard"> : Y���r���{�[�h</param>
//		void CreateObject(const bool isXAxisBillboard, const bool isYAxisBillboard);
//
//		/// <summary>
//		/// �X�V
//		/// </summary>
//		virtual void Update() override = 0;
//
//		/// <summary>
//		/// �`��
//		/// </summary>
//		virtual void Draw() override = 0;
//
//	protected:
//
//		// �r���[�v���W�F�N�V�����|�C���^
//		static YGame::ViewProjection* spVP_;
//
//	public:
//
//		/// <summary>
//		/// �ÓI������
//		/// </summary>
//		/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
//		static void StaticInitialize(YGame::ViewProjection* pVP);
//
//	public:
//
//		virtual ~BaseParticleForSprite3D() = default;
//
//	};
//}
