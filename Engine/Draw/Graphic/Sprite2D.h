#pragma once
#include "BaseGraphic.h"
#include "Vertices.h"
#include "Texture.h"
#include "PipelineSetting.h"
#include "Vector3.h"
#include "Vector2.h"

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

	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="pTexs"> : �e�N�X�`���|�C���^�z��</param>
		/// <param name="anchor"> : �A���J�[�|�C���g (�����l�͒��S)</param>
		/// <param name="isFlipX"> : X���]���邩</param>
		/// <param name="isFlipY"> : Y���]���邩</param>
		/// <returns>�X�v���C�g�|�C���^</returns>
		static Sprite2D* Create(
			const std::unordered_map<std::string, Texture*>& pTexs,
			YMath::Vector2 anchor = { 0.5f, 0.5f }, 
			const bool isFlipX = false,
			const bool isFlipY = false);

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
		void SetDrawCommand(std::unordered_map<std::string, uint32_t>& rpIndices) override;

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
		std::unordered_map<std::string, Texture*> pTexs_{};

		// �\�����邩
		bool isVisible_ = true;

	private:

		// �ÓI�X�v���C�g2D�i�[�pvector�z��
		static std::vector<std::unique_ptr<Sprite2D>> sSprites_;
	};
}
