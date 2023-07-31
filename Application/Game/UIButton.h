#pragma once
#include "BaseDrawObject.h"
#include "SlimeActor.h"

namespace YGame
{
	class UIButton :
		public SlimeActor
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="obj"> : �I�u�W�F�N�g (���I�C���X�^���X)</param>
		void Initialize(BaseDrawObject* obj);

		/// <summary>
		/// �X�V
		/// </summary>
		void Update();
		
		/// <summary>
		/// ���� (�u��)
		/// </summary>
		void PressTrigger();
		
		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="shaderTag"> : �V�F�[�_�[�^�O</param>
		/// <param name="priority"> : �`��D��x</param>
		void Draw(const std::string& shaderTag, const uint16_t priority);

	public:

		// �I�u�W�F�N�g
		std::unique_ptr<BaseDrawObject> obj_;
	};
}
