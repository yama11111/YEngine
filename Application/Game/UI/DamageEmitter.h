#pragma once
#include "UINumber.h"
#include "CBColor.h"
#include "ConstBufferObject.h"
#include "Ease.h"
#include "Timer.h"
#include <array>
#include <memory>

namespace YGame
{
	class DamageEmitter final
	{

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
		static void Initialize(ViewProjection* pVP);

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="pos"></param>
		/// <param name="damageVal"></param>
		static void Emit(const YMath::Vector3& pos, const uint32_t damageVal);

		/// <summary>
		/// �X�V
		/// </summary>
		static void Update();

		/// <summary>
		/// �`��
		/// </summary>
		static void Draw();

	private:

		class Damage final
		{

		public:

			/// <summary>
			/// ������
			/// </summary>
			void Initialize(ViewProjection* pVP);

			/// <summary>
			/// ���Z�b�g (���g����������)
			/// </summary>
			void Reset();

			/// <summary>
			/// �X�V
			/// </summary>
			void Update();

			/// <summary>
			/// �`��
			/// </summary>
			void Draw();

		public:

			/// <summary>
			/// �_���[�W����
			/// </summary>
			/// <param name="pos"> : �ʒu</param>
			/// <param name="damageValue"> : �_���[�W��</param>
			void Pop(const YMath::Vector3& pos, const uint32_t damageValue);

			/// <summary>
			/// ���쒆��
			/// </summary>
			/// <returns>����t���O</returns>
			inline bool IsAct() const { return isAct_; }

		private:

			// �g�����X�t�H�[��
			Transform trfm_;

			// X���r���{�[�h�t���O
			bool isXBillboard_ = false;

			// Y���r���{�[�h�t���O
			bool isYBillboard_ = false;

			// ����
			std::unique_ptr<UINumber> uiNum_;

			// �F
			std::unique_ptr<ConstBufferObject<CBColor>> cbColor_;


			// ����t���O
			bool isAct_ = false;

			// �����^�C�}�[
			YMath::Timer popTim_;

			// �㏸�C�[�W���O
			YMath::Ease<float> upEas_;

			// �X�P�[���C�[�W���O
			YMath::Ease<float> popScaEas_;

			// �c���^�C�}�[
			YMath::Timer remainTim_;

			// �����^�C�}�[
			YMath::Timer vanishTim_;

			// �A���t�@�l�C�[�W���O
			YMath::Ease<float> vanishAlphaEas_;
		};

	private:

		// �_���[�W�z��
		static std::array<Damage, 10> damage_;

		// �r���[�v���W�F�N�V�����|�C���^
		static ViewProjection* spVP_;

	};
}
