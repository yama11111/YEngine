#pragma once
#include "Sprite2D.h"
#include "MapChipCollider.h"
#include <memory>

namespace YGame
{
	// �}�b�v���
	struct MapData
	{
	
	public:
		
		// �}�b�v�`�b�v�ԍ�
		std::vector<std::vector<uint16_t>> chipNums_;
	
	public:

		/// <summary>
		/// csv�ǂݍ���
		/// </summary>
		/// <param name="mapFileName"> : �}�b�v�t�@�C����</param>
		void LoadCSV(const std::string& mapFileName);

		/// <summary>
		/// ����
		/// </summary>
		void Clear();
	
	};

	// �}�b�v�`�b�v
	class IMapChip
	{
	
	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="pMapData"> : �}�b�v�f�[�^�|�C���^</param>
		/// <param name="leftTop"> : ����</param>
		/// <param name="chipScale"> : �`�b�v1�̑傫��</param>
		void Initialize(MapData* pMapData, const YMath::Vector3& leftTop, const YMath::Vector3& chipScale);
		
		/// <summary>
		/// ������ (�}�b�v�f�[�^)
		/// </summary>
		/// <param name="pMapData"> : �}�b�v�f�[�^�|�C���^</param>
		void Initialize(MapData* pMapData);

		/// <summary>
		/// ������ (���� + �`�b�v�T�C�Y)
		/// </summary>
		/// <param name="leftTop"> : ����</param>
		/// <param name="chipScale"> : �`�b�v1�̑傫��</param>
		void Initialize(const YMath::Vector3& leftTop, const YMath::Vector3& chipScale);
		
		/// <summary>
		/// ���Z�b�g
		/// </summary>
		virtual void Reset() = 0;

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void Update() = 0;
		
		/// <summary>
		/// �`��
		/// </summary>
		virtual void Draw() = 0;
	
	public:

		/// <summary>
		/// �Փˎ�����
		/// </summary>
		/// <param name="collider"> : �R���C�_�[</param>
		void PerfectPixelCollision(MapChipCollider& collider);
		
		/// <summary>
		/// �傫�� (��`)
		/// </summary>
		/// <returns>�傫�� (��`)</returns>
		YMath::Vector2 Size();
	
	public:

		IMapChip() = default;
		
		virtual ~IMapChip() = default;
	
	protected:	
		
		// �`�b�v���Ƃ̃A�^������
		virtual bool CollisionChip(const int x, const int y);
	
	private:
		
		// ���ړ���̃`�b�v���Ƃ̃A�^������
		bool CollisionTemporaryMap(const YMath::Vector3& pos, const YMath::Vector3& scale, const YMath::Vector3& spd);
		
		// �`�b�v���Ƃ̃A�^������
		bool CollisionMap(const float left, const float right, const float top, const float bottom);
	
	protected:
		
		// �}�b�v�f�[�^�|�C���^
		MapData* pMapData_ = nullptr;


		// �`�b�v1���̑傫��
		YMath::Vector3 chipScale_;
		
		// ����([0][0])
		YMath::Vector3 leftTop_;
	
	};
}
