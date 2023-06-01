#pragma once
#include "Model.h"

namespace YGame
{
	class Level
	{

	public:

		// �I�u�W�F�N�g�Z�b�g
		struct ObjectSet
		{
			// ���f���|�C���^
			Model* pModel_ = nullptr;
			// �I�u�W�F�N�g�|�C���^
			std::unique_ptr<Model::Object> pObjs_;
			// �I�u�W�F�N�g�t�@�C����
			std::string objFileName_;
			// �q
			std::unique_ptr<ObjectSet> child_;
		};

	public:

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
		/// �X�V
		/// </summary>
		void UpdateObjSet(ObjectSet* obj);
		
		/// <summary>
		/// �`��
		/// </summary>
		void DrawObjSet(ObjectSet* obj);

	public:

		Level() = default;

		~Level() = default;

		Level(const Level&) = delete;

		const Level& operator=(const Level&) = delete;

	private:

		// �S�I�u�W�F�N�g
		std::list<std::unique_ptr<ObjectSet>> objSets_;

		// �t�@�C���p�X
		std::string fileName_;

	private:

		// �ÓI���x���f�[�^�i�[�plist
		static std::list<std::unique_ptr<Level>> sLevelDatas_;


	};
}
