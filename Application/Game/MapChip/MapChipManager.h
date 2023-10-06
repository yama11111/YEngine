#pragma once
#include "MapChip.h"

namespace YGame
{
	class MapChipManager
	{
	
	public:

		/// <summary>
		/// �}�b�v�f�[�^�ǂݍ��� (csv)
		/// </summary>
		/// <param name="mapFileName"> : �}�b�v�t�@�C����</param>
		void Load(const std::string& mapFileName);
		
		/// <summary>
		/// �}�b�v�f�[�^�ǂݍ��� (csv)
		/// </summary>
		/// <param name="mapIndex"> : �}�b�v�ԍ�</param>
		/// <param name="mapFileName"> : �}�b�v�t�@�C����</param>
		void Load(const uint16_t mapIndex, const std::string& mapFileName);
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="mapIndex"> : �}�b�v�ԍ�</param>
		/// <param name="leftTop"> : ������W</param>
		/// <param name="chipScale"> : �`�b�v1�̑傫��</param>
		void Initialize(
			const uint16_t mapIndex,
			const YMath::Vector3& leftTop,
			const YMath::Vector3& chipScale);
		
		/// <summary>
		/// ���Z�b�g
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
		/// �}�b�v�`�b�v�|�C���^�擾
		/// </summary>
		/// <returns>�}�b�v�`�b�v�|�C���^</returns>
		MapChip* CurrentMapPointer() { return &map_; }
	
	public:
		
		/// <summary>
		/// �C���X�^���X�|�C���^�擾
		/// </summary>
		/// <returns>�C���X�^���X�|�C���^</returns>
		static MapChipManager* GetInstance();

	private:

		// �f�t�H���g�R���X�g���N�^
		MapChipManager() = default;
		// �f�t�H���g�f�X�g���N�^
		~MapChipManager() = default;
		// ����R���X�g���N�^�폜
		MapChipManager(const MapChipManager&) = delete;
		// ����폜
		const MapChipManager& operator=(const MapChipManager&) = delete;

	private:
		
		// �}�b�v�f�[�^
		std::vector<std::unique_ptr<MapData>> mapDatas_;
		
		// ���݂̃}�b�v�f�[�^�C���f�b�N�X
		uint16_t currentIndex_ = 0;
		
		// �}�b�v
		MapChip map_;
	};
}

