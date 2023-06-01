#pragma once
#include "Model.h"
#include "Sprite3D.h"
#include "Lerp.h"
#include "Timer.h"
#include "Power.h"

namespace YGame
{
	// �p�[�e�B�N�����N���X
	class IParticle
	{
	
	public:

		// �����t���O
		bool isAlive_ = false;
	
	protected:
		
		// �����^�C�}�[
		YMath::Timer aliveTim_;
		
		// �`��ꏊ
		DrawLocation location_;

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="aliveTime"> : ��������</param>
		/// <param name="locaiton"> : �`��ꏊ</param>
		void Initialize(const uint32_t aliveTime, const DrawLocation& location);

		/// <summary>
		/// �����X�V
		/// </summary>
		/// <returns> : �����Ă��邩</returns>
		bool UpdateLife();

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void Update() = 0;

		/// <summary>
		/// �`��
		/// </summary>
		virtual void Draw() = 0;
	
	public:

		virtual ~IParticle() = default;

	};

	// ���f���p�p�[�e�B�N�����N���X
	class IParticleModel : public IParticle
	{
	
	protected:
		
		// �I�u�W�F�N�g
		std::unique_ptr<Model::Object> obj_;

		// �F
		std::unique_ptr<CBColor> color_;


		// ���f���|�C���^
		Model* pModel_ = nullptr;

	public:

		/// <summary>
		/// �I�u�W�F�N�g����
		/// </summary>
		void CreateObject();

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void Update() override = 0;

		/// <summary>
		/// �`��
		/// </summary>
		virtual void Draw() override = 0;
	
	protected:
		
		// �r���[�v���W�F�N�V�����|�C���^
		static YGame::ViewProjection* spVP_;
	
	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
		static void StaticInitialize(YGame::ViewProjection* pVP);
	
	public:

		virtual ~IParticleModel() = default;
	
	};

	// �p�[�e�B�N�����N���X
	class IParticleSprite3D : public IParticle
	{

	public:

		// �����t���O
		bool isAlive_ = false;

	protected:

		// �I�u�W�F�N�g
		std::unique_ptr<Sprite3D::Object> obj_;

		// �F
		std::unique_ptr<CBColor> color_;


		// �X�v���C�g3D�|�C���^
		Sprite3D* pSprite3D_ = nullptr;
	
	public:

		/// <summary>
		/// �I�u�W�F�N�g����
		/// </summary>
		/// <param name="isXAxisBillboard"> : X���r���{�[�h</param>
		/// <param name="isYAxisBillboard"> : Y���r���{�[�h</param>
		void CreateObject(const bool isXAxisBillboard, const bool isYAxisBillboard);

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void Update() override = 0;

		/// <summary>
		/// �`��
		/// </summary>
		virtual void Draw() override = 0;

	protected:

		// �r���[�v���W�F�N�V�����|�C���^
		static YGame::ViewProjection* spVP_;

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
		static void StaticInitialize(YGame::ViewProjection* pVP);

	public:

		virtual ~IParticleSprite3D() = default;

	};
}
