#pragma once
#include "ModelCommon.h"
#include "Object.h"
#include "ViewProjection.h"
#include "LightGroup.h"

namespace YGame
{
	// ���f���p�I�u�W�F�N�g
	typedef Object<ModelCommon::CBData> ObjectModel;

	// ���f���N���X
	class Model : private ModelCommon
	{
	private:
		// ���b�V���z��
		std::vector<Mesh> meshes_;
		// �F
		Color defColor_{};
	public:
		// �ǂݍ��ݐݒ�\����
		struct LoadStatus
		{
			std::string directoryPath_;
			std::string modelFileName_;
			bool isSmoothing_ = false;
			bool isInverseU_ = false;
			bool isInverseV_ = true;
			bool isNormalized_ = false;
			std::string extension_ = "";
		};
	public:
		// ����(������)
		static Model* Create();
		// ���f���ǂݍ���
		static Model* LoadObj(const std::string& modelFileName, const bool isSmoothing);
		// ���f���ǂݍ���(assimp)
		static Model* Load(const LoadStatus& state);
	public:
		// �`�� (�e�N�X�`�� + �F �L)
		void Draw(ObjectModel& obj, const ViewProjection& vp, LightGroup* lightGroup, Color& color, const UINT tex);
		// �`�� (�e�N�X�`�� �L)
		void Draw(ObjectModel& obj, const ViewProjection& vp, LightGroup* lightGroup, const UINT tex);
		// �`�� (�F �L)
		void Draw(ObjectModel& obj, const ViewProjection& vp, LightGroup* lightGroup, Color& color);
		// �`�� (�f�t�H���g)
		void Draw(ObjectModel& obj, const ViewProjection& vp, LightGroup* lightGroup);
	private:
		// �R���X�g���N�^
		Model() = default;
	};
}
