#include "AudioManager.h"
#include "YAssert.h"
#include <fstream>

using Game::AudioManager;
using DX::Result;

AudioManager::~AudioManager()
{
	xAudio2_.Reset();
	if (!audios_.empty())
	{
		for (size_t i = 0; i < audios_.size(); i++)
		{
			delete[] audios_[i].pBuff_;
		}
	}
}

void AudioManager::Initialize()
{
	// XAudio2�̃C���X�^���X����
	Result(XAudio2Create(&xAudio2_, 0, XAUDIO2_DEFAULT_PROCESSOR));

	// �}�X�^�[�{�C�X����
	Result(xAudio2_->CreateMasteringVoice(&masterVoice_));
}

UINT AudioManager::Load(const char* fileName)
{
	// �t�@�C�����̓X�g���[���̃C���X�^���X
	std::ifstream file;
	// .wav�t�@�C�����o�C�i�����[�h�ŊJ��
	file.open(fileName, std::ios_base::binary);
	// �t�@�C���I�[�v�����s�����o
	assert(file.is_open());

	// RIFF�w�b�_�|�̓ǂݍ���
	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));
	// �t�@�C����RIFF���`�F�b�N
	assert(strncmp(riff.chunk_.id_, "RIFF", 4) == 0);
	// �t�@�C����WAVE���`�F�b�N
	assert(strncmp(riff.type_, "WAVE", 4) == 0);

	// Format�`�����N�̓ǂݍ���
	FormatChunk format = {};
	// �`�����N�w�b�_�[�̊m�F
	file.read((char*)&format, sizeof(ChunkHeader));
	assert(strncmp(format.chunk_.id_, "fmt ", 4) == 0);
	// �`�����N�{�̂̓ǂݍ���
	assert(format.chunk_.size_ <= sizeof(format.fmt_));
	file.read((char*)&format.fmt_, format.chunk_.size_);

	// Data�`�����N�̓ǂݍ���
	ChunkHeader data;
	file.read((char*)&data, sizeof(data));
	// JUNK�`�����N�����o�����ꍇ
	if (strncmp(data.id_, "JUNK", 4) == 0)
	{
		// �ǂݎ��ʒu��JUMK�`�����N�̏I���܂Ői�߂�
		file.seekg(data.size_, std::ios_base::cur);
		// �t�@�C���ēǂݍ���
		file.read((char*)&data, sizeof(data));
	}
	assert(strncmp(data.id_, "data", 4) == 0);
	// Data�`�����N�̃f�[�^��(�g�`�f�[�^)�̓ǂݍ���
	char* pBuff = new char[data.size_];
	file.read(pBuff, data.size_);

	// �t�@�C�������
	file.close();

	// �T�E���h�f�[�^
	SoundData sound = {};
	sound.wfex_ = format.fmt_;
	sound.pBuff_ = reinterpret_cast<BYTE*>(pBuff);
	sound.buffSize_ = data.size_;

	// �T�E���h�f�[�^��ۑ�
	audios_.push_back(sound);

	return static_cast<UINT>(audios_.size() - 1);
}


//UINT AudioManager::Load(wchar_t* fileName)
//{
//	// �t�@�C������
//	HMMIO mmio;
//	MMIOINFO info;
//	mmio = mmioOpen(fileName, &info, MMIO_READ);
//	assert(mmio);
//
//	// RIFF �ǂݍ���
//	MMCKINFO riffChunk;
//	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
//	assert(mmioDescend(mmio, &riffChunk, nullptr, MMIO_FINDRIFF) == MMSYSERR_NOERROR);
//
//	// fmt �ǂݍ���
//	MMCKINFO chunk;
//	chunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
//	assert(mmioDescend(mmio, &chunk, &riffChunk, MMIO_FINDCHUNK) == MMSYSERR_NOERROR);
//
//	WAVEFORMATEX format;
//	assert(mmioRead(mmio, (HPSTR)&format, chunk.cksize) == chunk.cksize);
//
//	// data �ǂݍ���
//	chunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
//	assert(mmioDescend(mmio, &chunk, &riffChunk, MMIO_FINDCHUNK) == MMSYSERR_NOERROR);
//
//	return 0;
//}


void AudioManager::Play(const UINT audioIndex)
{
	// �g�`�t�H�[�}�b�g������SourceVoice����
	IXAudio2SourceVoice* pSourceVoice = nullptr;
	Result(xAudio2_->CreateSourceVoice(&pSourceVoice, &audios_[audioIndex].wfex_));

	// �Đ�����g�`�f�[�^�̐ݒ�
	XAUDIO2_BUFFER buff{};
	buff.pAudioData = audios_[audioIndex].pBuff_;
	buff.AudioBytes = audios_[audioIndex].buffSize_;
	buff.Flags = XAUDIO2_END_OF_STREAM;

	// �g�`�f�[�^�̍Đ�
	Result(pSourceVoice->SubmitSourceBuffer(&buff));
	Result(pSourceVoice->Start());
}
