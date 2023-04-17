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

	private:
		
		// �ÓI�I�[�f�B�I�i�[�pvector�z��
		static std::vector<std::unique_ptr<Audio>> audios_;

	public:
		
		/// <summary>
		/// �I�[�f�B�I�ǂݍ���(.wav�̂�)
		/// </summary>
		/// <param name="fileName"> : �t�@�C����</param>
		/// <returns>�I�[�f�B�I�|�C���^</returns>
		static Audio* Load(const std::string& fileName);

		/// <summary>
		/// �S�폜
		/// </summary>
		static void AllClear();

	public:
		
		/// <summary>
		/// �I�[�f�B�I�Đ�
		/// </summary>
		void Play();

	public:

		// �R�����N���X
		class Common
		{
		public:

			// XAudio2�G���W��
			static Microsoft::WRL::ComPtr<IXAudio2> xAudio2_;

			// �}�X�^�[�{�C�X
			static IXAudio2MasteringVoice* masterVoice_;

		public:

			/// <summary>
			/// �ÓI������
			/// </summary>
			static void StaticInitialize();

		public:

			Common() = default;

			~Common();
		};

	public:

		// �R����
		static Common common_;

	public:
		
		Audio() = default;

		~Audio() = default;
	};
}
