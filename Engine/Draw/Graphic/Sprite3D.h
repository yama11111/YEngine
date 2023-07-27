#pragma once
#include "BaseGraphic.h"
#include "Vertices.h"
#include "Texture.h"
#include "PipelineSetting.h"
#include "Vector3.h"

namespace YGame
{
	// �X�v���C�g3D (�r���{�[�h)
	class Sprite3D :
		public BaseGraphic
	{

	public:

		// ���_�f�[�^
		struct VData
		{
			YMath::Vector3 pos_; // xyz���W
		};

	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="pTexs"> : �e�N�X�`���|�C���^�z��</param>
		/// <returns>�X�v���C�g�|�C���^</returns>
		static Sprite3D* Create(const std::unordered_map<std::string, Texture*>& pTexs);

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

		Sprite3D() = default;

		~Sprite3D() = default;

	private:

		// �e�N�X�`��
		std::unordered_map<std::string, Texture*> pTexs_{};

	private:

		// ���_�f�[�^
		static YDX::Vertices<VData> vt_;

		// �������t���O
		static bool isInitVertices_;

		// �ÓI�X�v���C�g3D�i�[�pvector�z��
		static std::vector<std::unique_ptr<Sprite3D>> sSprites_;
	};
}

