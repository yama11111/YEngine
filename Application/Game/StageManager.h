#pragma once
#include <cstdint>

namespace YGame
{
	class StageManager
	{
	
	public:
		
		/// <summary>
		/// ������
		/// </summary>
		void Initialize();

		/// <summary>
		/// ���Z�b�g
		/// </summary>
		void Reset();

		/// <summary>
		/// �X�V
		/// </summary>
		void Update();

	public:

		/// <summary>
		/// �Q�[���I�[�o�[
		/// </summary>
		void GameOver();

		/// <summary>
		/// �X�e�[�W�N���A
		/// </summary>
		void ClearStage();
		
	public:

		/// <summary>
		/// ���݂̃X�e�[�W�ԍ�
		/// </summary>
		/// <returns>�X�e�[�W�ԍ�</returns>
		uint32_t CurrentStageIndex() const;

		/// <summary>
		/// �X�e�[�W�ԍ��ݒ�
		/// </summary>
		/// <param name="index"> : �X�e�[�W�ԍ�</param>
		void SetStageIndex(const uint32_t index);

	public:
		
		static StageManager* GetInstance();
	
	private:

		StageManager() = default;
		~StageManager() = default;
		StageManager(const StageManager&) = delete;
		const StageManager& operator=(const StageManager&) = delete;
	
	private:

		uint32_t stageIndex = 0;

		bool isGameOver_ = false;

		bool isStageClear_ = false;
	
	};
}
