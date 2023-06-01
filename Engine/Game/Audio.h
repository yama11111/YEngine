#pragma once
#include <xaudio2.h>
#include <wrl.h>
#include <vector>
#include <string>
#include <memory>

#pragma comment(lib, "xaudio2.lib")

namespace YGame
{
	// �I�[�f�B�I�N���X
	class Audio
	{
	private:

		// �`�����N�w�b�_
		struct ChunkHeader 
		{
			char id_[4]; // �`�����N���Ƃ�id
			int32_t size_; // �`�����N�T�C�Y
		};
		// RIFF�w�b�_�`�����N
		struct RiffHeader
		{
			ChunkHeader chunk_; // "RIFF"
			char type_[4]; // "WAVE"
		};
		// FMI�`�����N
		struct FormatChunk
		{
			ChunkHeader chunk_; // "fmt"
			WAVEFORMATEX fmt_; // �g�`�t�H�[�}�b�g
		};
		// �����f�[�^
		struct SoundData 
		{
			// �g�`�t�H�[�}�b�g
			WAVEFORMATEX wfex_;
			// �o�b�t�@�̐擪�A�h���X
			BYTE* pBuff_;
			// �o�b�t�@�T�C�Y
			unsigned int buffSize_;
		};

	private:

		// �����f�[�^
		SoundData sound_{};

		// �e�N�X�`���t�@�C����
		std::string fileName_;

		// SourceVoice
		IXAudio2SourceVoice* pSourceVoice_ = nullptr;

	private:
		
		// �ÓI�I�[�f�B�I�i�[�pvector�z��
		static std::vector<std::unique_ptr<Audio>> audios_;

	public:
		
		/// <summary>
		/// �I�[�f�B�I�ǂݍ���(.wav�̂�)
		/// </summary>
		/// <param name="audioFileName"> : �����t�@�C����</param>
		/// <returns>�I�[�f�B�I�|�C���^</returns>
		static Audio* Load(const std::string& audioFileName);

		/// <summary>
		/// �I�[�f�B�I�ǂݍ���(.wav�̂�)
		/// </summary>		
		/// <param name="directoryPath"> : �f�B���N�g���p�X��</param>
		/// <param name="audioFileName"> : �����t�@�C����</param>
		/// <returns></returns>
		static Audio* Load(const std::string& directoryPath, const std::string& audioFileName);

		/// <summary>
		/// �S�폜
		/// </summary>
		static void AllClear();

	private:

		/// <summary>
		/// �w�b�_�[�{��
		/// </summary>
		static void SearchHeader(std::ifstream& file, const char* chunkId);

	public:

		/// <summary>
		/// �I�[�f�B�I�Đ�
		/// </summary>
		/// <param name="isLoop"> : ���[�v���邩</param>
		void Play(const bool isLoop);

		/// <summary>
		/// �{�����[���ݒ�
		/// </summary>
		/// <param name="volume"> : ����</param>
		void SetVolume(const float volume);

		/// <summary>
		/// �I�[�f�B�I��~
		/// </summary>
		void Stop();

	public:

		// �x�[�X�N���X
		class Base
		{
		public:

			// XAudio2�G���W��
			static Microsoft::WRL::ComPtr<IXAudio2> sXAudio2_;

			// �}�X�^�[�{�C�X
			static IXAudio2MasteringVoice* sMasterVoice_;

		public:

			/// <summary>
			/// �ÓI������
			/// </summary>
			static void StaticInitialize();

		public:

			Base() = default;

			~Base();
		};

	public:
		
		Audio() = default;

		~Audio() = default;
	};
}
