#pragma once
#include "CharacterManager.h"
#include "MapChipManager.h"
#include "Camera.h"
#include <json.hpp>

namespace YGame
{
	class Level
	{

	public:

		static void LoadAsset();

		/// <summary>
		/// ���x���f�[�^�ǂݍ��� (.json)
		/// </summary>
		/// <param name="fileName"> : �t�@�C���� (.json)</param>
		/// <returns>���x���f�[�^�|�C���^</returns>
		static Level* LoadJson(const std::string& fileName);

		/// <summary>
		/// �S�f�[�^�N���A
		/// </summary>
		static void ClearAllData();

	public:
		
		void Initialize();

		/// <summary>
		/// �X�V
		/// </summary>
		void Update();

		/// <summary>
		/// �`��
		/// </summary>
		void Draw();

	public:

		Level() = default;

		~Level() = default;

		Level(const Level&) = delete;

		const Level& operator=(const Level&) = delete;

	private:
		
		/// <summary>
		/// �f�[�^�ǂݍ���
		/// </summary>
		/// <param name="object"> : �I�u�W�F�N�g(json)</param>
		/// <param name="pParent"> : �e�I�u�W�F�N�g�|�C���^</param>
		void LoadData(nlohmann::json& object, GameObject* pParent = nullptr);
	
	private:

		// �S�I�u�W�F�N�g
		std::list<std::unique_ptr<GameObject>> objs_;

		// �L�����N�^�[�}�l�[�W���[
		//std::unique_ptr<YGame::CharacterManager> characterMan_;

		// �}�b�v�`�b�v�}�l�[�W���[
		YGame::MapChipManager* pMapChipManager_ = nullptr;

		// �J����
		std::vector<std::unique_ptr<Camera>> cameras_;

		// �]���p�r���[�v���W�F�N�V����
		static ViewProjection transferVP_;

		// �t�@�C���p�X
		std::string fileName_;

	private:

		// �ÓI���x���f�[�^�i�[�plist
		static std::list<std::unique_ptr<Level>> sLevelDatas_;

	};
}
