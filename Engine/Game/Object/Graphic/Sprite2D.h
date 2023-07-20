#pragma once
#include "BaseGraphic.h"
#include "Vertices.h"
#include "Texture.h"
#include "PipelineSetting.h"
#include "Vector3.h"
#include "Vector2.h"
#include <list>
#include <array>

namespace YGame
{
	// �X�v���C�g2D
	class Sprite2D :
		public BaseGraphic
	{

	public:

		// ���_�f�[�^�\����
		struct VData
		{
			YMath::Vector3 pos_; // xyz���W
			YMath::Vector2 uv_;  // uv���W
		};

		// �ݒ�p�X�e�[�^�X
		struct Status
		{
			bool isDiv_ = true; // �摜�T�C�Y�ɍ��킹�邩
			YMath::Vector2 size_; // �T�C�Y
			YMath::Vector2 anchor_ = { 0.5f, 0.5f }; // �A���J�[�|�C���g
			bool isFlipX_ = false; // ���E���]
			bool isFlipY_ = false; // �㉺���]
		};

		// �e�N�X�`���ݒ�p�X�e�[�^�X
		struct TexStatus
		{
			Texture* pTex_; // �e�N�X�`���|�C���^
			bool isDiv_ = true; // �摜�T�C�Y�ɍ��킹�邩
			YMath::Vector2 leftTop_ = { 0.0f,0.0f }; // �e�N�X�`������
			YMath::Vector2 size_ = { 0.0f,0.0f }; // �e�N�X�`���T�C�Y
		};

	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="status"> : �X�v���C�g�ݒ�</param>
		/// <param name="(bool) isDiv_"> : �摜�T�C�Y�ɍ��킹�邩</param>
		/// <param name="(Vector2) status.size_"> : �傫��</param>
		/// <param name="(Vector2) status.anchor_"> : �A���J�[�|�C���g (�����l�͒��S)</param>
		/// <param name="(bool) status.isFlipX_"> : X���]���邩</param>
		/// <param name="(bool) status.isFlipY_"> : Y���]���邩</param>
		/// <param name="--------------------------------"></param>
		/// <param name="texStatus"> : �e�N�X�`���ݒ�</param>
		/// <param name="(Texture*) texStatus.pTex_"> : �e�N�X�`���|�C���^</param>
		/// <param name="(bool) isDiv_"> : �摜�T�C�Y�ɍ��킹�邩</param>
		/// <param name="(Vector2) texStatus.leftTop_"> : �e�N�X�`������</param>
		/// <param name="(Vector2) texStatus.size_"> : �e�N�X�`���T�C�Y</param>
		/// <param name="--------------------------------"></param>
		/// <returns>�X�v���C�g�|�C���^</returns>
		static Sprite2D* Create(const Status& status, const TexStatus& texStatus);

		/// <summary>
		/// �S�폜
		/// </summary>
		static void AllClear();

		/// <summary>
		/// ���f���p�̃p�C�v���C���ݒ�擾
		/// </summary>
		/// <returns>�p�C�v���C���ݒ�</returns>
		static PipelineSetting GetPipelineSetting();

	public:

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="rpIndices"> : ���[�g�p�����[�^��� + �ԍ�</param>
		void SetDrawCommand(std::unordered_map<std::string, uint32_t>& rpIndices) const override;

	public:

		Sprite2D() = default;

		~Sprite2D() = default;

	private:

		// ���_�f�[�^
		YDX::Vertices<VData> vt_;


		// �T�C�Y
		YMath::Vector2 size_;

		// �A���J�[�|�C���g
		YMath::Vector2 anchor_;

		// ���E���]
		bool isFlipX_ = false;

		// �㉺���]
		bool isFlipY_ = false;


		// �e�N�X�`��
		Texture* pTex_ = nullptr;

		// �e�N�X�`������
		YMath::Vector2 texLeftTop_;

		// �e�N�X�`���T�C�Y
		YMath::Vector2 texSize_;

		// �\�����邩
		bool isVisible_ = true;

	private:

		// �ÓI�X�v���C�g2D�i�[�pvector�z��
		static std::vector<std::unique_ptr<Sprite2D>> sSprites_;
	};
}
