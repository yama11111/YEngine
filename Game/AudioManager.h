#pragma once
#include <xaudio2.h>
#include <wrl.h>
#include <vector>

#pragma comment(lib, "xaudio2.lib")

namespace Game
{
	class AudioManager
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
		// XAudio2�G���W��
		Microsoft::WRL::ComPtr<IXAudio2> xAudio2_;
		// �}�X�^�[�{�C�X
		IXAudio2MasteringVoice* masterVoice_ = nullptr;
		// �I�[�f�B�I�pvector�z��
		std::vector<SoundData> audios_;
	public:
		// ������
		void Initialize();
		// �I�[�f�B�I�ǂݍ���(.wav�̂�)
		UINT Load(const char* fileName);
		//
		UINT Load(const wchar_t* fileName);
		// �Đ�
		void Play(const UINT audioIndex);
	public:
		~AudioManager();
	};
}
